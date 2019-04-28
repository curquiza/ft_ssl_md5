# algo, arg cmd, expect_error, outputfile

INPUT_CMDS = [
    { './ft_ssl md5 Makefile',                  False, 'md5_basic_1.txt' },
    { './ft_ssl sha256 tests/notes.txt',        False, 'sha256_basic_1.txt' },
    { './ft_ssl sha224 Makefile',               False, 'sha224_basic_1.txt' },
    { './ft_ssl sha512 include/ft_ssl.h',       False, 'sha512_basic_1.txt' },
    { './ft_ssl sha384 tests/inputs/coco.txt',  False, 'sha384_basic_1.txt' },
    { './ft_ssl sha1 tests/inputs/erase',       False, 'sha1_basic_1.txt' },
    # {'./ft_ssl md5 ft_ssl notes.txt', False, None},
    # {'echo lol | ./ft_ssl md5 -p', False, None}
]
