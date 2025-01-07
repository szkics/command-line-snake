add_library(gamemodes SHARED
  gamemodes.cpp
  ../timer/timer.cpp
  ../userinteraction/userinteraction.cpp)

INSTALL(
    TARGETS gamemodes
    LIBRARY DESTINATION lib
)