#!/bin/bash 

# return the number of districts for which a name met the criteria for inclusion

# Standard argument parsing code. 
# This script should be called with two arguments
# 1) The path to Baby_Names__Beginning_2007.csv.
# 2) The name we are trying to count
if [ "$#" -ne 2 ]
then 
  echo "$0" "is excpecting 2 arguments - the path to the data file and the name to lookup."
  echo "Example Usage: bash HowManyCounties.sh Baby_Names__Beginning_2007.csv ABIGAIL"
  exit 2
fi 

FILE_NAME=$1; 
CHILD_NAME=$2; 

# Complete by filling out the next few lines using any set of POSIX UNIX commands to 
# find out in how many counties the name Abigail was popular 
# enough to be include in this dataset.

echo `grep 2007,${CHILD_NAME}, ${FILE_NAME} | cut -d, -f3 | sort | uniq | wc -l`
