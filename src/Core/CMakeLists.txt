file(GLOB CORE_SOURCES
    "Battle/Actions/*.cpp"
    "Battle/Actions/*.hpp"
    "Battle/Combat/*.hpp"
    "Units/Components/Health/*.hpp"
    "Units/Components/Movement/*.cpp"
    "Units/Components/Movement/*.hpp"
    "Units/Services/*.hpp"
    "Simulation/*.cpp"
    "Simulation/*.hpp"
    "Simulation/Managers/*.hpp"
    "Map/*.cpp"
    "Map/*.hpp"
    "Units/*.cpp"
    "Units/*.hpp"
)

add_library(Core STATIC ${CORE_SOURCES})

target_include_directories(Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

set_target_properties(Core PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
