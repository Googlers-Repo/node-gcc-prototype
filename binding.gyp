{
  "targets": [{
    "target_name": "android_native",
    "cflags!": [ "-Wimplicit-function-declaration -llog" ],
    "cflags_cc!": [ "-Wimplicit-function-declaration -llog" ],
    "include_dirs": [
      "<!(node -e \"require('napi-macros')\")"
    ],
    "sources": [
      "native_log.c"
    ]
  }]
}