add_library(headers SHARED
  headers.cpp)

INSTALL(
    TARGETS headers
    LIBRARY DESTINATION lib
)