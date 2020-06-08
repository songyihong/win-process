{
  'target_defaults': {
    'win_delay_load_hook': 'false',
    'conditions': [
      ['OS=="win"', {
        'msvs_disabled_warnings': [
          4530,  # C++ exception handler used, but unwind semantics are not enabled
          4506,  # no definition for inline function
        ],
      }],
    ],
  },
  'targets': [
    {
      'target_name': 'win-process',
      'sources': [
        'src/main.cc',
      ],
      'libraries': [
        '-lpsapi.lib',
      ],
      'include_dirs': [
        '<!(node -e "require(\'nan\')")'
      ],
    }
  ]
}