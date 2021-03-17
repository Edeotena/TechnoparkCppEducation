#!/usr/bin/env bash

PROG_PATH=${1}  # ./main.out
ROOT=$(dirname $(realpath $0))

RECORDS_F_NAME="record.dat"
TRANSACTIONS_F_NAME="transaction.dat"
BLACKRECORDS_F_NAME="blackrecord.dat"

rm -f $RECORDS_F_NAME $TRANSACTIONS_F_NAME $BLACKRECORDS_F_NAME
touch $RECORDS_F_NAME $TRANSACTIONS_F_NAME $BLACKRECORDS_F_NAME

IN="1
1
Stanislav
Ivanov
address_1
tel_1
88
132
26
2
Kirill
Koptelev
address_2
tel_2
112
22
59"

echo "${IN}" | eval "${PROG_PATH}"

IN="2
2
33
1
54"

echo "${IN}" | eval "${PROG_PATH}"

IN="3"

echo "${IN}" | eval "${PROG_PATH}"

for file in $RECORDS_F_NAME $TRANSACTIONS_F_NAME $BLACKRECORDS_F_NAME; do
	diff -uN $file $ROOT/${file}.gold
	if [[ "$?" != "0" ]]; then
		echo "Files mismatches"
		exit 1
	fi
done
