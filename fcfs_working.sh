#!/bin/bash

#Take user input for
# arrival time,
# burst time,
# priority
function insertion_sort {
    local -n at=$1
    local -n bt=$2
    local -n pid=$3

    local i j key keybt keypid

    for ((i = 1; i < ${#at[@]}; i++)); do
        key=${at[i]}
        keybt=${bt[i]}
        keypid=${pid[i]}
        j=$((i - 1))
        while ((j >= 0 && at[j] > key)); do
            at[(j + 1)]=${at[j]}
            bt[(j + 1)]=${bt[j]}
            pid[(j + 1)]=${pid[j]}
            j=$((j - 1))
        done
        at[(j + 1)]=$key
        bt[(j + 1)]=$keybt
        pid[(j + 1)]=$keypid
    done
}
# Function to compute the completion time, waiting time, and turn around time
function compute_times {
    local -n at=$1
    local -n bt=$2
    local -n pid=$3
    local -n ct=$4
    local -n wt=$5
    local -n tat=$6
    local n=${#at[@]}
    for ((i = 0; i < n; i++)); do
        wt+=(0)
        tat+=(0)
    done
    ct[0]=${bt[0]}
    tat[0]=${ct[0]}-${at[0]}
    wt[0]=$((${tat[0]} - ${bt[0]}))

    for ((i = 1; i < n; i++)); do
        ct[i]=$((ct[i - 1] + bt[i]))
        tat[i]=$((ct[i] - at[i]))
        wt[i]=$((${tat[i]} - ${bt[i]}))
    done
}

# Function to compute the average waiting time and average turn around time
function compute_averages {
    local -n wt=$1
    local -n tat=$2
    local -n avgwt=$3
    local -n avgtat=$4

    local n=${#wt[@]}
    local sumwt=0
    local sumtat=0

    for ((i = 0; i < n; i++)); do
        sumwt=$((sumwt + wt[i]))
        sumtat=$((sumtat + tat[i]))
    done

    avgwt=$((sumwt / n))
    avgtat=$((sumtat / n))
}

# Function to print the Gantt chart
function print_gantt {
    local -n pid=$1
    local -n ct=$2

    local n=${#pid[@]}
    local gantt=""

    for ((i = 0; i < n; i++)); do
        gantt+="| P${pid[i]} "
    done

    gantt+="|"
    echo "$gantt"
    printf "%-4s" '0'
    for ((i = 0; i <= n; i++)); do
        printf "%-5s" "${ct[i]}"
    done
    echo ""
}
#driver code
echo 'Enter number of processes'
read N
ArrivalTime=()
BurstTime=()
PID=()
CompletionTime=()
WaitingTime=()
TurnAroundTime=()
echo "Enter ARRIVAL-TIME    BURST-TIME      PID for $N processes"
for ((i = 0; i < N; i++)); do
    read A B P
    ArrivalTime+=($A)
    BurstTime+=($B)
    PID+=($P)
done
declare AvgWT AvgTAT
insertion_sort ArrivalTime BurstTime PID
compute_times ArrivalTime BurstTime PID CompletionTime WaitingTime TurnAroundTime
compute_averages WaitingTime TurnAroundTime AvgWT AvgTAT
# print results
echo "ProcessID   ArrivalTime   BurstTime   CompletionTime   WaitingTime   TurnAroundTime"
for ((i = 0; i < N; i++)); do
    echo "${PID[i]}           ${ArrivalTime[i]}              ${BurstTime[i]}            ${CompletionTime[i]}            ${WaitingTime[i]}            ${TurnAroundTime[i]}"
done

echo "Average waiting time: $AvgWT"
echo "Average turnaround time: $AvgTAT"

print_gantt PID CompletionTime
