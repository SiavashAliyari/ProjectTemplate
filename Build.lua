-- premake5.lua
workspace "2DEngine"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"
IncludeDir = {}
LibDir = {}

IncludeDir["GLFW"] = "../Vendor/GLFW/include"
LibDir["GLFW"] = "../Vendor/GLFW/lib"


group "Core"
	include "Core/Build-Core.lua"
group ""

include "App/Build-App.lua"