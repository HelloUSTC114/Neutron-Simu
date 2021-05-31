#!/bin/bash
source ~/.bashrc

nRuns=30
nThreads=12

cd ~/Codes/Neutron-Build

# For Home PC
# dataDirRoot=~/Data/Geant4-Data/Position-Research/
# mkdir $dataDirRoot 2>/dev/null
# sourceDirRoot=~/Codes/Simu-LS/macJohn/Position-Research/

# For 507Station
dataDirRoot=/data/John/Neutron-Test1/
mkdir $dataDirRoot 2>/dev/null
sourceDirRoot=~/Codes/Neutron-Simu/macJohn/EJ-254-2/

# export LD_LIBRARY_PATH

function DoPosition() {
    echo "Seed: "  $(expr $(expr $1 \* $nThreads) + $2)
    ./CRTest $sourceDirRoot/Test_Slab.gdml $sourceDirRoot/test_neutron.mac $dataDir/rootFile/Yield-80-Run-$1-$2.root $(expr $(expr $1 \* $nThreads) + $2) >$dataDir/logFile/Yield-80-Run-$1-$2.log 2>&1
    # echo $sourceDirRoot/exe/Yield-$yield $sourceDirRoot/src/mac/test_pdu.mac $dataDir/rootFile/Yield-$yield-Run-$i.root $yield $dataDir/logFile/Yield-$yield-Run-$i.log

}

for ((i = 0; i < $nRuns; i++)); do
    echo RUN $i begins now -------- >>RunLog.txt
    echo $(date) >>RunLog.txt
    echo RUN $i begins now --------
    echo $(date)

    for ((j = 0; j < $nThreads; j++)); do
        dataDir=$dataDirRoot/
        mkdir $dataDir 2>/dev/null
        mkdir $dataDir/rootFile 2>/dev/null
        mkdir $dataDir/logFile 2>/dev/null

        DoPosition $i $j&

    done
    wait
    echo RUN $i ends now -------- >>RunLog.txt
    echo RUN $i ends now --------
done
