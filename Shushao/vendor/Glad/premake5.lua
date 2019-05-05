project "Glad"
    kind "StaticLib"
    language "C"

	-- targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    -- objdir ("obj/" .. outputdir .. "/%{prj.name}")

    configuration { "gmake2" }
        implibextension (".a")

    targetdir ("lib")
    objdir ("obj")

    makesettings [[
        CC = gcc
    ]]

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