{
    "targets": [
        {
            "target_name": "gpiox_lite",
            "cflags!": [ "-fno-exceptions" ],
            "cflags_cc!": [ "-fno-exceptions" ],
            "sources": [ "src/node.cpp", "src/gpiox.cpp" ],
            "include_dirs": [ "<!@(node -p \"require('node-addon-api').include\")", "src" ],
            "defines": [ "NAPI_DISABLE_CPP_EXEPTIONS" ],
        }
    ]
}
