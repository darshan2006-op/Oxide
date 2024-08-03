project "Demo"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files{
        "src/**.h",
        "src/**.cpp"
    }

    includedirs{
        "src",
        "%{IncludeDir.Oxide}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.spdlog}"
    }

    links{
        "Oxide"
    }

    filter "configurations:Debug"
        defines "OX_DEBUG"
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        defines "OX_RELEASE"
        runtime "Release"
        optimize "on"