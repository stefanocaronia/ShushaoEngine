-- Box2D premake5 script.
-- https://premake.github.io/

project "Glad"
    kind "StaticLib"
    language "C"

	-- targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    -- objdir ("obj/" .. outputdir .. "/%{prj.name}")

    targetdir ("lib")
    objdir ("obj")

    makesettings [[
        CC = gcc
    ]]

    configuration { "gmake2" }
        targetextension (".a")

    files
    {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }

	includedirs
	{
		"include"
	}

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"