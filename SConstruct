import os
import sys

# global
platform = sys.platform

# base
base_env = Environment()

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
debug_env.Append(OBJPREFIX=['debug/'])
debug_env.VariantDir('bin/debug', '.', duplicate=0)

# release
release_env = base_env.Clone()
release_env.Append(CPPDEFINES=['NDEBUG'])
release_env.Append(CCFLAGS=['-O2'])
release_env.Append(OBJPREFIX=['release/'])
release_env.VariantDir('bin/release', '.', duplicate=0)

# list
env_config_list = []
env_config_list.append((debug_env, 'debug'))
env_config_list.append((release_env, 'release'))

for env, config in env_config_list:
	env.SConscript('bin/%s/SConscript' % config, exports=['env', 'config', 'platform'])
