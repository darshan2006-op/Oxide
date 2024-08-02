include "deps.lua"


workspace "Oxide"

architecture "x86_64"
startproject "Demo"

configurations{
    "Debug",
    "Release"
}

flags{
    "MultiProcessorCompile"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


group "Dependencies"
    include "Oxide/vendor/glfw"
    include "Oxide/vendor/glad"

group "Core"
    include "Oxide"
    include "Demo"
