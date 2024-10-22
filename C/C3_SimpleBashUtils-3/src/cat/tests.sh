#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF=""

s21_command=(
    "./s21_cat"
    )
sys_command=(
    "cat"
    )

tests=(
"FLAGS test_files/test_case_cat.txt"
"FLAGS test_files/test_case_cat.txt test_files/test_1_cat.txt"
"FLAGS test_files/test_2_cat.txt test_files/test_3_cat.txt"
"FLAGS test_files/test_4_cat.txt test_files/test_5_cat.txt"
"FLAGS nofile.txt"
)
flags=(
    "b"
    "e"
    "n"
    "s"
    "t"
    "v"
)

run_test() {
    param=$(echo "$@" | sed "s/FLAGS/$var/")
    "${s21_command[@]}" $param > "${s21_command[@]}".log
    "${sys_command[@]}" $param > "${sys_command[@]}".log
    DIFF="$(diff -s "${s21_command[@]}".log "${sys_command[@]}".log)"
    let "COUNTER++"
    if [ "$DIFF" == "Files "${s21_command[@]}".log and "${sys_command[@]}".log are identical" ]
    then
        let "SUCCESS++"
        echo "$COUNTER - ✅ Success\n$param\n"
    else
        let "FAIL++"
        echo "$COUNTER - ❌ Fail $param"
    fi
    rm -f "${s21_command[@]}".log "${sys_command[@]}".log
}



for var1 in "${flags[@]}"
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        run_test "$i"
    done
done

for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1 -$var2"
                run_test "$i"
            done
        fi
    done
done


printf "\n"

echo "FAILED: $FAIL"
echo "SUCCESSFUL: $SUCCESS"
echo "ALL: $COUNTER"
printf "\n"
