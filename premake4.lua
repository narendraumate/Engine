-- A solution contains projects, and defines the available configurations
solution "Application"
    configurations { "debug", "release" }
	defines { "ASSIMP_BUILD_BOOST_WORKAROUND" }
	
	-- Disable assimp, DevIL, glsw
	excludes { "**/assimp/**", "**/DevIL/**", "**/glsw/**" }
	
	excludes {	"**/src-IL/**", 
				"**/src-ILU/**", 
				"**/src-ILUT/**", 
				"Engine/External/assimp/revision.h" }
	includedirs {	"Engine/External/assimp/code/BoostWorkaround", 
					"Engine/External/assimp/contrib/cppunit-1.12.1/include", 
					"Engine/External/DevIL/DevIL/include"	}

    -- A project defines one build target
    project "Application"
        kind "WindowedApp"
        language "C++"
		files { "**.h", "**.hh", "**.hpp", "**.c", "**.cc", "**.cpp" }
		files { "**.vert", "**.frag" }
 
        configuration "debug"
            defines { "DEBUG" }
            flags { "Symbols" }
            targetdir ( "bin/debug" )
            objdir ( "obj/debug" )
            -- targetname ( "Application" )

        configuration "release"
            defines { "NDEBUG" }
            flags { "Optimize" }
            targetdir ( "bin/release" )
            objdir ( "obj/release" )
            -- targetname ( "Application" )

        configuration "windows"
            linkoptions { }
            files { }
            excludes { "**/MacOS/**", "**/Linux/**" }

        configuration "macosx"
            linkoptions { "-framework Cocoa", "-framework OpenGL", "-framework QuartzCore" }
            files { "**.m", "**.mm" }
            excludes { "**/Windows/**", "**/Linux/**" }

        configuration "linux"
            linkoptions { "-lGL", "-lGLU" }
			files { }
            excludes { "**/Windows/**", "**/MacOS/**" }
