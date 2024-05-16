echo "Enter the first number:"
read num1

echo "Enter the operation (+, -, x, /):"
read op

echo "Enter the second number:"
read num2

if [ "$op" == "+" ]; then
  echo "Your Answer is: $num1 $op $num2 = $(($num1 + $num2))"
elif [ "$op" == "-" ]; then
  echo "Your Answer is: $num1 $op $num2 = $(($num1 - $num2))"
elif [ "$op" == "x" ]; then
  echo "Your Answer is: $num1 $op $num2 = $(($num1 * $num2))"
elif [ "$op" == "/" ]; then
  if [ "$num2" -eq 0 ]; then
    echo "Error: Division by zero is not allowed."
  else
    echo "Your Answer is: $num1 $op $num2 = $(($num1 / $num2))"
  fi
else
  echo "Incorrect operator. Please use +, -, x, or /."
fi
