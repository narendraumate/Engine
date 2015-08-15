-- A solution contains projects, and defines the available configurations
solution "Engine"
	configurations { "debug", "release" }

	-- Additional defines
	-- disable assimp boost, assimp zlib
	defines {	"ASSIMP_BUILD_BOOST_WORKAROUND",
				"ASSIMP_BUILD_NO_OWN_ZLIB"	}

	excludes { "**/callback/**", "**/glsw/**", "**/src-ILU/ilur/**" }

	includedirs {	"Engine/External/assimp/code/BoostWorkaround",
					"Engine/External/assimp/contrib/cppunit-1.12.1/include",
					"Engine/External/assimp/include",
					"Engine/External/DevIL/DevIL/include"	}

	-- A project defines one build target
	project "Engine"
		kind "WindowedApp"
		language "C++"
		files { "**.h", "**.hh", "**.hpp", "**.c", "**.cc", "**.cpp" }
		files { "**.vert", "**.frag" }
 
		configuration "debug"
			defines { "DEBUG" }
			flags { "Symbols" }
			targetdir ( "bin/debug" )
			objdir ( "obj/debug" )
			-- targetname ( "Engine" )

		configuration "release"
			defines { "NDEBUG" }
			flags { "Optimize" }
			targetdir ( "bin/release" )
			objdir ( "obj/release" )
			-- targetname ( "Engine" )

		configuration "windows"
			linkoptions { }
			files { }
			excludes { "**/MacOS/**", "**/Linux/**" }

		configuration "macosx"
			buildoptions { "-fgnu89-inline" } -- hack for DevIL
			linkoptions { "-framework Cocoa", "-framework OpenGL", "-framework QuartzCore" }
			files { "**.m", "**.mm" }
			excludes { "**/Windows/**", "**/Linux/**" }

		configuration "linux"
			linkoptions { "-lGL", "-lGLU", "-lGLEW", "-lX11", "-L/usr/lib/nvidia-331/" } -- hack for ubuntu 14.04 with nvidia-331
			files { }
			excludes { "**/Windows/**", "**/MacOS/**" }
