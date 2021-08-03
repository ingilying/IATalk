cmake_minimum_required(VERSION 3.5)
project(IATalk)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH /home/ingil/Qt5.12.9/5.12.9/gcc_64/lib/cmake)

set(CMAKE_BUILD_TYPE DEBUG)

find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Sql REQUIRED)
#set (CMAKE_CXX_FLAGS “${CMAKE_CXX_FLAGS} -g”)

include_directories(./Headers ./Sources)

aux_source_directory(Sources ia_sources)
#aux_source_directory(Headers ia_headers)
#target_include_directories(IATalk PUBLIC Headers)
# set(SOURCEFILES iaserver.cpp
#                 iatcpclient.cpp
#                 iatcpserver.cpp
#                 datapackage.cpp
#                 database.cpp
#                 main.cpp)
set(ia_headers Headers/iaserver.h
            Headers/iatcpserver.h
            Headers/iatcpclient.h
            Headers/datapackage.h
            Headers/database.h
            Headers/tools.h)
add_executable(iatalk ${ia_headers} ${ia_sources})

target_link_libraries(iatalk Qt5::Core Qt5::Network Qt5::Sql)
