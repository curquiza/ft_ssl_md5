# algo, arg cmd, expect_error, outputfile

INPUT_CMDS = [
    { 'cmd': './ft_ssl',                                                        'error': True,  'output': 'usage' },
    { 'cmd': './ft_ssl sha551 README.md',                                       'error': True,  'output': 'wrong_algo_1' },
    { 'cmd': './ft_ssl -q md5 Makefile',                                        'error': True,  'output': 'wrong_algo_2' },

    { 'cmd': './ft_ssl md5 README.md',                                          'error': False, 'output': 'md5_basic_1' },
    { 'cmd': './ft_ssl md5 src',                                                'error': True,  'output': 'md5_err_1' },
    { 'cmd': './ft_ssl md5 README.md src tests/inputs/hello',                   'error': True,  'output': 'md5_err_2' },
    { 'cmd': './ft_ssl md5 sha256 src tests/inputs/hello',                      'error': True,  'output': 'md5_err_3' },
    { 'cmd': './ft_ssl md5 -ry README.md -q',                                   'error': True,  'output': 'md5_err_4' },
    { 'cmd': './ft_ssl md5 -r README.md -y',                                    'error': True,  'output': 'md5_err_5' },
    { 'cmd': './ft_ssl md5 -q tests/inputs/coco.txt',                           'error': False, 'output': 'md5_opt_qr_1' },
    { 'cmd': './ft_ssl md5 -rq tests/inputs/coco.txt',                          'error': False, 'output': 'md5_opt_qr_2' },
    { 'cmd': 'echo lol | ./ft_ssl md5 -p tests/inputs/empty.txt',               'error': False, 'output': 'md5_opt_p_1' },
    { 'cmd': 'echo titi | ./ft_ssl md5 -ppp tests/inputs/coco.txt',             'error': False, 'output': 'md5_opt_p_2' },
    { 'cmd': './ft_ssl md5 -srq',                                               'error': False, 'output': 'md5_opt_s_1' },
    { 'cmd': 'echo lol | ./ft_ssl md5',                                         'error': False, 'output': 'md5_stdin_1' },
    { 'cmd': 'cat tests/inputs/erase | ./ft_ssl md5',                           'error': False, 'output': 'md5_stdin_2' },
    { 'cmd': './ft_ssl md5 -rs "toto" -s "titi"',                               'error': False, 'output': 'md5_multi_1' },
    { 'cmd': './ft_ssl md5 -s "toto" -sr "titi"',                               'error': True,  'output': 'md5_multi_2' },
    { 'cmd': './ft_ssl md5 -sr "toto" -s "titi"',                               'error': True,  'output': 'md5_multi_3' },
    { 'cmd': './ft_ssl md5 README.md -s "toto"',                                'error': True,  'output': 'md5_multi_4' },
    { 'cmd': 'echo "lol" | ./ft_ssl md5 -pr',                                   'error': False, 'output': 'md5_multi_5' },
    { 'cmd': 'echo "" | ./ft_ssl md5 -pr -s "lol" -p README.md src',            'error': True,  'output': 'md5_multi_6' },
    { 'cmd': 'echo "lol" | ./ft_ssl md5 -rp README.md',                         'error': False, 'output': 'md5_multi_7' },
    { 'cmd': 'echo "lol" | ./ft_ssl md5 -p',                                    'error': False, 'output': 'md5_multi_8' },
    { 'cmd': 'echo "lol" | ./ft_ssl md5 -stests/inputs/erase -s',               'error': True,  'output': 'md5_multi_9' },

    { 'cmd': './ft_ssl sha256 tests/notes.txt',                                 'error': False, 'output': 'sha256_basic_1' },
    { 'cmd': './ft_ssl sha256 -qr tests/inputs/coco.txt',                       'error': False, 'output': 'sha256_opt_qr_1' },
    { 'cmd': 'echo bouh | ./ft_ssl sha256 -ppppp tests/inputs/file README.md',  'error': False, 'output': 'sha256_opt_p_1' },
    { 'cmd': 'echo bouh | ./ft_ssl sha256 tests/inputs/hello',                  'error': False, 'output': 'sha256_stdin_1' },
    { 'cmd': 'echo bouh | ./ft_ssl sha256 tests/inputs/coco.txt -p',            'error': True,  'output': 'sha256_stdin_2' },
    { 'cmd': './ft_ssl sha256 README.md -r -s "toto"',                          'error': True,  'output': 'sha256_multi_1' },
    { 'cmd': 'echo "lol" | ./ft_ssl sha256 -s "hello" -p',                      'error': False, 'output': 'sha256_multi_2' },
    { 'cmd': './ft_ssl sha256 - README.md',                                     'error': True,  'output': 'sha256_multi_3' },
    { 'cmd': './ft_ssl sha256 -q -- -r README.md',                              'error': True,  'output': 'sha256_multi_4' },
    { 'cmd': './ft_ssl sha256 --- README.md',                                   'error': True,  'output': 'sha256_multi_5' },
    { 'cmd': './ft_ssl sha256 --',                                              'error': False, 'output': 'sha256_multi_6' },
    { 'cmd': 'echo lol | ./ft_ssl sha256 --',                                   'error': False, 'output': 'sha256_multi_7' },
    { 'cmd': 'echo lol | ./ft_ssl sha256 -p -s titi -p',                        'error': False, 'output': 'sha256_multi_8' },

    { 'cmd': './ft_ssl sha224 README.md',                                       'error': False, 'output': 'sha224_basic_1' },
    { 'cmd': './ft_ssl sha224 -s test_de_ouf',                                  'error': False, 'output': 'sha224_opt_s_1' },
    { 'cmd': 'echo bouh | ./ft_ssl sha224 -p',                                  'error': False, 'output': 'sha224_opt_p_1' },

    { 'cmd': './ft_ssl sha512 tests/inputs/hello',                              'error': False,  'output': 'sha512_basic_1' },
    { 'cmd': './ft_ssl sha512 -rrrrr README.md',                                'error': False,  'output': 'sha512_opt_qr_1' },
    { 'cmd': './ft_ssl sha512 -rrrqrr README.md',                               'error': False,  'output': 'sha512_opt_qr_2' },
    { 'cmd': './ft_ssl sha512 -s "toto" -r README.md -s README.md',             'error': True,   'output': 'sha512_multi_1' },

    { 'cmd': './ft_ssl sha384 tests/inputs/coco.txt',                           'error': False,  'output': 'sha384_basic_1' },

    { 'cmd': './ft_ssl sha1 tests/inputs/erase',                                'error': False,  'output': 'sha1_basic_1' },
    { 'cmd': './ft_ssl sha1 -q -s',                                             'error': True,   'output': 'sha1_opt_s_1' },

    { 'cmd': 'echo "pickle rick" | ./ft_ssl md5',                                                       'error': False,  'output': 'subject_1' },
    { 'cmd': 'echo "Do not pity the dead, Harry." | ./ft_ssl md5 -p',                                   'error': False,  'output': 'subject_2' },
    { 'cmd': 'echo "Pity the living." | ./ft_ssl md5 -q -r',                                            'error': False,  'output': 'subject_3' },
    { 'cmd': './ft_ssl md5 tests/inputs/file',                                                          'error': False,  'output': 'subject_4' },
    { 'cmd': './ft_ssl md5 -r tests/inputs/file',                                                       'error': False,  'output': 'subject_5' },
    { 'cmd': './ft_ssl md5 -s "pity those that aren\'t following baerista on spotify."',                'error': False,  'output': 'subject_6' },
    { 'cmd': 'echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p tests/inputs/file',       'error': False,  'output': 'subject_7' },
    { 'cmd': 'echo "some of this will not make sense at first" | ./ft_ssl md5 tests/inputs/file',       'error': False,  'output': 'subject_8' },
    { 'cmd': 'echo "but eventually you will understand" | ./ft_ssl md5 -p -r tests/inputs/file',        'error': False,  'output': 'subject_9' },
    { 'cmd': 'echo "GL HF let\'s go" | ./ft_ssl md5 -p -s "foo" tests/inputs/file',                     'error': False,  'output': 'subject_10' },
    { 'cmd': 'echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" tests/inputs/file -s "bar"',          'error': True,   'output': 'subject_11' },
    { 'cmd': 'echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" tests/inputs/file',        'error': False,  'output': 'subject_12' },
    { 'cmd': './ft_ssl sha256 -q tests/inputs/big_smoke_order_remix',                                   'error': False,  'output': 'subject_13' },
    { 'cmd': './ft_ssl sha256 tests/inputs/big_smoke_order_remix',                                      'error': False,  'output': 'subject_14' },
    { 'cmd': './ft_ssl sha256 -s "wubba lubba dub dub"',                                                'error': False,  'output': 'subject_15' },
]

# ./ft_ssl md5 -rp
# ./ft_ssl md5 -s "lol" -pr -stiti -pqr Makefile lol src/main.c
# cat tests/inputs/erase | ./ft_ssl md5 -p
