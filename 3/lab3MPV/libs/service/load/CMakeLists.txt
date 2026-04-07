find_package(yaml-cpp REQUIRED)

add_library(state_service_impl src/stateServiceImpl.cpp include/stateServiceImpl.h)
target_include_directories(state_service_impl PUBLIC include )
target_link_libraries(state_service_impl yaml-cpp)

add_library(config_service_iml include/configServiceImpl.h src/configServiceImpl.cpp)
target_include_directories(config_service_iml PUBLIC include)
target_link_libraries(config_service_iml yaml-cpp)