project "Glad"
	kind "StaticLib"
	language "C"
	
	targetdir (outputOrigin .."/bin/" .. outputdir .. "/%{prj.name}")
	objdir (outputOrigin .."/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"**.**"
	}

	includedirs
	{
		"include"
	}
	
	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		runtime "Debug"
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		runtime "Release"
		optimize "On"