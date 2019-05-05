project "SOIL"
    kind "StaticLib"
    language "C"
    targetname "libSOIL"

    targetdir ("lib")
    objdir ("obj")

    makesettings [[
        CC = gcc
    ]]

    configuration { "gmake2" }
        implibextension (".a")
        targetextension (".a")
        buildoptions { "-O2","-s","-w" }

    files {
        "src/image_helper.c",
        "src/stb_image_aug.c",
        "src/image_DXT.c",
        "src/SOIL.c",
    }

    includedirs {
		"src"
	}

    postbuildcommands {
        "@mkdir -p include/",
        "@cp src/SOIL.h include/"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"