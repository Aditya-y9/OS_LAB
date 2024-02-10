# switch case to make the user choose the 1. FCFS Scheduling 2. SJF Scheduling (Non-Preemptive and Preemptive) 3. Non- Preemptive Priority Scheduling 4. Round Robin Scheduling

echo "1. FCFS Scheduling"
echo "2. SJF Scheduling (Non-Preemptive and Preemptive)"
echo "3. Non- Preemptive Priority Scheduling"
echo "4. Round Robin Scheduling"

read -p "Enter your choice: " choice

case $choice in
    1) ./fcfs.sh ;;
    2) ./sjf.sh ;;
    3) ./priorityscheduling.sh ;;
    4) ./roundrobin.sh ;;
    *) echo "Invalid choice" ;;
esac