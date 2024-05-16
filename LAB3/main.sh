
while :
do
	echo "-------------------------------------"
	echo "       OS LAB3  ALGORITHMS       "
	echo "-------------------------------------"
	echo "1. First Come First Served Algorithm"
	echo "2. Non Pre-emptive Shortest Job First"
	echo "3. Pre-emptive Shortest Job First "
	echo "4. Non Pre-emptive Priority Scheduling"
	echo "5. Round Robin"
	echo "6. Exit/Quit"
	echo "====================================="
	
	echo -n "Enter your menu choice :"
	read input
	
	case $input in
		1) ./fcfs.sh ; read ;;
		2) ./sjfnp.sh ; read ;;
		3) ./sjfp.sh ; read ;;
		4) ./nonpreps.sh ; read ;;
		5) ./rr.sh ; read ;;
		6) exit 0
		echo "Thank you! Bye!";;
		*) echo "Provide a valid input please!" ; read ;;
	esac
done
