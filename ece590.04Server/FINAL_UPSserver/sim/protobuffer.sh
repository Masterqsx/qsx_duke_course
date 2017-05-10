#! /bin/sh
SRC_DIR=$1
DST_DIR=$2
PROTO_FILE=$3
protoc --python_out=${DST_DIR} ${SRC_DIR}/${PROTO_FILE}
