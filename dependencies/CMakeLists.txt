add_library(dependencies SHARED
  kbhit.cpp)

INSTALL(
    TARGETS dependencies
    LIBRARY DESTINATION lib
)