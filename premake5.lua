workspace "CFrame"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["Glad"] = "CFrame/vendor/Glad/include"
	IncludeDir["SDL3"] = "CFrame/vendor/SDL3/SDL/include"

	include "CFrame/vendor/Glad"
	include "CFrame/vendor/SDL3/SDL"
	

project "CFrame"
	location "CFrame"
	kind "Staticlib"
	language "C++"
	cppdialect "c++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}


	includedirs
	{
		"%{prj.name}/vendor/stb",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/glm/glm",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.SDL3}",
		"CFrame/vendor/freetype/include/",
		"CFrame/vendor/freetype/include/freetype"
	}

	libdirs {
        "CFrame/vendor/freetype/lib"   
    }

	links
	{
		"Glad",
		"SDL3",
		"freetype"
	}

	filter "system:windows"
		systemversion "latest"


		defines
		{
			"CF_PLATFORM_WINDOWS"
		}


		filter "configurations:Debug"
			defines "CF_DEBUG"
			symbols "on"

		filter "configurations:Release"
			defines "CF_RELEASE"
			optimize "on"

		filter "configurations:Dist"
			defines "CF_DIST"
			optimize "on"



project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "c++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")

	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"CFrame/vendor/spdlog/include",
		"CFrame/src"              
	}

	links
	{
	    "CFrame"
	}

		filter "system:windows"
		systemversion "latest"


		defines
		{
			"CF_PLATFORM_WINDOWS",
		}

		filter "configurations:Debug"
			defines "CF_DEBUG"
			symbols "on"

		filter "configurations:Release"
			defines "CF_RELEASE"
			optimize "on"

		filter "configurations:Dist"
			defines "CF_DIST"
			optimize "on"
