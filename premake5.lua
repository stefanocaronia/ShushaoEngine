workspace "Shushao"
	architecture "x64"
    startproject "Game"

	configurations {
		"Debug",
		"Release"
    }

    --[[ rebuildcommands {
        "make %{cfg.buildcfg} rebuild"
    } ]]

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

    debugdir ("bin/" .. outputdir .. "/%{prj.name}")

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/main.cpp",
		-- "%{prj.name}/src/**.h",
		-- "%{prj.name}/src/**.cpp",
		-- "%{prj.name}/src/**.rc",
	}

	includedirs {
        "%{Engine}/src",
		"%{Engine}/vendor/glm",
        "%{Engine}/vendor/spdlog/include",
		"%{Engine}/vendor/boost"
    }

    libdirs {
		"%{Engine}/vendor/Box2D/lib",
		"%{Engine}/vendor/freetype/lib",
		"%{Engine}/vendor/SOIL/lib",
		"%{Engine}/vendor/GLFW/lib",
		"%{Engine}/vendor/Glad/lib",
		"%{Engine}/vendor/boost/stage/lib"
    }

    links {
        Engine,
        "GLFW",
        "Glad",
        "SOIL2",
        "Box2D",
        "freetype",
        "opengl32",
        "libboost_context-vc142-mt-sgd-x64-1_70.lib",
        "libboost_coroutine-vc142-mt-sgd-x64-1_70.lib"
    }

    prelinkcommands {
        ("{COPY} res %{gamebin}"),
        ("{COPY} %{enginebin}/*.dll %{gamebin}")
    }

	filter "system:windows"
		systemversion "latest"
		defines {
			"SE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SE_DEBUG"
		runtime "Debug"
        symbols "on"

    filter { "configurations:Debug", "toolset:gcc" }
        buildoptions { "-std=c++17", "-Wall", "-fmax-errors=4", "-Wfatal-errors" }

	filter "configurations:Release"
		defines "SE_RELEASE"
		runtime "Release"
        optimize "on"

    filter { "configurations:Release", "toolset:gcc" }
        buildoptions { "-O2", "-std=c++17" }
        linkoptions { "-s -mwindows"}
        links { "mingw32" }


project "Shushao Resources"
    location "Shushao"
    kind "SharedLib"
    targetname "shushaores"
    staticruntime "Off"

    targetdir ("bin/" .. outputdir .. "/Shushao")
    objdir ("obj/" .. outputdir .. "/Shushao")

    files {
        "Shushao/src/Shushao/Resources/**.h",
        "Shushao/src/Shushao/Resources/**.rc"
    }

    linkoptions "/NOENTRY"

    configuration "Debug"
        buildoptions "/MDd"
    configuration "Release"
        buildoptions "/MD"
