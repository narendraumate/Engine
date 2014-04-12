import sys

# global
env_build_platform_list = []

# base
base_env = Environment()

base_env.Append(
	CPPPATH = ['.'],
)

# windows
windows_env = base_env.Clone()
windows_env.Append(
	CCFLAGS = [
			   '/EHsc',
			   ],
	LIBS = [
			'user32',
			'gdi32',
			],
)

windows_env_debug = windows_env.Clone()
windows_env_release = windows_env.Clone()
env_build_platform_list.append((windows_env_debug, "debug", "win32"))
env_build_platform_list.append((windows_env_release, "release", "win32"))

# macosx
macosx_env = base_env.Clone()
macosx_env.Append(
	LINKFLAGS = [
				 '-framework',
				 'Cocoa',
				 '-framework',
				 'OpenGL',
				 '-framework',
				 'QuartzCore',
				 ],
	FRAMEWORKS = [
			'Cocoa',
			'OpenGL',
			'QuartzCore',
			],
	LIBPATH = [
			   '/System/Library/Frameworks/Cocoa.framework',
			   '/System/Library/Frameworks/OpenGL.framework/Libraries',
			   '/System/Library/Frameworks/QuartzCore.framework/Libraries',
			   ],
)

macosx_env_debug = macosx_env.Clone()
macosx_env_release = macosx_env.Clone()
env_build_platform_list.append((macosx_env_debug, "debug", "darwin"))
env_build_platform_list.append((macosx_env_release, "release", "darwin"))

# linux
linux_env = base_env.Clone()
linux_env.Append(
	LINKFLAGS = [
				 '-lGL',
				 '-lGLU'
				 ],
)

linux_env_debug = linux_env.Clone()
linux_env_release = linux_env.Clone()
env_build_platform_list.append((linux_env_debug, "debug", "linux2"))
env_build_platform_list.append((linux_env_release, "release", "linux2"))

# common
for env, build, platform in env_build_platform_list:
	if build == "debug":
		env.Append(CPPDEFINES=['DEBUG'])
		env.VariantDir('bin/debug', '.', duplicate=0)
	elif build == "release":
		env.Append(CPPDEFINES=['NDEBUG'])
		env.VariantDir('bin/release', '.', duplicate=0)

# SConscript
for environment, build, platform in env_build_platform_list:
	if platform == sys.platform:
		# print environment, build, platform
		env.SConscript('bin/%s/SConscript' % build, {'env' : environment})
