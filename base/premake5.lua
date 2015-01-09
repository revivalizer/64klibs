project "base"
	kind "StaticLib"

--	targetdir("build/%{prj.name}/bin/%{cfg.longname}")
--	objdir   ("build/%{prj.name}/obj/%{cfg.longname}")

	configmap {
		["VSTi Debug"]   = "Debug",
		["VSTi Release"] = "Release",
		["Debug Standalone"]   = "Debug",
		["Release Standalone"] = "Release",
		["Release Standalone Crinkler"] = "Release",
		["Release Standalone Kkrunchy"] = "Release",
	}

	pchheader "pch.h"
	pchsource "pch.cpp"

	files { "./datatypes/*.h", "./datatypes/*.cpp" }
	files { "./math/*.h", "./math/*.cpp" }
	files { "./util/*.h", "./util/*.cpp" }
	files { "./pch.h", "./pch.cpp", "./base.h", "./config.h" }

	filter "Debug"
		defines { "DEBUG" }
		flags { "Symbols", "Maps" }
		optimize "Off"

	filter "Release"
		defines { "NDEBUG" }
		optimize "Size"
