#!/bin/bash

echo "$(date) : Checking logs..."

find "${CAFANALYSISSHARE:?}/logs" -type f -name "${1}*" -print0 | xargs -0 grep -iE "warn|fail|error" \
    | grep -v "No messages of type warning or worse printed" \
    | uniq | sort | uniq;

# old omissions
#    | grep -v "systematics handling" \
#    | grep -vE "root does not exist|can not find SF" | sed -e "/No cuts were activated for processing sample/,+1d" \
#    | grep -v "unexpected pileup weight" \
#    | grep -v "atlas-nightlies /cvmfs/atlas-nightlies.cern.ch/repo may be stale" \
#    | grep -v '^[\[1;33mWARNING^[\[0m^[\[1m: ^[\[0m^[\[1m   ' | grep -v '^[\[1;31mERROR^[\[0m^[\[1m: ^[\[0m^[\[1m   ' \
#    | grep -v "No messages of type warning or worse printed" \
