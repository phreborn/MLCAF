#!/bash/bin

dir=/publicfs/atlas/atlasnew/higgs/hh2X/huirun/multilepton/leptau/MLntuple/MVA
dir=/publicfs/atlas/atlasnew/higgs/hh2X/huirun/multilepton/leptau/MLntuple/gn2

for camp in mc16e
do
  ls ${dir}/${camp}/*root | grep -v user > FileList_nom_${camp}.txt
done

for camp in data18
do
  ls ${dir}/${camp}/*root > FileList_${camp}.txt
done
