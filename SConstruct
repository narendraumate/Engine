import os
import sys

# global
platform = sys.platform

# base
base_env = Environment()
base_env.VariantDir('obj', '.', duplicate=0)

# platform specific
if platform == 'win32':
	pass
elif platform == 'darwin':
	base_env.Append(FRAMEWORKS = ['Cocoa', 'OpenGL', 'QuartzCore'])
elif platform == 'linux2':
	base_env.Append(LIBS = ['-lGL', '-lGLU'])

# debug
debug_env = base_env.Clone()
debug_env.Append(CPPDEFINES=['DEBUG'])
debug_env.Append(CCFLAGS=['-g'])

# release
release_env = base_env.Clone()
release_env.Append(CPPDEFINES=['NDEBUG'])
release_env.Append(CCFLAGS=['-O2'])

# create environments list
env_config_list = []
env_config_list.append((debug_env, 'debug'))
env_config_list.append((release_env, 'release'))

# run all environments
for env, config in env_config_list:
	env.SConscript('obj/SConscript', exports=['env', 'config', 'platform'])
	env.Clean('.', 'obj')
	env.Clean('.', 'bin')

