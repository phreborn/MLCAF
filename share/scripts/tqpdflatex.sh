#!/bin/bash

alias tqpdflatex=/cvmfs/sft.cern.ch/lcg/external/texlive/2020/bin/x86_64-linux/pdflatex

OUTDIR=`dirname $1`
OUTPUT=`basename $1`
REGION=`echo $OUTDIR | rev | cut -d '/' -f 1 | rev`

tqpdflatex -interaction=batchmode -output-directory=${OUTDIR} $1
mv -v ${OUTDIR}/${OUTPUT/.tex/.pdf} ${OUTDIR}/${OUTPUT/.tex/-${REGION}.pdf}
echo "Done!"
