#!/bash/bin

dir=/publicfs/atlas/atlasnew/higgs/hh2X/huirun/multilepton/leptau/MLntuple/gn2

for camp in mc16a
do
  ls ${dir}/${camp}/*root > FileList_nom_${camp}.txt
done

for camp in data1516
do
  ls ${dir}/${camp}/*root > FileList_${camp}.txt
done
