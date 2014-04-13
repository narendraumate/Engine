Import('env', 'build', 'platform')

import os
import sys

platform = sys.platform
extensions = ('.c', '.cc', '.cpp')
excludedirs = set()

# HARDCODING BEGINS
excludedirs |= set(["assimp", "DevIL", "glsw"])
excludedirs |= set(["src-IL", "src-ILU", "src-ILUT"])
# HARDCODING ENDS

# platform specific
if platform == "win32":
    excludedirs |= set(["MacOS", "Linux"])
elif platform == "darwin":
    extensions += ('.m', '.mm')
    excludedirs |= set(["Windows", "Linux"])
elif platform == "linux2":
    excludedirs |= set(["Windows", "MacOS"])

# source Files
def recursive_glob(pathname):
    # Recursively look for files ending with extensions.
    # Return a list of matching files.
    matches = []
    for dirpath, dirnames, filenames in os.walk(pathname, topdown=True):
        dirnames[:] = [d for d in dirnames if d not in excludedirs]
        for filename in filenames:
             if filename.endswith(extensions):
                 matches.append(os.path.join(dirpath, filename))
    return matches

# source Files
def find_files():
    cwd = os.getcwd()
    file_list = []
    file_list = recursive_glob(cwd)
    return file_list

# program
env.Program('Application', find_files())
