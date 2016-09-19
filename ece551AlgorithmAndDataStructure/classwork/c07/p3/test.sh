#! /bin/bash
	for ((i=1 ; i<27; i++)) 
	 do
		./encrypt $i input.txt >answer.txt
		./breaker answer.txt
	done
