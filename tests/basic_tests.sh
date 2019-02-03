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
    local real_md5="$(printf "$1" | md5)"
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
    local real_sha256="$(printf "$1" | openssl sha256)"
    local my_sh256="$("$ft_ssl_bin" "sha256" "$1")"
    if [[ "$real_sha256" == "$my_sh256" ]]; then
        printf "%-15s$GREEN%s$DEF\n" "  > sha256" "OK"
    else
        printf "%-15s$RED%s$DEF\n" "  > sha256" "KO"
        print_in_trace "$1" "my_sha256" "$my_sha256" "real_sha256" "$real_sha256"
    fi
}

# usage : run_test "str"
run_test() {
    print_title "$1"
    run_md5_test "$1"
    run_sha256_test "$1"
}

rm -f $trace

run_test ""
run_test "coco"
run_test "$"
run_test "There are multiple versions of the echo command, with different behaviors. Apparently the shell used for your script uses a version that doesn't recognize -n"
run_test 'xargs can also be used to parallelize operations with the -P maxprocs argument to specify how many parallel processes should be used to execute the commands over the input argument lists. However, the output streams may not be synchronized. This can be overcome by using an --output file argument where possible, and then combining the results after processing. The following example queues 24 processes and waits on each to finish before launching another
xargs often covers the same functionality as the backquote (`) feature of many shells, but is more flexible and often also safer, especially if there are blanks or special characters in the input. It is a good companion for commands that output long lists of files such as find, locate and grep, but only if you use -0, since xargs without -0 deals badly with file names containing simple quote, " and space. GNU Parallel is a similar tool that offers better compatibility with find, locate and grep when file names may contain simple quote, ", and space (newline still requires -0).'
