project "render"
	kind "StaticLib"

	configmap {
		["Debug Standalone"]   = "Debug Standalone",
		["Release Standalone"] = "Release Standalone",
		["Release Standalone Crinkler"] = "Release Standalone",
		["Release Standalone Kkrunchy"] = "Release Standalone",
	}

	pchheader "pch.h"
	pchsource "pch.cpp"

	files { "./*.h", "./*.cpp" }

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
