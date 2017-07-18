project(qtrtpvideo)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

find_package(Qt4or5 COMPONENTS Core Gui Quick2 Qml REQUIRED)
find_package(Qt5GStreamer REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${QTGSTREAMER_INCLUDES})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${QTGSTREAMER_FLAGS}")
add_definitions(${QTGSTREAMER_DEFINITIONS})

set(qtrtpvideo_SOURCES main.cpp qtrtpvideo.cpp qtrtpvideoview.cpp)
qt4or5_add_resources(qtrtpvideo_rcc_SOURCES qtrtpvideo.qrc)

add_executable(qtrtpvideo
    ${qtrtpvideo_SOURCES}
    ${qtrtpvideo_rcc_SOURCES}
)
target_link_libraries(qtrtpvideo ${QTGSTREAMER_QUICK_LIBRARIES})
qt4or5_use_modules(qtrtpvideo Core Gui Quick2 Qml)
