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

include "Oxide"
include "Demo"