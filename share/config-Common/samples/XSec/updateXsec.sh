#!/bin/bash

PMG_XSEC_FILE="/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/PMGTools/PMGxsecDB_mc16.txt"
OUTPUT_FILE="${CAFANALYSISSHARE:?}/config-Common/samples/XSec/XS.csv-$(date +"%Y-%m-%d")"

echo -e "\e[93mUpdating Xsec...\e[39m"

# collect DSIDs from the map file, including commented samples
DSIDS=$(grep -F '/$(channel)/' "${CAFANALYSISSHARE:?}/config-Common/samples/maps/map.map" | cut -d ' ' -f 1 | tr -d '#[:blank:]')

# match DSIDs against the PMG file, sort, and apply a header line
OUTPUT=$(grep -wF "${DSIDS:?}" "${PMG_XSEC_FILE:?}" | sort | sed '1i SampleID process xsectioninpb filtereff kfactor uncertup uncertdown generator etag')

# re-format the output into a condensed, comma-separated, columnated table, with single-spacing between columns
OUTPUT=$(echo "${OUTPUT}" | tr -s '[:blank:]' '~' | sed 's/~/,~/g' | column -t -s '~' | sed 's/\( *\) /\1/g')

# save the output to file
echo "${OUTPUT}" > "${OUTPUT_FILE}"

echo -e "\e[92mXsec updated: \e[94m${OUTPUT_FILE}\e[39m"

# temporary information
echo -e "\e[91mnow manually remove multiple DSIDs for alternate e-tags:\e[39m"
# show the lines which have duplicated DSIDs
sort -k1n "${OUTPUT_FILE}" | awk 'a[$1]++{ if(a[$1]==2){ print b }; print $0}; {b=$0}'
