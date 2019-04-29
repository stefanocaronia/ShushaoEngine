workspace "Shushao"
	architecture "x64"
	startproject "Game"

	configurations {
		"Debug",
		"Release"
	}

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    Game = "Game"
    Engine = "Shushao"
    cores = 8
    gamebin = "../bin/" .. outputdir .. "/%{Game}/"
    enginebin = "../bin/" .. outputdir .. "/%{Engine}/"

    include "%{Engine}/vendor/GLFW"
    include "%{Engine}/vendor/Glad"

project "Shushao"
	location "Shushao"
	kind "SharedLib"
	language "C++"
    staticruntime "off"
    targetname "libshushao"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	pchheader "sepch.h"
    pchsource "%{Engine}/src/sepch.cpp"

    configuration { "gmake2" }
        buildoptions {
                --           "-static-libgcc",
                --           "-static-libstdc++"
        }

    files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

    includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/SDL2/include/SDL2",
		"%{prj.name}/vendor/SDL2_image/include/SDL2",
		"%{prj.name}/vendor/SDL2_mixer/include/SDL2",
		"%{prj.name}/vendor/glm",
		"%{prj.name}/vendor/boost",
		"%{prj.name}/vendor/glew/include",
		"%{prj.name}/vendor/Box2D/include",
		"%{prj.name}/vendor/freetype/include"
    }

    libdirs {
		"%{prj.name}/vendor/boost/stage/lib",
		"%{prj.name}/vendor/glew/lib",
		"%{prj.name}/vendor/Box2D/lib",
		"%{prj.name}/vendor/freetype/lib",
		"%{Engine}/vendor/SDL2/lib",
		"%{Engine}/vendor/SDL2_image/lib",
		"%{Engine}/vendor/SDL2_mixer/lib",
    }

    links {
        "boost_context",
        "boost_coroutine",
        "glew32",
        "mingw32",
        "opengl32",
        "gdi32",
        "glu32",
        "freetype",
        "Box2D",
        "SDL2main",
        "SDL2",
        "SDL2_image",
        "SDL2_mixer",
    }

    defines {
        "GLEW_STATIC",
    }

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines {
			"SE_PLATFORM_WINDOWS",
			"SE_BUILD_DLL"
		}

		postbuildcommands {}

	filter "configurations:Debug"
		defines "SE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "SE_DIST"
		runtime "Release"
		optimize "On"

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
        "%{Engine}/src",
        "%{Engine}/vendor/SDL2/include/SDL2",
		"%{Engine}/vendor/SDL2_image/include/SDL2",
		"%{Engine}/vendor/SDL2_mixer/include/SDL2",
		"%{Engine}/vendor/glm",
		"%{Engine}/vendor/boost",
		"%{Engine}/vendor/Box2D/include",
		"%{Engine}/vendor/freetype/include",
		"%{Engine}/vendor/glew/include"
    }

    libdirs {
		"%{Engine}/vendor/SDL2/lib",
		"%{Engine}/vendor/SDL2_image/lib",
        "%{Engine}/vendor/SDL2_mixer/lib",
        "%{Engine}/vendor/Box2D/lib",
    }

	links {
        Engine,
        "mingw32",
        "opengl32",
        "gdi32",
        "glu32",
        "SDL2main",
        "SDL2",
        "SDL2_image",
        "SDL2_mixer",
        "Box2D",
    }

    prelinkcommands {
        ("@{COPY} res %{gamebin}"),
        ("@{COPY} %{enginebin}/*.dll %{gamebin}"),
		("@{COPY} ../%{Engine}/vendor/SDL2/bin/SDL2.dll %{gamebin}"),
		("@{COPY} ../%{Engine}/vendor/SDL2_image/bin/*.dll %{gamebin}"),
		("@{COPY} ../%{Engine}/vendor/SDL2_mixer/bin/SDL2_mixer.dll %{gamebin}"),
		("@{COPY} ../%{Engine}/vendor/SDL2_mixer/bin/libogg-0.dll %{gamebin}"),
		("@{COPY} ../%{Engine}/vendor/SDL2_mixer/bin/libmpg123-0.dll %{gamebin}")
    }

    configuration { "gmake2" }
        buildoptions {}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines {
			"SE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "SE_DIST"
		runtime "Release"
		optimize "On"