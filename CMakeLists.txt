cmake_minimum_required(VERSION 3.15.0)

include(FetchContent)

FetchContent_Declare(
    vst3sdk
    GIT_REPOSITORY https://github.com/steinbergmedia/vst3sdk.git
    GIT_TAG v3.7.4_build_25
)

FetchContent_MakeAvailable(vst3sdk)

if(NOT vst3sdk_SOURCE_DIR)
    message(FATAL_ERROR "Path to VST3 SDK is empty!")
endif()

project(StackOverflowFx)

set(SMTG_VSTGUI_ROOT "${vst3sdk_SOURCE_DIR}")
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(StackOverflowFx
    source/version.h
    source/stackoverflowcids.h
    source/stackoverflowprocessor.h
    source/stackoverflowprocessor.cpp
    source/stackoverflowcontroller.h
    source/stackoverflowcontroller.cpp
    source/stackoverflowentry.cpp
)

#- VSTGUI Wanted ----
if(SMTG_ADD_VSTGUI)
    target_sources(StackOverflowFx
        PRIVATE
            resource/stackoverfloweditor.uidesc
    )
    target_link_libraries(StackOverflowFx
        PRIVATE
            vstgui_support
    )
    smtg_target_add_plugin_resources(StackOverflowFx
        RESOURCES
            "resource/stackoverfloweditor.uidesc"
    )
endif(SMTG_ADD_VSTGUI)
# -------------------

smtg_target_add_plugin_snapshots (StackOverflowFx
    RESOURCES
        resource/5A6A2AABAF505D3A8B4AF67F5E9BE0C6_snapshot.png
        resource/5A6A2AABAF505D3A8B4AF67F5E9BE0C6_snapshot_2.0x.png
)

target_link_libraries(StackOverflowFx
    PRIVATE
        sdk
)

if(SMTG_MAC)
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.12)
    smtg_target_set_bundle(StackOverflowFx
        BUNDLE_IDENTIFIER org.vst3qa.stackoverflowfx
        INFOPLIST "${CMAKE_CURRENT_LIST_DIR}/resource/Info.plist" PREPROCESS
    )
    smtg_target_set_debug_executable(StackOverflowFx
        "/Applications/VST3PluginTestHost.app"
        "--pluginfolder;$(BUILT_PRODUCTS_DIR)"
    )
elseif(SMTG_WIN)
    target_sources(StackOverflowFx PRIVATE 
        resource/win32resource.rc
    )
    if(MSVC)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT StackOverflowFx)

        smtg_target_set_debug_executable(StackOverflowFx
            "$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
            "--pluginfolder \"$(OutDir)/\""
        )
    endif()
endif(SMTG_MAC)
