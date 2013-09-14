-- A solution contains projects, and defines the available configurations
solution "Application"
    configurations { "Debug", "Release" }

    -- A project defines one build target
    project "Application"
        kind "ConsoleApp"
        language "C++"
        files { "**.h", "**.cpp" }
 
        configuration "Debug"
            defines { "DEBUG" }
            flags { "Symbols" }

        configuration "Release"
            defines { "NDEBUG" }
            flags { "Optimize" }

        configuration "windows"
            targetdir ( "build" )

        configuration "macosx"
            linkoptions { "-framework OpenGL", "-framework GLUT" }
