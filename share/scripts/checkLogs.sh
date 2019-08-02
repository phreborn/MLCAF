#!/bin/bash

echo "$(date) : Checking logs..."

find ./logs -type f -name "*" | xargs grep -iEr "warn|fail|error" \
    | grep -v "systematics handling" \
    | grep -vE "root does not exist|can not find SF" | sed -e "/No cuts were activated for processing sample/,+1d" \
    | grep -vE "unexpected pileup weight|atlas-nightlies /cvmfs/atlas-nightlies.cern.ch/repo may be stale" \
    | uniq | sort | uniq;
