configure_file(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

add_executable(matrix main.cpp)

add_library(utils version.cpp)

set_target_properties(matrix utils PROPERTIES
   CXX_STANDARD 14
   CXX_STANDARD_REQUIRED ON
   COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

target_link_libraries(matrix utils)

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS matrix RUNTIME DESTINATION bin)
