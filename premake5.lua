-- premake5.lua
workspace "GameEngine"
   configurations { "Debug", "Release" }
   platforms { "x64" }


project "GameEngine"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"
   location "build"
   pchheader "pch.h"
   pchsource "src/pch.cpp"
   forceincludes { "pch.h" }

   defines { 'PROJECT_ROOT="' .. _MAIN_SCRIPT_DIR .. '/"' }
   defines { "IMGUI_IMPL_OPENGL_LOADER_GLAD" }


   libdirs { "thirdparty/SDL3-3.3.6/lib/x64" }
   links { "SDL3" }

   includedirs { "src/**", "include/**", "src", "include" }
   includedirs { "thirdparty/SDL3-3.3.6/include" }
   includedirs { "thirdparty/glad/include" }
   includedirs { "thirdparty/nlohmann" }
   includedirs { "thirdparty/glm-1.0.2"}
   includedirs { "thirdparty/imgui-1.92.4" }
   includedirs { "thirdparty/imgui-1.92.4/backends" }

   files { "src/**.h", "src/**.hpp", "src/**.c", "src/**.cpp", "include/**.h", "include/**.hpp" }

   files { "shaders/**.glsl" }

   files { "**.lua", "**.json"}

   files { ".gitignore" }

   -- OpenGL
   files { "thirdparty/glad/src/glad.cpp" }
   
   -- Imgui 
   files { "thirdparty/imgui-1.92.4/imgui*.cpp" }
   files { "thirdparty/imgui-1.92.4/backends/imgui_impl_sdl3.cpp" }
   files { "thirdparty/imgui-1.92.4/backends/imgui_impl_opengl3.cpp" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"