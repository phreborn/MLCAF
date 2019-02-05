#!/bin/sh

samplesList=sampleList_v2.txt
outFile="/tmp/boehlerm/XSfile.txt";
tmpfile="/tmp/boehlerm/tmpFile";
rm $outFile; touch $outFile;
for dataset in `cat $samplesList`;
do
  rm  $tmpfile
  ami show dataset info $dataset > $tmpfile ;
  #echo `cat $tmpfile | grep datasetNumber |cut -f2 -d :`,`cat $tmpfile | grep approx_crossSection |cut -f2 -d :`,1.0,`cat $tmpfile | grep approx_GenFiltEff |cut -f2 -d :`,--,125,1,`cat $tmpfile | grep generatorName |cut -f2 -d :`,`cat $tmpfile | grep physicsShort |cut -f2 -d :`,`cat $tmpfile | grep conditionsTag |cut -f2 -d :` >> $outFile;
  #  SampleID,category,xsectioninpb,kfactor,efficiency,generator
  echo `cat $tmpfile | grep datasetNumber |cut -f2 -d :`,`cat $tmpfile | grep physicsShort |cut -f2 -d :`,`cat $tmpfile | grep approx_crossSection |cut -f2 -d :`,1.0,`cat $tmpfile | grep approx_GenFiltEff |cut -f2 -d :`,`cat $tmpfile | grep generatorName |cut -f2 -d :`
done