workspace "lorentz-simulation"
    location "build"
    architecture "x64"
    configurations { "Debug", "Release" }
    cppdialect "C++20"

project "lorentz-simulation"
    kind "ConsoleApp"
    language "C++"
    location "build"    

    defines "SFML_STATIC"
    files { "src/**.cpp", "src/**.hpp", "src/**.h", "libraries/include/ImGui/**.cpp", "assets/**.*", "src/shaders/**.*" }

    includedirs "libraries/*"
    libdirs "libraries/lib"
    links {
        "opengl32",
        "winmm"
    }

filter "configurations:Debug"
    defines "DEBUG"
    symbols "On"
    links {
        "raylib",
        "raylibdll",
    }

filter "configurations:Release"
    defines "RELEASE"
    optimize "Speed"
    links {
        "raylib",
        "raylibdll",
    }