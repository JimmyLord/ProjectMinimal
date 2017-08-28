cmake_minimum_required( VERSION 3.7 )

set( CMAKE_BUILD_TYPE Debug )

project( ProjectMinimal_Project VERSION 0.1 LANGUAGES CXX )

file( GLOB_RECURSE sourcefiles "Game/SourceCommon/*.cpp" "Game/SourceLinux/*.cpp" )
list( REMOVE_ITEM sourcefiles "${CMAKE_SOURCE_DIR}/Game/SourceLinux/LinuxMainWx.cpp" )

add_executable( ProjectMinimal ${sourcefiles} )

target_include_directories( ProjectMinimal PRIVATE "Game/SourceCommon" "Game/SourceLinux" )
target_compile_definitions( ProjectMinimal PRIVATE _DEBUG=1 MYFW_LINUX=1 )

target_include_directories( ProjectMinimal PUBLIC
    "../Framework/MyFramework/SourceCommon"
    "../Framework/MyFramework/SourceLinux"
    "../Framework/Libraries/Box2D/Box2D"
    "../Framework/Libraries/cJSON"
    "../Framework/Libraries/LodePNG"
)

target_link_libraries( ProjectMinimal
    ${CMAKE_CURRENT_BINARY_DIR}/../../Framework/build/libMyFramework.a # full path will allow cmake to detect library updates
    GL pthread openal X11
)
