#!/bin/bash
file_path=$1
text=$(<"$file_path")
text_to_be_replaced=$2
text_for_replacement=$3
edited_text=$(echo "$text" | sed "s/$text_to_be_replaced/$text_for_replacement/g")
echo "$edited_text" > history_of_vim.txt
