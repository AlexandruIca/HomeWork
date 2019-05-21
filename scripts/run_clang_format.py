#!/bin/python3

import os
import subprocess
# pip3 install colorama
import colorama
from typing import List

def absolute_path(path: str) -> str:
    return os.path.abspath(path)

def join(path1: str, path2: str) -> str:
    return os.path.join(path1, path2)

parent_dir: str = absolute_path("../")
#directories_to_run_through: List[str] =\
        #[join(parent_dir, "src/"), join(parent_dir, "include/")]
directories_to_run_through: List[str] =\
        [join(parent_dir, directory) for directory in ["include/", "src/", "tests/"]]

colorama.init()

for directory in directories_to_run_through:
    files_for_clang_format: List[str] = os.listdir(directory)

    for curr_file in files_for_clang_format:
        full_path: str = join(directory, curr_file)
        print(colorama.Fore.CYAN, end="")
        print("Running clang-format for: ", end="")
        print(colorama.Fore.YELLOW, full_path, colorama.Fore.RESET)
        subprocess.run("clang-format -i " + full_path, shell=True)

colorama.deinit()

