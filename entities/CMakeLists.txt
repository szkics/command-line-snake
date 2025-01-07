add_library(entities SHARED
  entities.cpp)

INSTALL(
    TARGETS entities
    LIBRARY DESTINATION lib
)