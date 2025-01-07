add_library(menu SHARED
  menu.cpp)

INSTALL(
    TARGETS menu
    LIBRARY DESTINATION lib
)