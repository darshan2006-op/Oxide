project "glad"
    kind "StaticLib"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files{
        "src/**.h",
        "include/**.h",
        "src/**.c"
    }

    includedirs{
        "%{IncludeDir.glad}"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        runtime "Release"
        optimize "on"