Import('env')
import os

platform = "Windows"
extensions = ('.h', '.hh', '.hpp', '.c', '.cc', '.cpp')

excludedirs = set()
excludedirs |= set(["assimp", "DevIL", "glsw"])
excludedirs |= set(["src-IL", "src-ILU", "src-ILUT"])

if platform == "Windows":
	excludedirs |= set(["MacOS", "Linux"])
elif platform == "MacOS":
	excludedirs |= set(["Windows", "Linux"])
elif platform == "Linux":
	excludedirs |= set(["Windows", "MacOS"])

def RecursiveGlob(pathname):
    # Recursively look for files ending with extensions.
    # Return a list of matching files/directories.
    matches = []
    for dirpath, dirnames, filenames in os.walk(pathname, topdown=True):
        dirnames[:] = [d for d in dirnames if d not in excludedirs]
        for filename in filenames:
             if filename.endswith(extensions):
                 matches.append(os.path.join(dirpath, filename))
    return matches

def find_files():
    cwd = os.getcwd()
    file_list = []
    file_list = RecursiveGlob(cwd)
    return file_list

Program('Application', find_files())
