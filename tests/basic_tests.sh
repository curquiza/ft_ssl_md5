#!/bin/bash

GREEN="\033[1;32m"
RED="\033[1;31m"
DEF="\033[0m"

ft_ssl_bin="./ft_ssl"
trace="tests/trace.txt"

# usage: print_title "str"
print_title() {
    if [[ "${#1}" -gt 40 ]]; then
        local new_str="$(printf "%.37s" "$1")..."
        printf "%-50s\n" "$new_str"
    elif [[ "${#1}" -eq 0 ]]; then
        printf "%-50s\n" "\"\""
    else
        printf "%-50s\n" "$1"
    fi
}

# usage: print_in_trace "str" "var_name1" "value1" "var_name2" "value2"
print_in_trace() {
    echo "$1" >> "$trace" 2>&1
    echo "$2 = $3" >> "$trace" 2>&1
    echo "$4 = $5" >> "$trace" 2>&1
    echo "---------------" >> "$trace" 2>&1
}

# usage : run_md5_test "str"
run_md5_test() {
    local real_md5="$(md5 "$1" | awk '{print $4}')"
    local my_md5="$("$ft_ssl_bin" "md5" "$1")"
    if [[ "$real_md5" == "$my_md5" ]]; then
        printf "%-15s$GREEN%s$DEF\n" "  > md5" "OK"
    else
        printf "%-15s$RED%s$DEF\n" "  > md5" "KO"
        print_in_trace "$1" "my_md5" "$my_md5" "real_md5" "$real_md5"
    fi
}

# usage : run_sha256_test "str"
run_sha256_test() {
    local real_sha256="$(openssl sha256 "$1" | awk '{print $2}')"
    local my_sha256="$("$ft_ssl_bin" "sha256" "$1")"
    if [[ "$real_sha256" == "$my_sha256" ]]; then
        printf "%-15s$GREEN%s$DEF\n" "  > sha256" "OK"
    else
        printf "%-15s$RED%s$DEF\n" "  > sha256" "KO"
        print_in_trace "$1" "my_sha256" "$my_sha256" "real_sha256" "$real_sha256"
    fi
}

# usage : run_sha224_test "str"
run_sha224_test() {
    local real_sha224="$(openssl sha224 "$1" | awk '{print $2}')"
    local my_sha224="$("$ft_ssl_bin" "sha224" "$1")"
    if [[ "$real_sha224" == "$my_sha224" ]]; then
        printf "%-15s$GREEN%s$DEF\n" "  > sha224" "OK"
    else
        printf "%-15s$RED%s$DEF\n" "  > sha224" "KO"
        print_in_trace "$1" "my_sha224" "$my_sha224" "real_sha224" "$real_sha224"
    fi
}

# usage : run_sha256_test "str"
run_sha512_test() {
    local real_sha512="$(openssl sha512 "$1" | awk '{print $2}')"
    local my_sha512="$("$ft_ssl_bin" "sha512" "$1")"
    if [[ "$real_sha512" == "$my_sha512" ]]; then
        printf "%-15s$GREEN%s$DEF\n" "  > sha512" "OK"
    else
        printf "%-15s$RED%s$DEF\n" "  > sha512" "KO"
        print_in_trace "$1" "my_sha512" "$my_sha512" "real_sha512" "$real_sha512"
    fi
}

# usage : run_sha256_test "str"
run_sha384_test() {
    local real_sha384="$(openssl sha384 "$1" | awk '{print $2}')"
    local my_sha384="$("$ft_ssl_bin" "sha384" "$1")"
    if [[ "$real_sha384" == "$my_sha384" ]]; then
        printf "%-15s$GREEN%s$DEF\n" "  > sha384" "OK"
    else
        printf "%-15s$RED%s$DEF\n" "  > sha384" "KO"
        print_in_trace "$1" "my_sha384" "$my_sha384" "real_sha384" "$real_sha384"
    fi
}

# usage : run_sha256_test "str"
run_sha1_test() {
    local real_sha1="$(openssl sha1 "$1" | awk '{print $2}')"
    local my_sha1="$("$ft_ssl_bin" "sha1" "$1")"
    if [[ "$real_sha1" == "$my_sha1" ]]; then
        printf "%-15s$GREEN%s$DEF\n" "  > sha1" "OK"
    else
        printf "%-15s$RED%s$DEF\n" "  > sha1" "KO"
        print_in_trace "$1" "my_sha1" "$my_sha1" "real_sha1" "$real_sha1"
    fi
}

# usage : run_test "str"
run_test() {
    print_title "$1"
    run_md5_test "$1"
    run_sha256_test "$1"
    run_sha224_test "$1"
    run_sha512_test "$1"
    run_sha384_test "$1"
    run_sha1_test "$1"
}

rm -f $trace

# run_test ""
# run_test "coco"
# run_test "$"
# run_test "There are multiple versions of the echo command, with different behaviors. Apparently the shell used for your script uses a version that doesn't recognize -n"
# run_test 'xargs can also be used to parallelize operations with the -P maxprocs argument to specify how many parallel processes should be used to execute the commands over the input argument lists. However, the output streams may not be synchronized. This can be overcome by using an --output file argument where possible, and then combining the results after processing. The following example queues 24 processes and waits on each to finish before launching another
# xargs often covers the same functionality as the backquote (`) feature of many shells, but is more flexible and often also safer, especially if there are blanks or special characters in the input. It is a good companion for commands that output long lists of files such as find, locate and grep, but only if you use -0, since xargs without -0 deals badly with file names containing simple quote, " and space. GNU Parallel is a similar tool that offers better compatibility with find, locate and grep when file names may contain simple quote, ", and space (newline still requires -0).'
run_test "Makefile"
run_test "src/main.c"
run_test "tests/inputs/erase"
run_test "tests/inputs/hello"
run_test "tests/inputs/coco.txt"
run_test "tests/inputs/empty.txt"
run_test "ft_ssl"


# Test relou de parsing
#
# $> md5 -rs "toto" -s "titi"                                                                  feature/input-parsing ✗  25/04/19 16:06
# f71dbe52628a3f83a77ab494817525c6 "toto"
# 5d933eef19aee7da192608de61b6c23d "titi"
# $> md5 -s "toto" -rs "titi"                                                                  feature/input-parsing ✗  25/04/19 16:06
# MD5 ("toto") = f71dbe52628a3f83a77ab494817525c6
# 5d933eef19aee7da192608de61b6c23d "titi"
# $> md5 -sr "toto" -s "titi"                                                                  feature/input-parsing ✗  25/04/19 16:07
# MD5 ("r") = 4b43b0aee35624cd95b910189b3dc231
# md5: toto: No such file or directory
# md5: -s: No such file or directory
# md5: titi: No such file or directory
# $> md5 Makefile -s "toto"
# MD5 (Makefile) = edc9d4e017be42fadc31ee179541d2e4
# md5: -s: No such file or directory
# md5: toto: No such file or directory

# $> md5 Makefile -r -s "toto"                                                                 feature/input-parsing ✗  25/04/19 16:10
# MD5 (Makefile) = edc9d4e017be42fadc31ee179541d2e4
# md5: -r: No such file or directory
# md5: -s: No such file or directory
# md5: toto: No such file or directory
# $> md5 -s "toto" -r Makefile -s Makefile                                                     feature/input-parsing ✗  25/04/19 16:12
# MD5 ("toto") = f71dbe52628a3f83a77ab494817525c6
# edc9d4e017be42fadc31ee179541d2e4 Makefile
# md5: -s: No such file or directory
# edc9d4e017be42fadc31ee179541d2e4 Makefile

# $> echo "lol" | md5 -pr                                                                      feature/input-parsing ✗  25/04/19 16:20
# lol
# 59bcc3ad6775562f845953cf01624225
# d41d8cd98f00b204e9800998ecf8427e
# $> echo -n "" | md5 -pr                                                                      feature/input-parsing ✗  25/04/19 16:21
# d41d8cd98f00b204e9800998ecf8427e
# d41d8cd98f00b204e9800998ecf8427e
# $> echo "lol" | md5 -rp Makefile
# lol
# 59bcc3ad6775562f845953cf01624225
# edc9d4e017be42fadc31ee179541d2e4 Makefile

