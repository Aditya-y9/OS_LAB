#!/bin/bash
#Take user input for
# arrival time,
# burst time,
# priority
echo -n 'Enter number of processes:'
read N
declare -a arrival_time burst_time pid completion_time waiting_time tat
declare AvgWT AvgTat
echo -e "\nEnter the Arrival Time and Burst Time:\n"
for ((i = 0; i < N; i++)); do
    echo -n "p$((i + 1)): "
    read arrival_time[i]
    read burst_time[i]
    pid[i]=$((i + 1))
done
function insertion_sort_arrival {
    local -n at=$1
    local -n bt=$2
    local -n p_id=$3
    local i j key keybt keypid
    for ((i = 1; i < ${#at[@]}; i++)); do
        key=${at[i]}
        keybt=${bt[i]}
        keypid=${p_id[i]}
        j=$((i - 1))
        while ((j >= 0 && at[j] > key)); do
            at[(j + 1)]=${at[j]}
            bt[(j + 1)]=${bt[j]}
            p_id[(j + 1)]=${p_id[j]}
            j=$((j - 1))
        done
        at[(j + 1)]=$key
        bt[(j + 1)]=$keybt
        p_id[(j + 1)]=$keypid
    done
}
function insertion_sort_pid {
    local -n at=$1
    local -n bt=$2
    local -n p_id=$3
    local -n ct=$4
    local -n wt=$5
    local -n t_at=$6
    local i j key keybt keypid
    for ((i = 1; i < ${#at[@]}; i++)); do
        key=${at[i]}
        keybt=${bt[i]}
        keypid=${p_id[i]}
        keyct=${ct[i]}
        keywt=${wt[i]}
        keytat=${t_at[i]}
        j=$((i - 1))
        while ((j >= 0 && p_id[j] > keypid)); do
            at[(j + 1)]=${at[j]}
            bt[(j + 1)]=${bt[j]}
            p_id[(j + 1)]=${p_id[j]}
            wt[(j + 1)]=${wt[j]}
            ct[(j + 1)]=${ct[j]}
            t_at[(j + 1)]=${t_at[j]}
            j=$((j - 1))
        done
        at[(j + 1)]=$key
        bt[(j + 1)]=$keybt
        p_id[(j + 1)]=$keypid
        wt[(j + 1)]=$keywt
        ct[(j + 1)]=$keyct
        t_at[(j + 1)]=$keytat
    done
}
function CheckComplete {
    local -n complete=$1 b_t=$2
    for i in "${b_t[@]}"; do
        ((complete += i))
    done
}
function SJF {
    local -n at=$1 bt=$2 ct=$3 p_id=$4
    local -i check_complete clock_cycle index currentpid lastpid gantt
    local -a gantt_times
    clock_cycle=0
    lastpid=0
    gantt_times[0]=0
    gantt=1
    echo -n "|"
    while true; do
        check_complete=0
        CheckComplete check_complete bt
        if [ ${check_complete} -le 0 ]; then
            echo -n -e "\tP${lastpid}\t|"
            gantt_times[${gantt}]=$((${clock_cycle}))
            break
        fi
        ((clock_cycle++))
        local minimum=9999
        for ((i = 0; i < N; i++)); do
            if [ ${at[i]} -lt ${clock_cycle} ] && [ ${bt[i]} -lt ${minimum} ] && [ ${bt[i]} -gt 0 ]; then
                minimum=${bt[i]}
                index=$i
                currentpid=${p_id[i]}
            fi
        done
        if [ ${lastpid} -ne ${currentpid} ]; then
            if [ ${lastpid} -ne 0 ]; then
                # echo -n -e "\tP${currentpid}\t|"
                # gantt_times[${gantt}]=$((${clock_cycle} - 1))
                # ((gantt++))
                # else
                echo -n -e "\tP${lastpid}\t|"
                gantt_times[${gantt}]=$((${clock_cycle} - 1))
                ((gantt++))
            fi
            lastpid=${currentpid}
        fi
        ((bt[${index}]--))
        if [ ${bt[${index}]} -eq 0 ]; then
            ct[${index}]=${clock_cycle}
        fi
    done
    echo -n -e "\n${gantt_times[0]}\t"
    for ((i = 1; i < ${#gantt_times[@]}; i++)); do
        echo -n -e "\t${gantt_times[i]}\t"
    done
    echo -e "\n"
}
function WaitingTime_TurnAroundTime {

    local -n wt=$1 ct=$2 at=$3 bt=$4 t_at=$5

    for ((i = 0; i < N; i++)); do
        t_at[i]=$((ct[i] - at[i]))
        wt[i]=$((t_at[i] - bt[i]))

    done
}
function print_results {
    local -n p_id=$1 at=$2 bt=$3 wt=$4 t_at=$5 ct=$6
    echo -e "\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time"
    for ((i = 0; i < ${#pid[@]}; i++)); do
        echo -e "${p_id[i]}\t\t${at[i]}\t\t${bt[i]}\t\t${ct[i]}\t\t${wt[i]}\t\t${t_at[i]}"
    done
}
function compute_averages {
    local -n wt=$1
    local -n t_at=$2
    local -n avgwt=$3
    local -n avgtat=$4
    local n=${#wt[@]}
    local sumwt=0
    local sumtat=0
    for ((i = 0; i < n; i++)); do
        sumwt=$((sumwt + wt[i]))
        sumtat=$((sumtat + t_at[i]))
    done
    avgwt=$((sumwt / n))
    avgtat=$((sumtat / n))
}
# sort according to arrival_time
insertion_sort_arrival arrival_time burst_time pid
burst_time_reserve=("${burst_time[@]}")
SJF arrival_time burst_time completion_time pid
WaitingTime_TurnAroundTime waiting_time completion_time arrival_time
burst_time_reserve tat
insertion_sort_pid arrival_time burst_time_reserve pid completion_time
waiting_time tat
print_results pid arrival_time burst_time_reserve waiting_time tat
completion_time
compute_averages waiting_time tat AvgWT AvgTat
echo "Average waiting time: $AvgWT"
echo "Average turnaround time: $AvgTat"
