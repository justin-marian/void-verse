#!/usr/bin/env python

import subprocess
import shutil
import os
import sys
from collections import namedtuple

# Define constants
BIN_DIR = "BIN"
INPUT_FILE = "INPUTS/"
OUTPUTS_FILE = "OUTPUTS/"
DEV_FILE = "DEV_OUTPUT/"
MEMORY_CHECK_FILE = os.path.join(BIN_DIR, "memCheck")
runExec = os.path.join(BIN_DIR, "main")
inputFileName = os.path.join(BIN_DIR, "input")

size_header = 60

# Define namedtuple for test results
test_tuple = namedtuple("TEST", "name, error")

# Variables to track test results and score
number_tests_passed = 0
number_tests = 0
memory_shame_list = []
memory_score = 20

def calculate_score_without_memory():
    """
    Returns:
        int: The score of the person without memory points
    """
    return (70.0 / number_tests) * number_tests_passed if number_tests_passed > 0 else 0

def calculate_score():
    """
    Returns:
        int: The total score of the person
    """
    score = calculate_score_without_memory()
    return score + (memory_score if len(memory_shame_list) == 0 and score >= 50 else 0)

def create_output_folders():
    if not os.path.exists(OUTPUTS_FILE):
        os.mkdir(OUTPUTS_FILE)

def compile_and_copy_files():
    rc = subprocess.call("make build", shell=True)
    if not os.path.exists(runExec):
        sys.stderr.write(
            "The file %s is missing and could not be created with make" % runExec
        )
        sys.exit(-1)

    if not os.path.exists(INPUT_FILE):
        sys.stderr.write("Could not find the inputs file.....how did you manage that?")
        sys.exit(-1)

def print_test_status(name, passed):
    header = "TEST " + name + "." * (size_header - len(name) - 12)
    if passed:
        print("\033[92m" + header + " PASSED\033[0m")
    else:
        print("\033[91m" + header + " FAILED\033[0m")

def run_tests():
    print("\n=======================================================\n")

    regular_tests = sorted(os.listdir(INPUT_FILE))
    global number_tests
    number_tests = len(regular_tests)

    for name_file in regular_tests:
        shutil.copy(INPUT_FILE + name_file, inputFileName)

        proc = os.popen(
            'valgrind --leak-check=full \
                    --show-leak-kinds=all --track-origins=yes \
                    --log-file="' + MEMORY_CHECK_FILE + '" '
            + runExec
            + " < "
            + inputFileName
        )
        result = proc.read().strip()
        proc.close()
        with open(OUTPUTS_FILE + "output_" + name_file, "w") as f:
            f.write(result)

        with open(DEV_FILE + "dev_" + name_file, "r") as dev:
            test_passed = dev.read().strip() == result
            global number_tests_passed
            if test_passed:
                number_tests_passed += 1
            print_test_status(name_file, test_passed)

        ## memory check
        with open(MEMORY_CHECK_FILE, "r") as mem:
            mem_str = mem.read().strip()
            if "All heap blocks were freed" not in mem_str:
                memory_shame_list.append(test_tuple(name_file, "memory not freed"))
            elif "Invalid read" in mem_str:
                memory_shame_list.append(
                    test_tuple(name_file, "not enough memory allocated string")
                )

def check_memory_results():
    if len(memory_shame_list) == 0 and calculate_score_without_memory() >= 50:
        print("\033[92m" + "Test memory.......................................... PASSED\033[0m")
    elif calculate_score_without_memory() < 50:
        print("\033[91m" + "Test memory.......................................... FAILED" + "\033[0m")
        print("You need at least 50 points to get memory points")
    else:
        print("\033[91m" + "Test memory.......................................... FAILED" + "\033[0m")

    for shame in memory_shame_list:
        print("\033[91m" + "Failed Test: " + shame.name + "-- probable problem: " + shame.error + "\033[0m")

def display_final_score():
    print(
        "\n======================= Score ======================= " + str(calculate_score()) + "p/90\n"
    )

def cleanup():
    if os.path.exists(MEMORY_CHECK_FILE):
        os.remove(MEMORY_CHECK_FILE)
    if os.path.exists("input"):
        os.remove("input")

    subprocess.call("make clean", shell=True)

def main():
    create_output_folders()
    compile_and_copy_files()
    run_tests()
    check_memory_results()
    display_final_score()
    cleanup()

if __name__ == "__main__":
    main()
