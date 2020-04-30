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
            'conditions': [
                ['node_shared_openssl=="false"', {
                  # so when "node_shared_openssl" is "false", then OpenSSL has been
                  # bundled into the node executable. So we need to include the same
                  # header files that were used when building node.
                  'include_dirs': [
                    '<(node_root_dir)/deps/openssl/openssl/include'
                  ],
                  "conditions" : [
                    ["target_arch=='ia32'", {
                      "include_dirs": [ "<(node_root_dir)/deps/openssl/config/piii" ]
                    }],
                    ["target_arch=='x64'", {
                      "include_dirs": [ "<(node_root_dir)/deps/openssl/config/k8" ]
                    }],
                    ["target_arch=='arm'", {
                      "include_dirs": [ "<(node_root_dir)/deps/openssl/config/arm" ]
                    }]
                  ]
                }]
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