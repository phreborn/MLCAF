#!/bin/bash

REGION="SR"
<<<<<<< HEAD
TASK="alternateFR"
=======
<<<<<<< HEAD:share/AHZ-lephad/config/SR/analyze-submit-FF.sh
TASK="FF"
=======
TASK="alternateFR"
>>>>>>> 4dc7ea971698cb3d71224c891293bc3055dcea55:share/AHZ-lephad/config/SR/analyze-submit-alternateFR.sh
>>>>>>> 4dc7ea971698cb3d71224c891293bc3055dcea55

# Configuration of the analyze stage
CONFIG="AHZ-lephad/config/${REGION}/master/analyze-${TASK}.cfg"

# Job identifier
<<<<<<< HEAD
IDENTIFIER=${REGION}-${TASK}
=======
IDENTIFIER="${REGION}-${TASK}"
>>>>>>> 4dc7ea971698cb3d71224c891293bc3055dcea55

# Job list
JOBLIST="jobs_${REGION}-${TASK}_c16a.txt jobs_${REGION}-${TASK}_c16d.txt jobs_${REGION}-${TASK}_c16e.txt"

<<<<<<< HEAD
source "${CAFANALYSISSHARE:?}/AHZ-lephad/config/common/submit.sh" 
=======
source "${CAFANALYSISSHARE:?}/AHZ-lephad/config/common/submit.sh" "${CONFIG}" "${IDENTIFIER}" "${JOBLIST}"
>>>>>>> 4dc7ea971698cb3d71224c891293bc3055dcea55
