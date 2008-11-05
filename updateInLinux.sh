#!/bin/bash

OP_PATH=/14.5.A/models/std/
MANET_PATH=$OP_PATH/manet
INCLUDE_PATH=$OP_PATH/include

echo "updating the repository..."
svn update

echo "copying necessary files..."
cp OPNET/$MANET_PATH/* $MANET_PATH
cp OPNET/$INCLUDE_PATH/* $INCLUDE_PATH

echo "making temporary tmp folder under tmp..."
mkdir /tmp/tmp

echo "remember to update manually the function block and state variables!!!"
