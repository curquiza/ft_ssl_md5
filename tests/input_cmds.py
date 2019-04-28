# algo, arg cmd, expect_error, outputfile

INPUT_CMDS = [
    { './ft_ssl',                                                   True,   'usage' },
    { './ft_ssl sha551 Makefile',                                   True,   'wrong_algo_1' },
    { './ft_ssl -q md5 Makefile',                                   True,   'wrong_algo_2' },

    { './ft_ssl md5 Makefile',                                      False,  'md5_basic_1' },
    { './ft_ssl md5 src',                                           True,   'md5_err_1' },
    { './ft_ssl md5 Makefile src src/main.txt',                     True,   'md5_err_2' },
    { './ft_ssl md5 sha256 src src/main.txt',                       True,   'md5_err_3' },
    { './ft_ssl md5 -ry Makefile -q',                               True,   'md5_err_4' },
    { './ft_ssl md5 -r Makefile -y',                                True,   'md5_err_5' },
    { './ft_ssl md5 -q tests/inputs/coco.txt',                      False,  'md5_opt_qr_1' },
    { './ft_ssl md5 -rq tests/inputs/coco.txt',                     False,  'md5_opt_qr_2' },
    { 'echo lol | ./ft_ssl md5 -p src/main.c',                      False,  'md5_opt_p_1' },
    { 'echo titi | ./ft_ssl md5 -ppp ft_ssl',                       False,  'md5_opt_p_2' },
    { './ft_ssl md5 -srq',                                          False,  'md5_opt_s_1' },
    { './ft_ssl md5 -rs "toto" -s "titi"',                          False,  'md5_multi_1' },
    { './ft_ssl md5 -s "toto" -sr "titi"',                          False,  'md5_multi_2' },
    { './ft_ssl md5 -sr "toto" -s "titi"',                          True,   'md5_multi_3' },
    { './ft_ssl md5 Makefile -s "toto"',                            True,   'md5_multi_4' },
    { 'echo "lol" | ./ft_ssl md5 -pr',                              False,  'md5_multi_5' },
    { 'echo -n "" | ./ft_ssl md5 -pr',                              False,  'md5_multi_6' },
    { 'echo "lol" | ./ft_ssl md5 -rp Makefile',                     False,  'md5_multi_7' },
    { 'echo "lol" | ./ft_ssl md5 -p',                               False,  'md5_multi_8' },


    { './ft_ssl sha256 tests/notes.txt',                            False,  'sha256_basic_1' },
    { './ft_ssl sha256 -qr tests/inputs/coco.txt',                  False,  'sha256_opt_qr_1' },
    { 'echo -n bouh | ./ft_ssl sha256 -ppppp ft_ssl Makefile',      False,  'sha256_opt_p_1' },
    { 'echo bouh | ./ft_ssl sha256 ft_ssl',                         False,  'sha256_stdin_1' },
    { 'echo bouh | ./ft_ssl sha256 ft_ssl -p',                      True,   'sha256_stdin_2' },
    { './ft_ssl sha256 Makefile -r -s "toto"',                      True,   'sha256_multi_1' },
    { 'echo "lol" | ./ft_ssl sha256 -s "hello" -p',                 False,  'sha256_multi_2' },
    { './ft_ssl sha256 - Makefile',                                 True,   'sha256_multi_3' },
    { './ft_ssl sha256 -q -- -r Makefile',                          True,   'sha256_multi_4' },
    { './ft_ssl sha256 --- Makefile',                               True,   'sha256_multi_5' },
    { './ft_ssl sha256 --',                                         False,  'sha256_multi_6' },
    { 'echo lol | ft_ssl sha256 --',                                False,  'sha256_multi_7' },
    { 'echo lol | ./ft_ssl sha256 -p -s titi -p',                   False,  'sha256_multi_8' },

    { './ft_ssl sha224 Makefile',                                   False,  'sha224_basic_1' },
    { './ft_ssl sha224 -s test_de_ouf',                             False,  'sha224_opt_s_1' },
    { 'echo bouh | ./ft_ssl sha224 -p',                             False,  'sha224_opt_p_1' },

    { './ft_ssl sha512 include/ft_ssl.h',                           False,  'sha512_basic_1' },
    { './ft_ssl sha512 -rrrrr Makefile',                            True,   'sha512_opt_qr_1' },
    { './ft_ssl sha512 -rrrqrr Makefile',                           True,   'sha512_opt_qr_2' },
    { './ft_ssl sha512 -s "toto" -r Makefile -s Makefile',          True,   'sha512_multi_1' },

    { './ft_ssl sha384 tests/inputs/coco.txt',                      False,  'sha384_basic_1' },
    { 'echo titi | ./ft_ssl sha256 -p Mak',                         True,   'sha384_opt_p_1' },

    { './ft_ssl sha1 tests/inputs/erase',                           False,  'sha1_basic_1' },
    { './ft_ssl sha1 -q -s',                                        True,   'sha1_opt_s_1' },

    { 'echo "pickle rick" | ./ft_ssl md5',                                                      False,  'subject_1' },
    { 'echo "Do not pity the dead, Harry." | ./ft_ssl md5 -p',                                  False,  'subject_2' },
    { 'echo "Pity the living." | ./ft_ssl md5 -q -r',                                           False,  'subject_3' },
    { './ft_ssl md5 tests/inputs/file',                                                         False,  'subject_4' },
    { './ft_ssl md5 -r tests/inputs/file',                                                      False,  'subject_5' },
    { './ft_ssl md5 -s "pity those that aren\'t following baerista on spotify."',               False,  'subject_6' },
    { 'echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p tests/inputs/file',      False,  'subject_7' },
    { 'echo "some of this will not make sense at first" | ./ft_ssl md5 tests/inputs/file',      False,  'subject_8' },
    { 'echo "but eventually you will understand" | ./ft_ssl md5 -p -r tests/inputs/file',       False,  'subject_9' },
    { 'echo "GL HF let\'s go" | ./ft_ssl md5 -p -s "foo" tests/inputs/file',                    False,  'subject_10' },
    { 'echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" tests/inputs/file -s "bar"',         True,   'subject_11' },
    { 'echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" tests/inputs/file',       False,  'subject_12' },
    { './ft_ssl sha256 -q tests/inputs/big_smoke_order_remix',                                  False,  'subject_13' },
    { './ft_ssl sha256 tests/inputs/big_smoke_order_remix',                                     False,  'subject_14' },
    { './ft_ssl sha256 -s "wubba lubba dub dub"',                                               False,  'subject_15' },
]

# ./ft_ssl md5 -rp
# ./ft_ssl md5 -s "lol" -pr -stiti -pqr Makefile lol src/main.c
