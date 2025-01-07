add_library(userinteraction SHARED
  userinteraction.cpp
)

INSTALL(
    TARGETS userinteraction
    LIBRARY DESTINATION lib
)d