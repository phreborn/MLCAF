#!/bin/bash

echo "$(date) : Checking logs..."

find "${CAFANALYSISSHARE:?}/logs" -type f -name "${1}*" -print0 | xargs -0 grep -iE "warn|fail|error" \
    | grep -v "No messages of type warning or worse printed" \
    | grep -v $'\e\[1;33mWARNING\e\[0m\e\[1m: \e\[0m\e\[1m   ' | grep -v $'\e\[1;31mERROR\e\[0m\e\[1m: \e\[0m\e\[1m   ' \
    | sed -e "/No cuts were activated for processing sample/,+1d" \
    | uniq | sort | uniq;

# old omissions
#    | grep -v "systematics handling" \
#    | grep -v "root does not exist" \
#    | grep -v "can not find SF" \
#    | grep -v "unexpected pileup weight" \
#    | grep -v "atlas-nightlies /cvmfs/atlas-nightlies.cern.ch/repo may be stale" \
