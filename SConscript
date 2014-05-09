Import('env', 'config', 'platform')

import os
import sys

platform = sys.platform
srcextensions = ('.c', '.cc', '.cpp')
excludedirs = set()

# HARDCODING BEGINS
excludedirs |= set(["assimp", "DevIL", "glsw"])
excludedirs |= set(["src-IL", "src-ILU", "src-ILUT"])
# HARDCODING ENDS

# platform specific
if platform == "win32":
    excludedirs |= set(["MacOS", "Linux"])
elif platform == "darwin":
    srcextensions += ('.m', '.mm')
    excludedirs |= set(["Windows", "Linux"])
elif platform == "linux2":
    excludedirs |= set(["Windows", "MacOS"])

# recursive search
def recursive_glob(pathname, extensions):
    # Recursively look for files ending with extensions.
    # Return a list of matching files.
    matches = []
    for dirpath, dirnames, filenames in os.walk(pathname, topdown=True):
        dirnames[:] = [d for d in dirnames if d not in excludedirs]
        for filename in filenames:
             if filename.endswith(extensions):
                 matches.append(os.path.join(dirpath, filename))
    return matches

# find files
def find_files(extensions):
    cwd = os.getcwd()
    filenames = []
    filenames = recursive_glob(cwd, extensions)
    return filenames

# generate obj files
srcfilenames = find_files(srcextensions)
objfilenames = []
cwd = os.getcwd()

for srcfilename in srcfilenames:
    objfilepath = srcfilename.replace(cwd, '').rsplit(".", 1)[0] + env['OBJSUFFIX']
    objfilename = '#/obj/%s/%s' % (config, objfilepath)
    objfilenames.append(objfilename)
    env.Object(source=srcfilename, target=objfilename)

# generate bin files
target = env.Program('#/bin/%s/Application' % config, objfilenames)

