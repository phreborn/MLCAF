#!/bin/bash

alias tqpdflatex=/afs/cern.ch/sw/XML/texlive/latest/bin/x86_64-linux/pdflatex
#export PATH=/afs/cern.ch/sw/XML/texlive/latest/bin/x86_64-linux/pdflatex:$PATH

tqpdflatex -interaction=nonstopmode -output-directory=`echo $1 | cut -d '/' -f 1,2` -jobname=summary-`echo $1 | cut -d '/' -f 2` $1
