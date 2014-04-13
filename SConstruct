import os
import sys

# global
env_build_platform_list = []

# base
base_env = Environment()

# windows
windows_env = base_env.Clone()

windows_env_debug = windows_env.Clone()
windows_env_release = windows_env.Clone()
env_build_platform_list.append((windows_env_debug, "debug", "win32"))
env_build_platform_list.append((windows_env_release, "release", "win32"))

# macosx
macosx_env = base_env.Clone()
macosx_env.Append(FRAMEWORKS = ['Cocoa', 'OpenGL', 'QuartzCore'])#

macosx_env_debug = macosx_env.Clone()
macosx_env_release = macosx_env.Clone()
env_build_platform_list.append((macosx_env_debug, "debug", "darwin"))
env_build_platform_list.append((macosx_env_release, "release", "darwin"))

# linux
linux_env = base_env.Clone()
linux_env.Append(LINKFLAGS = ['-lGL', '-lGLU'])#

linux_env_debug = linux_env.Clone()
linux_env_release = linux_env.Clone()
env_build_platform_list.append((linux_env_debug, "debug", "linux2"))
env_build_platform_list.append((linux_env_release, "release", "linux2"))

# common
for env, build, platform in env_build_platform_list:
	env.VariantDir(os.path.join('bin', build), '.', duplicate=0)
	if build == "debug":
		env.Append(CPPDEFINES=['DEBUG'])#
		env.Append(CCFLAGS=['-g'])#
	elif build == "release":
		env.Append(CPPDEFINES=['NDEBUG'])#
		env.Append(CCFLAGS=['-O2'])#

# SConscript
for env, build, platform in env_build_platform_list:
	if build == "debug" and platform == sys.platform:
		env.SConscript('bin/%s/SConscript' % build, exports=['env', 'build', 'platform'])
