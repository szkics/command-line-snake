add_library(gamelogic SHARED
  gamelogic.cpp
  ../dependencies/kbhit.cpp)

INSTALL(
    TARGETS gamelogic
    LIBRARY DESTINATION lib
)