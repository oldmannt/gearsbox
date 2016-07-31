{
  "targets": [
      {
      "target_name": "gearsbox",
      "type": "static_library",
      "dependencies": [
        "./deps/sqlite3/sqlite3.gyp:sqlite3",
        "./deps/curl/libcurl.gyp:libcurl",
        "./deps/libuv/uv.gyp:libuv",
      ],
      "sources": [
        "<!@(python ./deps/djinni/example/glob.py ./generated-src/cpp   '*.cpp' '*.hpp' '*.h')",
        "<!@(python ./deps/djinni/example/glob.py ./src '*.cpp' '*.hpp' '*.c' '*.h')",
        "<!@(python ./deps/djinni/example/glob.py ./interface '*.hpp' '*.h')",
      ],
      "include_dirs": [
        "./generated-src/cpp",
        "./src/cpp",
        "./interface",
        './src/ui',
        './deps/ffmpeg/include',
      ],
      'all_dependent_settings': {
        'include_dirs': [
          './generated-src/cpp',
          "./interface",
          './src/cpp/ui',
        ]
      },
      'cflags!': [
              '-Werror',
            ],
    },
    {
      "target_name": "gearsbox_objc",
      "type": "static_library",
      "dependencies": [
        "./deps/djinni/support-lib/support_lib.gyp:djinni_objc",
        "gearsbox",
      ],
      "sources": [
        "<!@(python ./deps/djinni/example/glob.py ./generated-src/objc  '*.h' '*.mm' '*.m')",
        "<!@(python ./deps/djinni/example/glob.py src/objc  '*.h' '*.mm' '*.m')",
      ],
      "include_dirs": [
        "./generated-src/objc",
        "./generated-src/cpp",
      ],
      'all_dependent_settings': {
        'include_dirs': [
          './generated-src/objc',
          './generated-src/cpp',
          "./interface",
          './src/cpp/ui',
        ]
      },
      "defines": [
        'ZF_LOG_USE_NSLOG',
      ],
      'cflags!': [
              '-Werror',
            ],
    },
    {
      "target_name": "gearsbox_jni",
      "type": "static_library",
      "dependencies": [
        "./deps/djinni/support-lib/support_lib.gyp:djinni_jni",
        "gearsbox",
      ],
      "ldflags" : [ "-llog", "-Wl,--build-id,--gc-sections,--exclude-libs,ALL" ],
      "sources": [
        "./deps/djinni/support-lib/jni/djinni_main.cpp",
        "<!@(python deps/djinni/example/glob.py generated-src/jni   '*.cpp')",
      ],
      "include_dirs": [
        "generated-src/jni",
        "generated-src/cpp",
        "src/cpp",
        "./interface",
        './src/cpp/ui',
      ],
      "defines": [
        'ZF_LOG_USE_ANDROID_LOG',
      ],
      'cflags!': [
              '-Werror',
            ],
      'all_dependent_settings': {
        'include_dirs': [
          "./interface",
          './generated-src/cpp',
          './src/cpp/ui',
        ]
      },
    },
    {
      'target_name': 'test',
      'type': 'executable',
      'dependencies': [
        'gearsbox',
        'deps/gtest.gyp:gtest',
      ],
      'cflags_cc!': [ '-Werror', '-Wextra' ],
      'xcode_settings': {
        'OTHER_CPLUSPLUSFLAGS!' : ['-Werror', '-Wextra'],
      },
      'include_dirs': [
        '.',
        'test',
      ],
      "defines": [
        'TEST_STAND_ALONE',
        'GEARSBOX_TEST',
      ],
      'sources': [
        '<!@(python deps/djinni/example/glob.py test *.cpp *.hpp *.h)',
      ]
    },
  ],
}