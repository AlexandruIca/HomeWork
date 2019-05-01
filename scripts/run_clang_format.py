#!/bin/python3

import os
import subprocess

directories_to_run_through = ["../src/", "../include"]

for directory in directories_to_run_through:
    files_for_clang_tidy = os.listdir(directory)

    for curr_file in files_for_clang_tidy:
        full_path = os.path.join(directory, curr_file)
        print("Running clang-format for: ", full_path)
        subprocess.run("clang-format -i " + full_path, shell=True)

