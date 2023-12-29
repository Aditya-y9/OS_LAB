#!/bin/bash

declare -a burst_time at gantt_times
sum_burst_time=0
smallest=9
sumt=0
sumw=0
current_time=0

read -p "enter the no of processes: " n

for ((i = 0; i < n; i++)); do
    read -p "the arrival time for process P$((i + 1)): " at[i]
    read -p "the burst time for process P$((i + 1)): " burst_time[i]
    sum_burst_time=$((sum_burst_time + burst_time[i]))
done

burst_time[9]=9999

echo "Gantt Chart"
echo "-----------"

while ((current_time < sum_burst_time)); do
    smallest=9
    for ((i = 0; i < n; i++)); do
        if ((at[i] <= current_time && burst_time[i] > 0 && burst_time[i] < burst_time[smallest])); then
            smallest=$i
        fi
    done

    gantt_times+=("$current_time")
    current_time=$((current_time + burst_time[smallest]))
    gantt_times+=("$current_time")

    printf "| P%d " $((smallest + 1))

    sumt=$((sumt + current_time - at[smallest]))
    sumw=$((sumw + current_time - at[smallest] - burst_time[smallest]))

    burst_time[smallest]=0
done

echo "|"

echo -e "\n\n average waiting time = $(awk "BEGIN {printf \"%.2f\", $sumw/$n}")"
echo -e "\n\n average turnaround time = $(awk "BEGIN {printf \"%.2f\", $sumt/$n}")"

exit 0
