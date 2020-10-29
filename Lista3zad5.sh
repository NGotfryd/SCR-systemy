#!/bin/bash

trap 'echo "Jestem odporny na SIGINT"' INT
trap 'echo "Jestem odporny na SIGQUIT"' QUIT
trap 'echo "Jestem odporny na SIGFPE"' FPE
trap 'echo "Jestem odporny na SIGILL"' ILL


while true; do
	date
	sleep 5
done
