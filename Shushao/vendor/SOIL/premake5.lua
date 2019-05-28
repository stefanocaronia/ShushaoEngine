project "SOIL2"
    kind "StaticLib"
    language "C++"

    buildoptions { "/TP" }
    defines { "_CRT_SECURE_NO_WARNINGS" }

    targetdir ("lib")
    objdir ("obj")

    files { "src/SOIL2/*.c" }

    configuration "debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "On"

    configuration "release"
        defines "NDEBUG"
        runtime "Release"
        optimize "On"