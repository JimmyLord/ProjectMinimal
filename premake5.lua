------------------------------------------------ Pure Lua ---------------------------------------------------

-- Copy some dlls into the OpenCVTest folder if they're not already there.
function FileExists(name)
   local f = io.open( name,"r" )
   if f ~= nil then io.close( f ) return true else return false end
end

function CopyFile(source, destination)
    if( FileExists( destination ) == false ) then
        print( "Copying " .. source )
        local ret, err = os.copyfile( source, destination )
        if ret == nil then print( err ) end
        print( "done" )
    end
end

monoInstallationPath = "C:/Program Files (x86)/Mono" -- TODO: Don't hardcode the path to mono installation.

CopyFile( "Framework/Libraries/pthreads-w32/dll/x64/pthreadVC2.dll", "GameMinimalReplaceMe/Game/pthreadVC2-x64.dll" )
CopyFile( "Framework/Libraries/pthreads-w32/dll/x86/pthreadVC2.dll", "GameMinimalReplaceMe/Game/pthreadVC2-x86.dll" )

-- Helper to include other premake.lua files.
local rootFolder = os.getcwd()

local buildFolder = os.getcwd() .. "/build/"
os.mkdir( buildFolder )

BuildSingleProjectPremake = function(folder, filename)
    os.chdir( folder )
    include( filename )
    os.chdir( rootFolder )
end

-- Premake configuration options
PremakeConfig_UseMemoryTracker = true
PremakeConfig_UseMono = false

-- Workspace
workspace "MinimalReplaceMe"
    configurations  { "Debug", "Release" }
    location        ( buildFolder )
    startproject    "MinimalReplaceMe"
    cppdialect      "C++17"

    filter "system:windows"
        platforms       { "x86", "x64" }

BuildSingleProjectPremake( "GameMinimalReplaceMe/", "premake5inc.lua" )
BuildSingleProjectPremake( "Framework/", "premake5inc.lua" )

group "Physics"
    BuildSingleProjectPremake( "Framework/Libraries/", "premake5inc-box2d.lua" )
group ""
