#!/bin/bash

make re

RED=`tput setaf 1`
GREEN=`tput setaf 2`
BASE=`tput setaf 7`
FAILS=0
SUCCESS=0
COUNTER=0
LEAKS=0

flags=(
    "b"
    "e"
    "n"
    "s"
    "t"
    "v"
)

test_files=(
    "../common/test_files/1.txt" # normal text
    "../common/test_files/2.txt" # non-printable characters
    "../common/test_files/3.txt" # empty file
    "../common/test_files/4" # binary file
)

# Generate combinations of concatenated flags
generate_flag_combinations() {
    combinations=()
    local size=${#flags[@]}
    for ((i = 0; i < (1 << size); i++)); do
        combination="-"
        for ((j = 0; j < size; j++)); do
            if ((i & (1 << j))); then
                combination+="${flags[j]}"
            fi
        done
        combinations+=("$combination")
    done
}

# Run the tests
run_tests() {
    generate_flag_combinations

    # Create a directory for diffs
    mkdir -p diffs

    for file in "${test_files[@]}"; do
        if [[ ! -f "$file" ]]; then
            echo "Skipping test for '$file' (file not found)"
            continue
        fi

        for combination in "${combinations[@]}"; do
            let "COUNTER++"
            if [[ "$combination" == "-" ]]; then
                continue  # Skip empty combination
            fi

            # Run real cat and your implementation
            real_output="real_cat_output.txt"
            s21_output="s21_cat_output.txt"
            cat $combination "$file" > "$real_output"
            ./s21_cat $combination "$file" > "$s21_output"

            # Prepare diff directory and filename
            file_name=$(basename "$file")
            diff_file="diffs/diff_${file_name}_${combination// /_}.txt"

            # Create the directory if it doesn't exist
            mkdir -p "$(dirname "$diff_file")"

            # Compare outputs
            if diff -q "$real_output" "$s21_output" > /dev/null; then
                echo "[${GREEN}${SUCCESS}${BASE}/${RED}${FAILS}${BASE}]${GREEN}Test passed for: cat $combination $file${BASE}"
                let "SUCCESS++"
            else
                echo "[${GREEN}${SUCCESS}${BASE}/${RED}${FAILS}${BASE}]${RED}Test failed for: cat $combination $file${BASE}"
                diff "$real_output" "$s21_output" > "$diff_file"
                echo "Diff saved to $diff_file"
                let "FAILS++"
            fi

            # Memory leak check with Valgrind
            valgrind --leak-check=full --error-exitcode=1 ./s21_cat $combination "$file" > /dev/null 2>&1
            if [[ $? -ne 0 ]]; then
                echo "[${GREEN}${SUCCESS}${BASE}/${RED}${FAILS}${BASE}/${RED}${LEAKS}${BASE}]${RED}Memory leak found for: cat $combination $file${BASE}"
                let "LEAKS++"
            fi

            # Clean up temporary files
            rm "$real_output" "$s21_output"
        done
    done
}

# Main function to run all tests
main() {
    echo "Running tests for s21_cat implementation..."
    run_tests

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
