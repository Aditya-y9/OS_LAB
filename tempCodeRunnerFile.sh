echo -n 'Enter number of processes:'
read N
declare -a arrival_time burst_time pid completion_time waiting_time tat
declare AvgWT AvgTat