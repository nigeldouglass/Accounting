{
    "targets": [
        {
            "target_name": "CppDB",
            "sources":[
                './cppdb/entry.cpp',
                "<!@(node -p \"require('fs').readdirSync('./cppdb/database').filter(f=>f.endsWith('.cpp')).map(f=>'cppdb/database/'+f).join(' ')\")",
                "<!@(node -p \"require('fs').readdirSync('./cppdb/database/structures').filter(f=>f.endsWith('.cpp')).map(f=>'cppdb/database/structures/'+f).join(' ')\")",
                "<!@(node -p \"require('fs').readdirSync('./cppdb/utils').filter(f=>f.endsWith('.cpp')).map(f=>'cppdb/utils/'+f).join(' ')\")",
                "<!@(node -p \"require('fs').readdirSync('./cppdb/utils/serialization').filter(f=>f.endsWith('.cpp')).map(f=>'cppdb/utils/serialization/'+f).join(' ')\")",
            ],
            'include_dirs': [
                "<!@(node -p \"require('node-addon-api').include\")"
            ],
            'libraries': [],
            'dependencies': [
                "<!(node -p \"require('node-addon-api').gyp\")"
            ],
            "cflags_cc": [
                "-std=c++17", 
                "-stdlib=libc++",
                "-fexceptions", 
            ],
            'cflags!': [ 
                '-fno-exceptions',
            ],
            "cflags_cc!": [ 
                '-fno-exceptions',
            ],
            "conditions": [
                [ 'OS!="win"', {
                    "cflags+": [ "-std=c++17" ],
                    "cflags_c+": [ "-std=c++17" ],
                    "cflags_cc+": [ "-std=c++17" ],
                }],
                [ 'OS=="mac"', {
                    "xcode_settings": {
                        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                        "OTHER_CPLUSPLUSFLAGS" : [ "-std=c++17", "-stdlib=libc++" ],
                        "OTHER_LDFLAGS": [ "-stdlib=libc++" ],
                        "MACOSX_DEPLOYMENT_TARGET": "10.15"
                    },
                }],
            ],
        }
    ]
}