cmake_minimum_required(VERSION 3.14)

project(QCV VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "$ENV{HOME}/Apps/Qt_5_12/5.12.12/gcc_64")
if (ANDROID)
    add_definitions(-ANDROID_PLATFORM)
    message(STATUS "Android opencv: ")
    set(OpenCV_DIR "$ENV{HOME}/Apps/OpenCV-android-sdk/sdk/native/jni")
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick LinguistTools AndroidExtras REQUIRED)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick LinguistTools AndroidExtras REQUIRED)
else()
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick LinguistTools REQUIRED)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick LinguistTools REQUIRED)
endif()

find_package( OpenCV REQUIRED )
message(STATUS "OpenCV ${OpenCV_DIR}")
message(STATUS "OpenCV_LIBS ${OpenCV_LIBS}")

set(TS_FILES QCV_zh_CN.ts)

# CPP模块源码
set(QC_ANDROIDFILE_SOURCE
    androidfile.h
    androidfile.cpp
)
set(
    QC_UTILS_SOURCE
    previewprovider.h
    previewprovider.cpp
)

set(PROJECT_SOURCES
        main.cpp
        qml.qrc
        ${TS_FILES}
        ${QC_ANDROIDFILE_SOURCE}
        ${QC_UTILS_SOURCE}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QCV
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QCV APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(QCV SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QCV
          ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_compile_definitions(QCV
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(QCV
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick ${OpenCV_LIBS})
if (ANDROID)
    target_link_libraries(QCV
      PRIVATE Qt${QT_VERSION_MAJOR}::AndroidExtras)
endif()

set_target_properties(QCV PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(QCV)
    qt_finalize_executable(QCV)
endif()
