#! /bin/bash


NUM_PLAYERS=$1
NUM_HOPS=$2

./ringmaster $NUM_PLAYERS $NUM_HOPS &

sleep 2

for (( i=0; i<$NUM_PLAYERS; i++ ))
do
  ./player $i &
done

wait

