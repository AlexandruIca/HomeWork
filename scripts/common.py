import os
from typing import List, Callable

def absolute_path(path: str) -> str:
    return os.path.abspath(path)

def join(path1: str, path2: str) -> str:
    return os.path.join(path1, path2)

def valid_file(file_path: str) -> bool:
    if file_path.endswith(".cpp") or file_path.endswith(".hpp"):
        return True
    return False

def walk_through_files(callback: Callable[[str], None]):
    parent_dir: str = absolute_path("../")
    directories_to_run_through: List[str] =\
            [join(parent_dir, directory) for directory in ["include/", "src/", "tests/"]]

    for directory in directories_to_run_through:
        files_for_clang_format: List[str] = os.listdir(directory)

        for curr_file in files_for_clang_format:
            full_path: str = join(directory, curr_file)

            if valid_file(full_path):
                callback(full_path)

