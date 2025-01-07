add_library(snake SHARED
  snake.cpp)

INSTALL(
    TARGETS snake
    LIBRARY DESTINATION lib
)