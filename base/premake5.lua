project "base"
	kind "StaticLib"

--	targetdir("build/%{prj.name}/bin/%{cfg.longname}")
--	objdir   ("build/%{prj.name}/obj/%{cfg.longname}")

	configmap {
		["VSTi Debug"]   = "Debug",
		["VSTi Release"] = "Release",
		["Debug Standalone"]   = "Debug Standalone",
		["Release Standalone"] = "Release Standalone",
		["Release Standalone Crinkler"] = "Release Standalone",
		["Release Standalone Kkrunchy"] = "Release Standalone",
	}

	pchheader "pch.h"
	pchsource "pch.cpp"

	files { "./datatypes/*.h", "./datatypes/*.cpp" }
	files { "./math/*.h", "./math/*.cpp" }
	files { "./util/*.h", "./util/*.cpp" }
	files { "./pch.h", "./pch.cpp", "./base.h" }

	filter "configurations:*Standalone"
		defines { "STANDALONE" }
	filter {}

	filter "Debug*"
		defines { "DEBUG" }
		flags { "Symbols", "Maps" }
		optimize "Off"

	filter "Release*"
		defines { "NDEBUG" }
		optimize "Size"
