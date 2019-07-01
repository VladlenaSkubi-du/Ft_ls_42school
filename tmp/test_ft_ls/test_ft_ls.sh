#!/usr/bin/env bash
flags="1CFGRSacdfglprstu"
ori="ls $flags $argvs > test_ori.txt"
our="./ft_ls $flags $argvs > test_our.txt"
compare="diff -y test_ori.txt test_our.txt"



