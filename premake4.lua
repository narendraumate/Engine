-- A solution contains projects, and defines the available configurations
solution "Application"
    configurations { "Debug", "Release" }
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
 
        configuration "Debug"
            defines { "DEBUG" }
            flags { "Symbols" }
            targetdir ( "bin/Debug" )
            objdir ( "obj/Debug" )
            -- targetname ( "Application" )

        configuration "Release"
            defines { "NDEBUG" }
            flags { "Optimize" }
            targetdir ( "bin/Release" )
            objdir ( "obj/Release" )
            -- targetname ( "Application" )

        configuration "windows"
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

