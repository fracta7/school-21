#!/bin/bash

path=$1
number_of_lines=$(wc -l < $path)

declare -A unique_entries
declare -A unique_hashes

while IFS= read -r line; do
	file_path="${line%% *}"
	unique_entries["$file_path"]=1

	IFS=' - ' read -r -a fields <<< "$line"
        hash="${field[3]}"
	unique_hashes["$hash"]=1
done < "$path"

number_of_unique_entries=${#unique_entries[@]}
number_of_unique_hashes=${#unique_hashes[@]}

echo "$number_of_lines $number_of_unique_entries $number_of_unique_hashes"
