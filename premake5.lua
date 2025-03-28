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
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/glm/glm",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.SDL3}"
	}

	links
	{
		"Glad",
		"SDL3"
	}

	filter "system:windows"
		systemversion "latest"


		defines
		{
			"CF_PLATFORM_WINDOWS",
			"CF_BUILD_DLL"
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
		"CFrame/src",
		"%{prj.name}/vendor/glm/glm",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.SDL3}"
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
