#!/bin/bash
HEADER_FILE="Breviar/config.build.h"

OLD_HEADER=""
if [[ -f $HEADER_FILE ]]
then
	OLD_HEADER=$(cat $HEADER_FILE)
fi

NEW_HEADER="#define BUILD_NUMBER @\"$(git rev-parse --short HEAD)\""

if [[ "$OLD_HEADER" != "$NEW_HEADER" ]]
then
	echo "Writing $HEADER_FILE"
	echo -n $NEW_HEADER >$HEADER_FILE
fi

