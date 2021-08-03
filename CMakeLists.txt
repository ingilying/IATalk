cmake_minimum_required(VERSION 3.5)

project(iaclient LANGUAGES CXX)
#set(CMAKE_INCLUDE_CURRENT_DIR "/home/ingil/Qt5.12.9/5.12.9/gcc_64/lib/cmake/")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/home/ingil/Qt5.12.9/5.12.9/gcc_64/lib/cmake/")
#set(CMAKE_AUTOUIC ON)
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
qt5_add_resources(QRC_FILES rc.qrc)
set(TS_FILES iaclient_zh_CN.ts)
add_compile_options(-g)
#add_link_options( -g)
include_directories(./Headers ./Sources)

aux_source_directory(Sources ia_sources)
set(ia_headers 
    Headers/mainwindow.h
    Headers/logindialog.h
    Headers/loginsetdialog.h
    Headers/datapackage.h
    Headers/HttpDownload.h
    Headers/ChatMessage.h
    Headers/Chat.h
)

set(ia_ui
    Ui/mainwindow.ui
    Ui/logindialog.ui
    Ui/loginsetdialog.ui
)
qt5_wrap_ui(WRAP_MAIN Ui/mainwindow.ui)
qt5_wrap_ui(WRAP_LOGIN Ui/logindialog.ui)
qt5_wrap_ui(WRAP_LOGINSET Ui/loginsetdialog.ui)
source_group("Ui" FILES ${UI_FILES} ${WRAP_MAIN} ${WRAP_LOGIN} ${WRAP_LOGINSET})
include_directories(${WRAP_FILES})
  add_executable(iaclient
    ${ia_sources}
    ${ia_headers}
    ${ia_ui}
    ${QRC_FILES}
    ${TS_FILES}
    #${WRAP_FILES}
    ${WRAP_MAIN} 
    ${WRAP_LOGIN} 
    ${WRAP_LOGINSET}
  )

target_link_libraries(iaclient PRIVATE Qt5::Widgets Qt5::Network)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
