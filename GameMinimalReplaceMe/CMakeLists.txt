cmake_minimum_required( VERSION 3.7 )

project( ProjectMinimal_Project VERSION 0.1 LANGUAGES CXX )

file( GLOB_RECURSE sourcefiles "Game/SourceCommon/*.cpp" "Game/SourceLinux/*.cpp" )
#list( REMOVE_ITEM sourcefiles "${CMAKE_SOURCE_DIR}/Game/SourceLinux/LinuxMainWx.cpp" )
list( REMOVE_ITEM sourcefiles "${CMAKE_SOURCE_DIR}/Game/SourceLinux/LinuxMain.cpp" )

add_executable( ProjectMinimal ${sourcefiles} )

target_include_directories( ProjectMinimal PRIVATE "Game/SourceCommon" "Game/SourceLinux" )

target_compile_definitions( ProjectMinimal PRIVATE MYFW_LINUX=1 )

if( CMAKE_BUILD_TYPE MATCHES Debug )
    target_compile_definitions( ProjectMinimal PRIVATE _DEBUG=1 )
endif()

if( CMAKE_BUILD_TYPE MATCHES wxDebug )
    target_compile_definitions( ProjectMinimal PRIVATE MYFW_USING_WX=1 _FILE_OFFSET_BITS=64 __WXGTK__ )
elseif( CMAKE_BUILD_TYPE MATCHES wxRelease )
    target_compile_definitions( ProjectMinimal PRIVATE MYFW_USING_WX=1 _FILE_OFFSET_BITS=64 __WXGTK__ )
endif()
    
target_include_directories( ProjectMinimal PUBLIC
    "../Framework/MyFramework/SourceCommon"
    "../Framework/MyFramework/SourceLinux"
    "../Framework/MyFramework/SourceWidgets"
    "../Framework/Libraries/Box2D/Box2D"
    "../Framework/Libraries/cJSON"
    "../Framework/Libraries/LodePNG"
    "../Framework/Libraries/wxWidgets/include"
)

target_link_libraries( ProjectMinimal
    ${CMAKE_CURRENT_BINARY_DIR}/../../../Framework/build/${CMAKE_BUILD_TYPE}/libMyFramework.a # full path will allow cmake to detect library updates
    GL pthread openal X11
)

if( CMAKE_BUILD_TYPE MATCHES wxDebug )
    target_link_libraries( ProjectMinimal
        ${CMAKE_CURRENT_BINARY_DIR}/../../../Framework/Libraries/wxWidgets/gtk-build-debug/lib/libwx_gtk3u_xrc-3.1.a
        ${CMAKE_CURRENT_BINARY_DIR}/../../../Framework/Libraries/wxWidgets/gtk-build-debug/lib/libwx_gtk3u_qa-3.1.a
        ${CMAKE_CURRENT_BINARY_DIR}/../../../Framework/Libraries/wxWidgets/gtk-build-debug/lib/libwx_baseu_net-3.1.a
        ${CMAKE_CURRENT_BINARY_DIR}/../../../Framework/Libraries/wxWidgets/gtk-build-debug/lib/libwx_gtk3u_html-3.1.a
        ${CMAKE_CURRENT_BINARY_DIR}/../../../Framework/Libraries/wxWidgets/gtk-build-debug/lib/libwx_gtk3u_adv-3.1.a
        ${CMAKE_CURRENT_BINARY_DIR}/../../../Framework/Libraries/wxWidgets/gtk-build-debug/lib/libwx_gtk3u_core-3.1.a
        ${CMAKE_CURRENT_BINARY_DIR}/../../../Framework/Libraries/wxWidgets/gtk-build-debug/lib/libwx_baseu_xml-3.1.a
        ${CMAKE_CURRENT_BINARY_DIR}/../../../Framework/Libraries/wxWidgets/gtk-build-debug/lib/libwx_baseu-3.1.a
        ${CMAKE_CURRENT_BINARY_DIR}/../../../Framework/Libraries/wxWidgets/gtk-build-debug/lib/libwx_gtk3u_aui-3.1.a
        ${CMAKE_CURRENT_BINARY_DIR}/../../../Framework/Libraries/wxWidgets/gtk-build-debug/lib/libwx_gtk3u_gl-3.1.a
        gthread-2.0
        X11
        Xxf86vm
        SM
        gtk-3
        gdk-3
        pangocairo-1.0
        pango-1.0
        atk-1.0
        cairo-gobject
        cairo
        gdk_pixbuf-2.0
        gio-2.0
        gobject-2.0
        glib-2.0
        Xtst
        png
        expat
        #  wxregexu-3.1
        #  wxtiff-3.1
        #  wxjpeg-3.1
        z
        dl
        m
    )
    target_include_directories( ProjectMinimal PUBLIC
        "../Framework/Libraries/wxWidgets/gtk-build-debug/lib/wx/include/gtk3-unicode-static-3.1" )
elseif( CMAKE_BUILD_TYPE MATCHES wxRelease )
    target_link_libraries( ProjectMinimal
        ${CMAKE_CURRENT_BINARY_DIR}/../../../Framework/Libraries/wxWidgets/gtk-build-release/lib/libwx_baseu-3.1.a
        ${CMAKE_CURRENT_BINARY_DIR}/../../../Framework/Libraries/wxWidgets/gtk-build-release/lib/libwx_gtk3u_core-3.1.a
        ${CMAKE_CURRENT_BINARY_DIR}/../../../Framework/Libraries/wxWidgets/gtk-build-release/lib/libwx_gtk3u_gl-3.1.a
        ${CMAKE_CURRENT_BINARY_DIR}/../../../Framework/Libraries/wxWidgets/gtk-build-release/lib/libwx_gtk3u_aui-3.1.a
    )
    target_include_directories( ProjectMinimal PUBLIC
        "../Framework/Libraries/wxWidgets/gtk-build-release/lib/wx/include/gtk3-unicode-static-3.1" )
endif()

if( CMAKE_BUILD_TYPE MATCHES wxDebug )
    set( CMAKE_BUILD_TYPE Debug )
elseif( CMAKE_BUILD_TYPE MATCHES wxRelease )
    set( CMAKE_BUILD_TYPE Release )
endif()
