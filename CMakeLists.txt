cmake_minimum_required(VERSION 3.24)
project(AdvancedCalculator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Widgets Gui Core Charts)

include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(nlohmann_json)

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE APP_HEADERS CONFIGURE_DEPENDS src/*.h)

qt_add_executable(advanced_calculator
    ${APP_SOURCES}
    ${APP_HEADERS}
    resources/resources.qrc
)

target_include_directories(advanced_calculator PRIVATE src)

target_link_libraries(advanced_calculator PRIVATE
    Qt6::Widgets Qt6::Gui Qt6::Core Qt6::Charts nlohmann_json::nlohmann_json
)

if(WIN32)
    target_compile_definitions(advanced_calculator PRIVATE NOMINMAX)
endif()

install(TARGETS advanced_calculator RUNTIME DESTINATION bin)
