include_directories(include)
add_subdirectory(include)

include_directories(libs)
add_subdirectory(libs)

add_subdirectory(loader)

include_directories(containerClass)
add_subdirectory(containerClass)


include(FetchContent)
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)
FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(sfml)

add_executable(lab3Copy main.cpp )
target_link_libraries(lab3Copy
        static_loader
        sfml-graphics
        sfml-window
        sfml-audio
        sfml-system
        nlohmann_json::nlohmann_json
        graphic_view
)


add_subdirectory(tests)
include_directories(tests)

find_package(Doxygen REQUIRED)

if(DOXYGEN_FOUND)
    set(DOXYGEN_EXCLUDE "${CMAKE_BINARY_DIR}")
    set(DOXYGEN_EXCLUDE_EXTERNAL YES)
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_RECURSIVE YES)
    set(DOXYGEN_FILE_PATTERNS *.h *.hpp *.cpp)
    set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/docs")
    doxygen_add_docs(doxygen_docs
            "${CMAKE_CURRENT_SOURCE_DIR}/include"
            "${CMAKE_CURRENT_SOURCE_DIR}/libs"
            "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/containerClass"

    )
endif()