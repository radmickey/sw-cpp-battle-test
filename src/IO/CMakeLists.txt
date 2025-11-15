file(GLOB IO_SOURCES
    "*.cpp"
    "*.hpp"
    "Commands/*.cpp"
    "Commands/*.hpp"
    "Events/*.cpp"
    "Events/*.hpp"
    "System/*.cpp"
    "System/*.hpp"
    "System/details/*.cpp"
    "System/details/*.hpp"
)

add_library(IO STATIC ${IO_SOURCES})

target_include_directories(IO PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

set_target_properties(IO PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
