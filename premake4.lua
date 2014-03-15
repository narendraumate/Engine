-- A solution contains projects, and defines the available configurations
solution "Application"
    configurations { "Debug", "Release" }
	defines { "ASSIMP_BUILD_BOOST_WORKAROUND" }
	
	-- Disable assimp and DevIL entirely
	excludes { "**/assimp/**", "**/DevIL/**" }
	
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
            files { "**.h", "**.hh", "**.hpp", "**.c", "**.cc", "**.cpp" }
            excludes { "**/MacOS/**", "**/Linux/**" }

        configuration "macosx"
            linkoptions { "-framework Cocoa", "-framework OpenGL", "-framework QuartzCore" }
            files { "**.h", "**.hh", "**.hpp", "**.c", "**.cc", "**.cpp", "**.m", "**.mm" }
            excludes { "**/Windows/**", "**/Linux/**" }

        configuration "linux"
            linkoptions { "-lGL", "-lGLU" }
            files { "**.h", "**.hh", "**.hpp", "**.c", "**.cc", "**.cpp" }
            excludes { "**/Windows/**", "**/MacOS/**" }

