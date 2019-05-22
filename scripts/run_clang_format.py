#!/bin/python3

# pip3 install colorama
import colorama
import common
import subprocess

colorama.init()

def callback(file_path: str):
    print(colorama.Fore.CYAN, end="")
    print("Running clang-format for: ", end="")
    print(colorama.Fore.YELLOW, file_path, colorama.Fore.RESET)
    subprocess.run("clang-format -i " + file_path, shell=True)

common.walk_through_files(callback)

colorama.deinit()

