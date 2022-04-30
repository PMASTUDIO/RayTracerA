-- premake5.lua
workspace "RayTracerA"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "RayTracerA"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "RayTracerA"
