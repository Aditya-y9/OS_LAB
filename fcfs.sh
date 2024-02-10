#!/bin/bash

# Initialize variables
current_time=0
start_column=1
total_waiting_time=0
total_process_time=0
num_processes=0

# Clear the console
clear

# Set text color to green
echo -e "\033[32m"

# Prompt the user to enter the number of processes
echo -n "Enter the number of processes: "
read num_processes

# Initialize arrays to store process information
declare -a process_name
declare -a arrival_time
declare -a process_time

# Get user input for each process
for ((i = 0; i < num_processes; i++)); do
    echo -n "Enter Process Name for Process $((i+1)): "
    read process_name[i]

    echo -n "Enter Arrival Time for Process $((i+1)): "
    read arrival_time[i]

    echo -n "Enter Process Time for Process $((i+1)): "
    read process_time[i]
done

# Reset text color to default
echo -e "\033[0m"

# Loop through each process and print its Gantt chart

current_row=3
total_waiting_time=0
total_processing_time=0
current_process=0
current_time=0
waiting_time=0

for ((i = 0; i < num_processes; i++)); do
    # Display current process name
    tput cup $current_row 2
    echo ${process_name[i]}

    # Display process start time
    tput cup $current_row 17
    echo ${arrival_time[i]}

    # Display process running time
    tput cup $current_row 32
    echo ${process_time[i]}

    # Calculate waiting time
    waiting_time=$((current_time - arrival_time[i]))

    # Display waiting time
    tput cup $current_row 47
    echo $waiting_time

    # Display Gantt chart
    tput cup $((last_row + 5 + current_process)) ${arrival_time[i]}
    echo -e "\033[48;5;208m \033[0m"
    sleep 1

    for ((j = 1; j <= waiting_time; j++)); do
        tput cup $((last_row + 5 + current_process)) $((arrival_time[i] + j))
        echo -e "\033[48;5;226m \033[0m"
        #sleep 1
    done

    for ((j = 1; j <= process_time[i]; j++)); do
        tput cup $((last_row + 2)) $((total_processing_time + j))
        echo $(((current_time + j) / 10))
        tput cup $((last_row + 3)) $((total_processing_time + j))
        echo $(((current_time + j) % 10))

        tput cup $((last_row + 4)) $((total_processing_time + j))
        echo ${process_name[i]}
        tput cup $((last_row + 5 + current_process)) $((total_processing_time + j))
        echo -e "\033[48;5;28m \033[0m"
        sleep 1
    done

    # Update current time and total times
    current_time=$((arrival_time[i] + process_time[i] + waiting_time))
    total_waiting_time=$((total_waiting_time + waiting_time))
    total_processing_time=$((total_processing_time + process_time[i]))

    # Display running time
    tput cup $current_row 62
    echo $total_processing_time

    ((current_process++))
    ((current_row++))
done

# Calculate average waiting time and average process time
avg_waiting_time=$(echo "scale=2; $total_waiting_time / $num_processes" | bc -l)
avg_process_time=$(echo "scale=2; $total_processing_time / $num_processes" | bc -l)

# Move cursor to row 3, column 86
tput cup 3 86
# Write Average Waiting Time
echo $avg_waiting_time

# Move cursor to row 3, column 109
tput cup 3 109
# Write Average Process Time
echo $avg_process_time

tput cup $((last_row + last_row + 6)) 1
