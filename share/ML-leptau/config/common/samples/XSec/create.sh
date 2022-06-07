#!/bin/bash

outf=XS.csv
> ${outf}
echo "SampleID, process, xsectioninpb, filtereff, kfactor, uncertup, uncertdown, generator, etag" >> ${outf}

dsids=$(cat ../maps/HHML.map | grep -v "#" | cut -d ' ' -f 1 | sort | uniq)
for id in ${dsids}
do
  if [ "${id}" == "" ];then continue;fi
  echo "${id}, Default, 1, 1, 1, 0, 0, Default, Default" >> ${outf}
done
