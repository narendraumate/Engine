import os
import sys

# global
platform = sys.platform

# base
base_env = Environment()
base_env.Append(CPPDEFINES=['ASSIMP_BUILD_BOOST_WORKAROUND', 'ASSIMP_BUILD_NO_OWN_ZLIB'])

# platform specific
if platform == 'win32':
	pass
elif platform == 'darwin':
	base_env.Append(CCFLAGS = ['-fgnu89-inline']) # hack for DevIL
	base_env.Append(FRAMEWORKS = ['Cocoa', 'OpenGL', 'QuartzCore'])
elif platform == 'linux2':
	base_env.Append(LINKFLAGS = ['-L/usr/lib/nvidia-331/']) # hack for ubuntu 14.04 with nvidia-331
	base_env.Append(LIBS = ['-lGL', '-lGLU', '-lGLEW', '-lX11'])

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
	objects = env.SConscript('SConscript', exports=['env', 'config', 'platform'])
	target = env.Program('#bin/%s/Application' % (config), objects)	
	env.Clean(target, 'bin')
	env.Clean(target, 'obj')

