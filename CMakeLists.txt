cmake_minimum_required(VERSION 3.14)

project(btrider LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)


set(sources	
	main.cpp
	./source/cmdfunctional.cpp
	./source/textres.cpp
)

set(headers
    ./include/textres.h
    ./include/cmddata.h
    ./include/cmdfunctional.h
)

add_executable(btrider ${sources} ${headers})

target_include_directories(btrider
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(btrider Bthprops.lib)




