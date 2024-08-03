project "Oxide"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files{
        "src/**.h",
        "src/**.cpp"
    }

    includedirs{
        "src",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.spdlog}"
    }

    links{
        "opengl32.lib",
        "GLFW",
        "glad"
    }

    filter "configurations:Debug"
        defines "OX_DEBUG"
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        defines "OX_RELEASE"
        runtime "Release"
        optimize "on"