#!/bin/bash

cnt=0
j=0
n=0
t=0
remain=0
flag=0
tq=0
wt=0
tat=0
context_switches=0

declare -a at bt rt

echo -n "Enter Total Process: "
read n

remain=$n

for ((cnt = 0; cnt < n; cnt++)); do
    echo -n "Enter Arrival Time and Burst Time for Process Process Number $((cnt + 1)): "
    read at[cnt]
    read bt[cnt]
    rt[cnt]=${bt[cnt]}
done

echo -n "Enter Time Quantum: "
read tq

echo -e "\n\nProcess\t|Turnaround Time|Waiting Time\n\n"

for ((t = 0, cnt = 0; remain != 0; )); do
    if ((rt[cnt] <= tq && rt[cnt] > 0)); then
        t=$((t + rt[cnt]))
        rt[cnt]=0
        flag=1
    elif ((rt[cnt] > 0)); then
        rt[cnt]=$((rt[cnt] - tq))
        t=$((t + tq))
        ((context_switches++))
    fi
    if ((rt[cnt] == 0 && flag == 1)); then
        remain=$((remain - 1))
        echo "P[$((cnt + 1))]" $'\t|\t' "$((t - at[cnt]))" $'\t|\t' "$((t - at[cnt] - bt[cnt]))"
        wt=$((wt + t - at[cnt] - bt[cnt]))
        tat=$((tat + t - at[cnt]))
        flag=0
    fi

    if ((cnt == n - 1)); then
        cnt=0
    elif ((at[cnt + 1] <= t)); then
        cnt=$((cnt + 1))
    else
        cnt=0
    fi
done

echo -e "\nAverage Waiting Time= $(awk 'BEGIN {printf "%.2f", '$wt'/'$n'}')"

echo -e "\nAvg Turnaround Time = $(awk 'BEGIN {printf "%.2f", '$tat'/'$n'}')"

echo -e "\nNumber of Context Switches: $context_switches"

exit 0
