# Define a common build environment
common_env = Environment()

# Clone Debug environment
debug_env = common_env.Clone()
debug_env.Append(CPPDEFINES=['DEBUG'])
debug_env.Append(CCFLAGS=['Symbols'])
debug_env.VariantDir('bin/Debug', '.')

# Clone Release environment
release_env = common_env.Clone()
release_env.Append(CPPDEFINES=['NDEBUG'])
release_env.Append(CCFLAGS=['Optimize'])
release_env.VariantDir('bin/Release', '.')

# Iterate over all build environments and invoke the lower level SConscript files.
for mode, env in dict(Debug=debug_env, Release=release_env).iteritems():
    env.SConscript('SConscript', {'env': env})
