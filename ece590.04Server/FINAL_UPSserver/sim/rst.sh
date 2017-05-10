#!/bin/bash

world="$1"
if [ "$world" == "" ]
then
    echo "You need to specify a world"
    exit 1
fi

echo "delete from truckhas where wid=${world}; delete from shipments where wid=${world}; delete from whready where wid=${world}; delete from deliveries where wid=${world}; update trucks set trstate=1, statechange='infinity'::timestamp where wid=${world};" | psql packagesim
