#!/usr/bin/bash

for folder in `ls scan/ -1`
do
	yodamerge scan/$folder/run* -o scan/$folder/merged_4params.yoda
	rm scan/$folder/job scan/$folder/run*
done
