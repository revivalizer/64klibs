project "opengl"
	kind "StaticLib"

	configmap {
		["Debug Standalone"]   = "Debug",
		["Release Standalone"] = "Release",
		["Release Standalone Crinkler"] = "Release",
		["Release Standalone Kkrunchy"] = "Release",
	}

	pchheader "pch.h"
	pchsource "pch.cpp"

	files { "./ogl/*.h" }
	files { "./*.h", "./*.cpp" }

	filter "Debug"
		defines { "DEBUG" }
		flags { "Symbols", "Maps" }
		optimize "Off"

	filter "Release"
		defines { "NDEBUG" }
		optimize "Size"
