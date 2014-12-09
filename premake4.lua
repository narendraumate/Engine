-- A solution contains projects, and defines the available configurations
solution "Engine"
	configurations { "debug", "release" }

	-- Additional defines
	-- defines { "ASSIMP_BUILD_BOOST_WORKAROUND" } -- disable assimp boost
	
	-- Disable assimp, callback, DevIL, glsw
	excludes { "**/assimp/**", "**/callback/**", "**/DevIL/**", "**/glsw/**" }
	
	excludes {	"**/src-IL/**", 
				"**/src-ILU/**", 
				"**/src-ILUT/**", 
				"Engine/External/assimp/revision.h"	}
	includedirs {	"Engine/External/assimp/code/BoostWorkaround", 
					"Engine/External/assimp/contrib/cppunit-1.12.1/include", 
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
			linkoptions { "-framework Cocoa", "-framework OpenGL", "-framework QuartzCore" }
			files { "**.m", "**.mm" }
			excludes { "**/Windows/**", "**/Linux/**" }

		configuration "linux"
			linkoptions { "-lGL", "-lGLU", "-lGLEW", "-lX11", "-L/usr/lib/nvidia-331/" } -- hack for ubuntu 14.04 with nvidia-331
			files { }
			excludes { "**/Windows/**", "**/MacOS/**" }
