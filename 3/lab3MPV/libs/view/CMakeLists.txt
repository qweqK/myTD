add_library(graphic_view include/graphicView.h src/graphicView.cpp)
target_include_directories(graphic_view PUBLIC include)
target_link_libraries( graphic_view PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        view
)