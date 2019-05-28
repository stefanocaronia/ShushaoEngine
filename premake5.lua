workspace "Shushao"
	architecture "x64"
    startproject "Game"

	configurations {
		"Debug",
		"Release"
    }

    rebuildcommands {
        "make %{cfg.buildcfg} rebuild"
    }

    --outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    outputdir = "%{cfg.buildcfg}"
    Game = "Game"
    Engine = "Shushao"
    gamebin = "../bin/" .. outputdir .. "/%{Game}/"
    enginebin = "../bin/" .. outputdir .. "/%{Engine}/"

    include "Shushao/vendor/GLFW"
    include "Shushao/vendor/Glad"
    include "Shushao/vendor/SOIL"
    include "Shushao/vendor/Box2D"
    include "Shushao/vendor/imgui"

project "ShushaoDLL"
    location "Shushao"
    kind "SharedLib"
    targetname "libshushao"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    files {
		"%{prj.name}/src/Shushao/Resources/**.h",
		"%{prj.name}/src/Shushao/Resources/**.rc"
	}

project "Shushao"
	location "Shushao"
	kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    targetname "libshushao"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	pchheader "sepch.h"
    pchsource "%{Engine}/src/sepch.cpp"

    files {
		"%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
	}

    includedirs {
        "%{prj.name}/src",
		"%{prj.name}/vendor/GLFW/include",
		"%{prj.name}/vendor/Glad/include",
		"%{prj.name}/vendor/SOIL/include",
        "%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/glm",
		"%{prj.name}/vendor/boost",
		"%{prj.name}/vendor/Box2D",
		"%{prj.name}/vendor/freetype/include"
    }

    libdirs {
		"%{prj.name}/vendor/boost/stage/lib",
		"%{prj.name}/vendor/Box2D/lib",
		"%{prj.name}/vendor/freetype/lib",
		-- "%{prj.name}/vendor/SDL2_mixer/lib"
    }

    links {
        "GLFW",
        "Glad",
        "SOIL",
        "Box2D",
        "boost_context",
        "boost_coroutine",
        "freetype",
        "gdi32",
        "mingw32",
        "opengl32",
        "mingw32"
    }

    defines {
    }

	filter "system:windows"
		systemversion "latest"

		defines {
			"SE_PLATFORM_WINDOWS",
			"SE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "SE_DEBUG"
		runtime "Debug"
        symbols "On"

    filter { "configurations:Debug", "toolset:gcc" }
        buildoptions { "-std=c++17", "-Wall", "-fmax-errors=4", "-Wfatal-errors" }

	filter "configurations:Release"
		defines "SE_RELEASE"
		runtime "Release"
        optimize "On"

    filter { "configurations:Release", "toolset:gcc" }
        buildoptions { "-O2", "-std=c++17" }
        linkoptions { "-s -mwindows"}

project "Game"
	location "Game"
	kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
        "%{Engine}/src",
		"%{Engine}/vendor/glm",
        "%{Engine}/vendor/spdlog/include",
		"%{Engine}/vendor/boost",
		"%{Engine}/vendor/freetype/include"
    }

	links {
        Engine
    }

    prelinkcommands {
        ("@cp -r res %{gamebin}"),
        ("@cp %{enginebin}/*.dll %{gamebin}")
    }

	filter "system:windows"
		systemversion "latest"
		defines {
			"SE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SE_DEBUG"
		runtime "Debug"
        symbols "On"

    filter { "configurations:Debug", "toolset:gcc" }
        buildoptions { "-std=c++17", "-Wall", "-fmax-errors=4", "-Wfatal-errors" }

	filter "configurations:Release"
		defines "SE_RELEASE"
		runtime "Release"
        optimize "On"

    filter { "configurations:Release", "toolset:gcc" }
        buildoptions { "-O2", "-std=c++17" }
        linkoptions { "-s -mwindows"}
