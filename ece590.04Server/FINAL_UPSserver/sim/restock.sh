#!/bin/bash

world="$1"
if [ "$world" == "" ]
then
    echo "You need to specify a world"
    exit 1
fi

echo "update whstock set num = num + 10000 WHERE num < 20000;" | psql packagesim
