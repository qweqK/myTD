find_package(Catch2 2.13.8 REQUIRED)


include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2
)

FetchContent_MakeAvailable(Catch2)


add_executable(tests testProg.cpp testContainer.cpp)
add_compile_options(tests PRIVATE --coverage)
add_link_options(tests PRIVATE --coverage)
target_link_libraries(tests matrix Catch2::Catch2WithMain static_loader)

