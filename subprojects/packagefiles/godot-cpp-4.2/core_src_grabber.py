import os
import fnmatch
import sys

def find_cpp_files(directory):
    cpp_files = []
    for root, dirs, files in os.walk(directory):
        for filename in fnmatch.filter(files, '*.cpp'):
            cpp_files.append(os.path.join(root, filename))
    return cpp_files


if __name__ == "__main__":
    files = find_cpp_files(sys.argv[1])

    print(";".join(files))