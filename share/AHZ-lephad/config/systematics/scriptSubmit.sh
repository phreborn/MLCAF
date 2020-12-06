#!/bin/bash

echo "Submitting systematic jobs: CP-weight"
python scriptSubmit.py --task CP-weight --jobs bsmtautau_lephad/config-Common/jobLists/jobs_systematics-CP.txt --variationsPerJob 4

#echo "Submitting systematic jobs: CP-p4"
#python scriptSubmit.py --task CP-p4 --jobs bsmtautau_lephad/config-Common/jobLists/jobs_systematics-CP.txt --variationsPerJob 4
