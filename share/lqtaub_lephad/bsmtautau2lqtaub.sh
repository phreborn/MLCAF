#!/bin/bash
function changeFolder(){
for file in `ls $1`
do
  if [ -d $1"/"$file ]
  then
  changeFolder $1"/"$file
  else
  sed -i "s/bsmtautau/lqtaub/g" $1"/"$file
  fi
done
}

changeFolder $1
