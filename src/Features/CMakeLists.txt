file(GLOB FEATURES_SOURCES
    "Battle/Actions/*.cpp"
    "Battle/Combat/*.cpp"
    "Units/Components/Health/*.cpp"
    "Units/Services/*.cpp"
    "Simulation/Managers/*.cpp"
    "Map/*.cpp"
    "Map/DistanceCalculators/*.cpp"
    "Units/Types/*.cpp"
)

add_library(Features STATIC ${FEATURES_SOURCES})

target_link_libraries(Features PRIVATE Core)

target_include_directories(Features PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

set_target_properties(Features PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
