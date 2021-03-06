# sudo apt install libboost-system-dev
# sudo apt install libwebsocketpp-dev
# sudo apt install libjsoncpp-dev
# sudo apt install libssl-dev
# sudo apt install uuid-dev

cmake_minimum_required (VERSION 3.0.2)
project (rpi-intercom)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

# add_definitions(-DUSE_HTTPS)

# To fix "relocation R_X86_64_32 against `.rodata.str1.1' can not be used when making a PIE object" error on Unbuntu 18.04
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie")

set(BOOST_MIN_VERSION "1.39.0")
find_package(Boost ${BOOST_MIN_VERSION} REQUIRED COMPONENTS system)

find_package(jsoncpp REQUIRED)
# find_package(ssl REQUIRED) TODO
# find_package(uuid REQUIRED) TODO

file (GLOB SOURCE_FILES src/*.cpp)

add_executable(rpi-intercom ${SOURCE_FILES})
target_link_libraries(rpi-intercom pthread boost_system uuid asound ssl crypto jsoncpp)