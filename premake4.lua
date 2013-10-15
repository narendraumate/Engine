-- A solution contains projects, and defines the available configurations
solution "Application"
    configurations { "Debug", "Release" }

    -- A project defines one build target
    project "Application"
        kind "WindowedApp"
        language "C++"
 
        configuration "Debug"
            defines { "DEBUG" }
            flags { "Symbols" }

        configuration "Release"
            defines { "NDEBUG" }
            flags { "Optimize" }

        configuration "windows"
            targetdir ( "build" )
            files { "**.h", "**.hpp", "**.c", "**.cpp" }
            excludes { "**/MacOS/**", "**/Linux/**" }

        configuration "macosx"
            linkoptions { "-framework Cocoa", "-framework OpenGL", "-framework QuartzCore" }
            files { "**.h", "**.hpp", "**.c", "**.cpp", "**.m", "**.mm" }
            excludes { "**/Windows/**", "**/Linux/**" }

        configuration "linux"
            files { "**.h", "**.hpp", "**.c", "**.cpp" }
            excludes { "**/Windows/**", "**/MacOS/**" }

