import sys

platform = sys.platform

common_env = Environment()

if platform == "win32":
    pass
elif platform == "darwin":
    common_env.Append(
        LINKFLAGS=['-framework', 'Cocoa', '-framework', 'OpenGL', '-framework', 'QuartzCore'],
        FRAMEWORKS=['Cocoa', 'OpenGL', 'QuartzCore']
	)
elif platform == "linux2":
    pass

debug_env = common_env.Clone()
debug_env.Append(CPPDEFINES=['DEBUG'])
debug_env.VariantDir('bin/debug', '.', duplicate=0)

release_env = common_env.Clone()
release_env.Append(CPPDEFINES=['NDEBUG'])
release_env.VariantDir('bin/release', '.', duplicate=0)

for mode, env in dict(debug=debug_env, release=release_env).iteritems():
    #env.SConscript('bin/%s/SConscript' % mode, {'env': env})
    env.SConscript('bin/%s/SConscript' % mode, exports='env')
