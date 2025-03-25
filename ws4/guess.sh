random_number=$((RANDOM % 10 + 1))

echo "I'm thinking of a number between 1 and 10. Can you guess it?"
read -p "Enter your guess: " guess

while [ $guess -ne $random_number ]; do
    read -p "Enter your guess: " guess
done

echo "You guessed it! The number was $random_number."
