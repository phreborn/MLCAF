#!/bin/bash

PMG_XSEC_FILE="/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/PMGTools/PMGxsecDB_mc16.txt"

DSIDS=$(grep -F '/$(channel)/' "${CAFANALYSISSHARE:?}/configCommon/htautau_lephad_common.map" | cut -d ' ' -f 1 | tr -d '#[:blank:]')

grep -wF "${DSIDS:?}" "${PMG_XSEC_FILE:?}" | sort | sed '1i SampleID process xsectioninpb filtereff kfactor uncertup uncertdown generator etag' \
    | tr -s '[:blank:]' '~' | sed 's/~/,~/g' | column -t -s '~' | sed 's/\( *\) /\1/g' \
        > "${CAFANALYSISSHARE:?}/configCommon/htautau_lephad_common_xsec.csv-$(date +"%m-%d-%Y")"

echo "then manually edit all bbH/ggH cross-sections to equal 1.0 pb"
echo "or find a built-in solution in the framework to modify it at runtime"
