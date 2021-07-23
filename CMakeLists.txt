cmake_minimum_required(VERSION 3.5)

project(iaclient LANGUAGES CXX)
#set(CMAKE_INCLUDE_CURRENT_DIR "/home/ingil/Qt5.12.9/5.12.9/gcc_64/lib/cmake/")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/home/ingil/Qt5.12.9/5.12.9/gcc_64/lib/cmake/")
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets Network LinguistTools REQUIRED)

set(TS_FILES iaclient_zh_CN.ts)

if(ANDROID)
  add_library(iaclient SHARED
    main.cpp
    mainwindow.cpp
    logindialog.cpp
    mainwindow.h
    logindialog.h
    mainwindow.ui
    logindialog.ui
    ${TS_FILES}
  )
else()
  add_executable(iaclient
    main.cpp
    mainwindow.cpp
    logindialog.cpp
    loginsetdialog.cpp
    datapackage.cpp
    mainwindow.h
    logindialog.h
    loginsetdialog.h
    datapackage.h
    mainwindow.ui
    logindialog.ui
    loginsetdialog.ui
    ${TS_FILES}
  )
endif()

target_link_libraries(iaclient PRIVATE Qt5::Widgets Qt5::Network)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
