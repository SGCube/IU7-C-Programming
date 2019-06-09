#!/usr/bin/env bash
./app.exe data_err/in_$1.txt out.txt < read_cmd.txt 2> out_err_$1.txt > output_$1.txt
if diff data_err/out_$1.txt out_err_$1.txt;
then echo $1: PASSED
else echo $1: FAILED
fi