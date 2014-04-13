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
macosx_env.Append(
	FRAMEWORKS = [
				  'Cocoa',
				  'OpenGL',
				  'QuartzCore',
				  ],
	LINKFLAGS = [
				 '-framework', 'Cocoa',
				 '-framework', 'OpenGL',
				 '-framework', 'QuartzCore',
				 ],
	CPPPATH = [
			   '/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk/System/Library/Frameworks/Cocoa.framework/Headers',
			   '/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk/System/Library/Frameworks/OpenGL.framework/Headers',
			   '/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk/System/Library/Frameworks/QuartzCore.framework/Headers',
			   ],
	LIBPATH = [
			   '/System/Library/Frameworks/Cocoa.framework',
			   '/System/Library/Frameworks/OpenGL.framework',
			   '/System/Library/Frameworks/QuartzCore.framework',
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
