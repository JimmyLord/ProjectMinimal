-- This is not a complete premake5 lua script, it's meant to be included from another script that defines the workspace.
-- Like this, for example:
--     local rootDir = os.getcwd();
--     os.chdir( "../Engine/MyEngine/" )
--     include( "premake5inc.lua" )
--     os.chdir( rootDir )

-- Global Build Settings
if PremakeConfig_UseMono == nil then
    PremakeConfig_UseMono = false
end
if PremakeConfig_UseMemoryTracker == nil then
    PremakeConfig_UseMemoryTracker = true
end

project "MinimalReplaceMe"
    configurations      { "Debug", "Release" }
    dependson           { "Box2D", "MyFramework" }
    kind                "WindowedApp"
    language            "C++"
    targetdir           "$(SolutionDir)Output/%{cfg.platform}-%{prj.name}-%{cfg.buildcfg}"
    objdir              "$(SolutionDir)Output/Intermediate/%{cfg.platform}-%{prj.name}-%{cfg.buildcfg}"
    pchheader           "GamePCH.h"
    pchsource           "Game/SourceCommon/GamePCH.cpp"
    debugdir            "$(SolutionDir)../GameMinimalReplaceMe/Game"

    includedirs {
        "Game/SourceCommon",
        "$(SolutionDir)../Framework/Libraries/b2Settings",
        "$(SolutionDir)../Framework/Libraries/Box2D/include",
        "$(SolutionDir)../Framework/Libraries/Box2D/src",
    }

    files {
        "Game/SourceCommon/**.cpp",
        "Game/SourceCommon/**.h",
        "../.gitignore",
        "../premake5.lua",
        "../PremakeGenerateBuildFiles.bat",
        "../Windows-CreateSymLinksForData.bat",
        "premake5inc.lua",
        "Game/Data/**.glsl",
    }

    vpaths {
        -- Place these files in the root of the project.
        [""] = {
            "../.gitignore",
            "../premake5.lua",
            "../PremakeGenerateBuildFiles.bat",
            "../Windows-CreateSymLinksForData.bat",
            "premake5inc.lua",
        },
        -- Place the SourceCommon and SourceEditor folders in the root of the project.
        ["*"] = {
            "Game",
        },
    }

    links {
        "MyFramework",
        "Box2D",
    }

    filter "system:windows"
        defines         "MYFW_WINDOWS"
        systemversion   "latest"
        characterset    "MBCS"

        files {
            "Game/SourceWindows/**.cpp",
            "Game/SourceWindows/**.h",
        }

        links {
            "pthreadVC2",
            "delayimp",
            "Ws2_32",
            "opengl32",
            "xinput"
        }

        linkoptions { "/DELAYLOAD:pthreadVC2.dll" }

    filter { "system:windows", "platforms:x86" }
        libdirs {
            "../Framework/Libraries/pthreads-w32/lib/x86",
        }
        
    filter { "system:windows", "platforms:x64" }
        libdirs {
            "../Framework/Libraries/pthreads-w32/lib/x64",
        }

    filter { "system:windows", "files:Game/SourceWindows/WinMainWx.*" }
        flags           "ExcludeFromBuild"

    filter "configurations:Debug or EditorDebug"
        defines         "_DEBUG"
        symbols         "on"

    filter "configurations:Release or EditorRelease"
        defines         "NDEBUG"
        optimize        "Full"

    filter "configurations:EditorDebug or EditorRelease"
        defines         { "MYFW_EDITOR", "MYFW_USING_IMGUI" }

if PremakeConfig_UseMono == true then
    filter {}
        defines         "MYFW_USE_MONO"
        links           "mono-2.0-sgen"
end

if PremakeConfig_UseMemoryTracker == true then
    filter "configurations:Debug or EditorDebug or EditorRelease"
        defines         "MYFW_USE_MEMORY_TRACKER"
end
