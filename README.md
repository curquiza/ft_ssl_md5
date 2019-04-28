# ft_ssl_md5

## Usage
```
$> ./ft_ssl
Usage: ./ft_ssl [algo] [options] [args]

Hash algorithms available:
  md5
  sha256
  sha224
  sha512
  sha384
  sha1

Options available:
  -p: echo STDIN to STDOUT and append the checksum to STDOUT
  -q: quiet mode
  -r: reverse the format of the output
  -s: print the sum of the given string
```

## Run
```
$> make re
...
$> echo "lol" | ./ft_ssl md5
59bcc3ad6775562f845953cf01624225
```

## Tests
```
$> make run_basic_tests
...
$> make run_main_tests
...
```
