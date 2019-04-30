#!/bin/python3

import os
import subprocess
import argparse
import sys

directories_to_run_through = ["../src/", "../include"]
compile_commands_json_dir = "../"

for directory in directories_to_run_through:
    files_for_clang_tidy = os.listdir(directory)

    for curr_file in files_for_clang_tidy:
        full_path = os.path.join(directory, curr_file)
        print("Running clang-tidy for: ", full_path)

        if '--fix' in sys.argv:
            subprocess.run("clang-tidy -p " + compile_commands_json_dir +\
                " -checks='-*,modernize*' " + full_path + " -header-filter=.* "\
                + "-fix",\
                shell=True)
        else:
            subprocess.run("clang-tidy -p " + compile_commands_json_dir +\
                " -checks='-*,modernize*' " + full_path + " -header-filter=.* ",\
                shell=True)

