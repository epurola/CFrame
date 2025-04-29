
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "SDL3"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"CFrame/vendor/SDL3/src/**.c",   
    
	}

	includedirs
	{
		"CFrame/vendor/SDL3/SDL/include" 
	}

	filter "system:windows"
	systemversion "latest"                  
	defines 
	{  
		"SDL_PLATFORM_WINDOWS"         
	}
		systemversion "latest"
		staticruntime "on" 