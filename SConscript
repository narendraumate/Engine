Import('env', 'config', 'platform')

import os
import sys

###############################################################################
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
def find_files(cwd, extensions):
    filenames = []
    filenames = recursive_glob(cwd, extensions)
    return filenames
###############################################################################
platform = sys.platform
srcextensions = ('.c', '.cc', '.cpp', '.m', '.mm')
objextensions = ('.o', '.obj')
excludedirs = set()

# platform specific
if platform == 'win32':
    excludedirs |= set(['MacOS', 'Linux'])
elif platform == 'darwin':
    excludedirs |= set(['Windows', 'Linux'])
elif platform == 'linux2':
    excludedirs |= set(['Windows', 'MacOS'])
###############################################################################

# find root directory
root = os.getcwd()

# find src files
srcfilenames = find_files(root, srcextensions)

# for return purposes
objects = []

# generate obj files
for srcfilename in srcfilenames:
    objfilepath = srcfilename.replace(root, '').rsplit('.', 1)[0] + env['OBJSUFFIX']
    objfilename = '#obj/%s/%s' % (config, objfilepath)
    object = env.Object(source=srcfilename, target=objfilename)
    objects.append(object)

# return all compiled objects
Return('objects')

