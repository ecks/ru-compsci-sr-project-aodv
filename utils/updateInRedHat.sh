#!/bin/sh
# Authors: Hristo Asenov & Remo Cocco

OP_PATH=/usr/opnet/15.0.A/models/std
MANET_PATH=$OP_PATH/manet
IP_PATH=$OP_PATH/ip
INCLUDE_PATH=$OP_PATH/include

OP_PATH_SVN=14.5.A/models/std
MANET_PATH_SVN=$OP_PATH_SVN/manet
IP_PATH_SVN=$OP_PATH_SVN/ip
INCLUDE_PATH_SVN=$OP_PATH_SVN/include

#set -x

svn update

cp OPNET/$MANET_PATH_SVN/* $MANET_PATH
cp OPNET/$IP_PATH_SVN/* $IP_PATH
cp OPNET/$INCLUDE_PATH_SVN/* $INCLUDE_PATH

#set +x

echo "remember to update manually the function block and state variables!!!"
