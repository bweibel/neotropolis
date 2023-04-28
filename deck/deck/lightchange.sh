#!/bin/bash

# Set up the serial port
# You may need to change /dev/cu.usbserial-A703EYMX to the correct port for your Arduino
PORT=/dev/cu.usbserial-A703EYMX
BAUD=9600

# Check if the port is already in use
if lsof $PORT > /dev/null; then
    echo "$PORT is busy. Please close any applications that may be using it and try again."
    exit 1
fi

# Set up the serial port with stty
stty -f $PORT cs8 $BAUD ignbrk -brkint -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts

# Open the serial port with cat in the background
cat $PORT > /dev/null &
CAT_PID=$!

# Loop waiting for user input
while true; do
    # Prompt the user
    echo "Enter a character to send to the Arduino, or 'q' to quit:"
    read input

    # Check if the user wants to quit
    if [[ "$input" == "q" ]]; then
        break
    fi

    # Send the input to the Arduino
    echo -n "$input" > $PORT
done

# Kill the cat process when done
kill $CAT_PID
