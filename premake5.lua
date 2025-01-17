outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
outputOrigin = "C:/Windows/Temp/Limux"
workspace "Limux"
	platforms { "x86", "x64" }
	startproject "LimuxEditor"
	configurations { "Debug", "Release" ,"Dist"}

	systemversion "latest"
	
    staticruntime "off"

	flags
	{
		"MultiProcessorCompile"
	}

	vpaths {
		["Headers"] = { "%{prj.name}/src/**.hpp","%{prj.name}/src/**.h" },
		["Sources"] = { "%{prj.name}/src/**.cpp","%{prj.name}/src/**.c" },
		["images"] = {"**.png","**.jpg","**.bmp","**.ppm","**.pgm","**.pbm","**.tga","**.gif","**.ico","**.icns","**.cur","**.xbm","**.xpm"},
		["shaders"] = {"**.shader","**.frag","**.vert","**.glsl","**.hlsl"},
		["Docs"] = "**.md",
	}
	
	filter "platforms:x86"
		architecture "x86"
		defines { "x86" }
		
	filter "platforms:x64"
		architecture "x86_64"
		defines { "x64" }

	
	
IncludeDir = {}
IncludeDir["GLFW"]   = "%{wks.location}/Limux/vendor/GLFW/include"
IncludeDir["Glad"]   = "%{wks.location}/Limux/vendor/Glad/include"
IncludeDir["ImGui"]  = "%{wks.location}/Limux/vendor/ImGui"
IncludeDir["glm"]    = "%{wks.location}/Limux/vendor/glm"
IncludeDir["stb"]    = "%{wks.location}/Limux/vendor/stb"
IncludeDir["assimp"] = "%{wks.location}/Limux/vendor/assimp/include"
IncludeDir["assimpconfig"] = "%{wks.location}/Limux/vendor/assimp/_config_headers/"
IncludeDir["entt"] = "%{wks.location}/Limux/vendor/entt/include"



group "Dependencies"
	include "Limux/vendor/GLFW"
	include "Limux/vendor/Glad"
	include "Limux/vendor/ImGui"
	include "Limux/vendor/stb"
	include "Limux/vendor/assimp"
	
group ""
--group "Engine"
	include "Limux"
--	include "sandbox"
	include "LimuxEditor"
--group ""
