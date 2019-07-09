#!/bin/python3

# pip3 install colorama
import colorama
import common
import subprocess
import sys

colorama.init()

def callback(file_path: str):
    print(colorama.Fore.CYAN, end="")
    print("Running clang-tidy for: ", end="")
    print(colorama.Fore.YELLOW + file_path, end="")
    print(colorama.Fore.RESET)

    if '--fix' in sys.argv:
        subprocess.run("clang-tidy -header-filter=.* -p ../ " + file_path + "-fix", shell=True)
    else:
        subprocess.run("clang-tidy -header-filter=.* -p ../ " + file_path, shell=True)

common.walk_through_files(callback)

colorama.deinit()

