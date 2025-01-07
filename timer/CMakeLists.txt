add_library(timer SHARED
  timer.cpp
)

INSTALL(
    TARGETS timer
    LIBRARY DESTINATION lib
)