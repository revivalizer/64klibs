local common = {}
common.targetDir = "build/%{prj.name}/bin/%{cfg.longname}"
common.objDir    = "build/%{prj.name}/obj/%{cfg.longname}"

common.compilerFlags             = { "FatalWarnings", "MultiProcessorCompile", "No64BitChecks",  "NoEditAndContinue" }
common.standaloneFlags           = { "NoBufferSecurityCheck", "NoExceptions", "NoManifest", "NoRTTI", "NoRuntimeChecks" }
common.buildOptions              = { "/wd4725" } -- 4725 is old warning for tan asm func
common.standaloneLinkOptions     = { "/NODEFAULTLIB", "/ignore:4254", "/DYNAMICBASE:NO", "SAFESEH:NO"} -- 4254 is section '.CRT' (40000040) merged into '.data' (C0000040) with different attributes

common.GenerateStandardSetup = function()
	targetdir(common.targetDir)
	objdir   (common.objDir)
	location "build"

	flags(common.compilerFlags)
	buildoptions(common.buildOptions)
	warnings       "extra"
	floatingpoint  "fast"

	defines { "_CRT_SECURE_NO_WARNINGS" }
	defines { "WIN32" }
end

common.GenerateStandardDebugConfiguration = function()
	filter "configurations:*Debug*"
		defines { "DEBUG" }
		flags { "Symbols", "Maps" }
		optimize "Off"

	filter {}
end

common.GenerateStandardReleaseConfiguration = function()
	filter "configurations:*Release*"
		defines { "NDEBUG" }
		optimize "Size"

	filter {}
end

common.GenerateStandaloneConfiguration = function()
	filter "configurations:*Standalone*"
		defines { "STANDALONE" }

	filter {}
end

common.GenerateCrinklerConfiguration = function()
	filter "configurations:*Crinkler*"
		linkoptions {"/CRINKLER /REPORT:crinkler.html /TRANSFORM:CALLS"}

	filter {}
end

common.GenerateKkrunchyConfiguration = function()
	filter "configurations:*Kkrunchy*"
		-- needs something here

	filter {}
end

common.GenerateStandardConfigurations = function()
	common.GenerateStandardDebugConfiguration()
	common.GenerateStandardReleaseConfiguration()
end

common.GenerateStandaloneConfigurations = function()
	common.GenerateStandaloneConfiguration()
	common.GenerateCrinklerConfiguration()
	common.GenerateKkrunchyConfiguration()
end

common.NoStdLib = function()
	flags { "NoBufferSecurityCheck", "NoExceptions", "NoManifest", "NoRTTI", "NoRuntimeChecks", "OmitDefaultLibrary" } 
	buildoptions { "/wd4725 /wd4201" } -- 4725 is old warning for tan asm func
	buildoptions { "/arch:IA32" } -- removes intrinsic SSE2 pow, sin etc
--	buildoptions { "/QIfist" }
end

common.NoStdLibLink = function()
	linkoptions { "/NODEFAULTLIB" }
	linkoptions {"/DYNAMICBASE:NO"} -- neccesary for kkrunchy
	linkoptions {"/SAFESEH:NO"}
end

return common