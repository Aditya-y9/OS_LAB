#!/bin/bash
read -p "Enter number of process: " numP
for ((i = 0; i < $numP; i++)); do
    read -p "Arival Time of p$(expr $i + 1): " arrivalT[$i]
    isCompleted[$i]=0
done
for ((i = 0; i < $numP; i++)); do
    read -p "Burst Time of p${i+1}: " burstT[$i]
done
echo "--- Higher number greater priority ---"
for ((i = 0; i < $numP; i++)); do
    read -p "Priority of p${i+1}: " prio[$i]
done
timeC=0
nProcessDone=0
totalTAT=0
totalWaitingT=0
while [ $nProcessDone -lt $numP ]; do
    ((maxPrioIndex = -1))
    for ((i = 0; i < $numP; i++)); do
        if [[ (isCompleted[i] -eq 0) && (arrivalT[i] -le timeC) && (
            maxPrioIndex -eq -1) ]]; then
            ((maxPrioIndex = i))
        fi
        if [[ (isCompleted[i] -eq 0) && (arrivalT[i] -le timeC) && (prio[i] -gt prio[maxPrioIndex]) ]]; then
            ((maxPrioIndex = i))
        fi
    done
    if [[ maxPrioIndex -eq -1 ]]; then
        ((timeC = timeC + 1))
        continue
    fi
    ((isCompleted[maxPrioIndex] = 1))
    ((cTimeLocal = timeC + burstT[maxPrioIndex]))
    ((completionTime[maxPrioIndex] = cTimeLocal))
    ((taT[maxPrioIndex] = cTimeLocal - arrivalT[maxPrioIndex]))
    ((totalTAT = totalTAT + taT[maxPrioIndex]))
    ((waitingT[maxPrioIndex] = taT[maxPrioIndex] - burstT[maxPrioIndex]))
    ((totalWaitingT = totalWaitingT + waitingT[maxPrioIndex]))
    ((nProcessDone = nProcessDone + 1))
    ((timeC = cTimeLocal))
done
for ((i = 0; i < $numP; i++)); do
    echo "Completion Time for p${i+1}: ${completionTime[$i]}"
done
for ((i = 0; i < $numP; i++)); do
    echo "Turn Around Time for p${i+1}: ${taT[$i]}"
done
for ((i = 0; i < $numP; i++)); do
    echo "Waiting Time for p${i+1}: ${waitingT[$i]}"
done
echo "Average Turn Around Time: $totalTAT / $numP"
echo "Average Waiting Time: $totalWaitingT / $numP"
