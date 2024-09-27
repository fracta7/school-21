#!/bin/bash

RED=`tput setaf 1`
GREEN=`tput setaf 2`
BASE=`tput setaf 7`
FAILS=0
SUCCESS=0
COUNTER=0
LEAKS=0  # Variable to track memory leaks

make re

# Define the grep flags to test, excluding -e since it will always be included
flags=(
    "i"  # Ignore case
    "v"  # Invert match
    "c"  # Count matches
    "l"  # List matching files
    "n"  # Show line numbers
    "s"  # Suppress error messages
    "h"  # Suppress filenames in output
    "o"
)

# Define the test files
test_files=(
    "../common/test_files/1.txt" # normal text
    "../common/test_files/3.txt" # empty file
    "../common/test_files/source_code.txt"
)

# Define the pattern to search for
pattern="text"

# Generate a random combination of flags
generate_random_flags() {
    local size=${#flags[@]}
    local num_flags=$((RANDOM % size + 1)) # Random number of flags to include
    local selected_flags=()

    # Randomly select flags
    while [[ ${#selected_flags[@]} -lt $num_flags ]]; do
        local flag=${flags[$((RANDOM % size))]}
        if [[ ! " ${selected_flags[@]} " =~ " ${flag} " ]]; then
            selected_flags+=("$flag")
        fi
    done

    # Concatenate the selected flags
    echo "-e ${pattern} ${selected_flags[@]/#/-}"
}

# Run the tests
run_tests() {
    mkdir -p diffs

    for file in "${test_files[@]}"; do
        let "COUNTER++"
        if [[ ! -f "$file" ]]; then
            echo "Skipping test for '$file' (file not found)"
            continue
        fi

        # Generate a random flag combination
        combination=$(generate_random_flags)

        # Run real grep and your implementation
        real_output="real_grep_output.txt"
        s21_output="s21_grep_output.txt"
        
        # Run both greps with the generated flag combinations and the specified pattern
        grep $combination "$file" > "$real_output" 2>/dev/null
        ./s21_grep $combination "$file" > "$s21_output" 2>/dev/null

        # Prepare diff directory and filename
        file_name=$(basename "$file")
        diff_file="diffs/diff_${file_name}_${combination// /_}.txt"

        # Create the directory if it doesn't exist
        mkdir -p "$(dirname "$diff_file")"

        # Compare outputs
        if diff -q "$real_output" "$s21_output" > /dev/null; then
            echo "[${GREEN}${SUCCESS}${BASE}/${RED}${FAILS}${BASE}/${RED}${LEAKS}${BASE}]${GREEN}Test passed for: grep $combination $file${BASE}"
            let "SUCCESS++"
        else
            echo "[${GREEN}${SUCCESS}${BASE}/${RED}${FAILS}${BASE}/${RED}${LEAKS}${BASE}]${RED}Test failed for: grep $combination $file${BASE}"
            diff "$real_output" "$s21_output" > "$diff_file"
            echo "Diff saved to $diff_file"
            let "FAILS++"
        fi

        # Memory leak check with Valgrind
        valgrind --leak-check=full --error-exitcode=1 ./s21_grep $combination "$file" > /dev/null 2>&1
        if [[ $? -ne 0 ]]; then
            echo "[${GREEN}${SUCCESS}${BASE}/${RED}${FAILS}${BASE}/${RED}${LEAKS}${BASE}]${RED}Memory leak found for: grep $combination $file${BASE}"
            let "LEAKS++"
        fi

        # Clean up temporary files
        rm "$real_output" "$s21_output"
    done
}

# Main function to run all tests 25 times
main() {
    echo "Running tests for s21_grep implementation 25 times..."

    # Loop to run tests 25 times
    for i in {1..25}; do
        echo "Test iteration: $i"
        run_tests
    done
    echo ""
    echo "##########################"
    echo "#                        #"
    echo "#   Testing complete     #"
    echo "#                        #"
    echo "##########################"
    echo ""
    echo "${GREEN}SUCCESSFUL:${SUCCESS}${BASE}"
    echo "${RED}UNSUCCESSFUL:${FAILS}${BASE}"
    echo "${RED}LEAKS FOUND:${LEAKS}${BASE}"
    echo "${GREEN}TOTAL:${COUNTER}${BASE}"
}

# Run the main function
main
