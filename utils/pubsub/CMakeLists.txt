
set(UTILS_NAME pubsub)
add_library(${UTILS_NAME} INTERFACE)

target_sources(${UTILS_NAME} INTERFACE
   ${CMAKE_CURRENT_LIST_DIR}/src/publisher.cpp
)

# Pull in pico libraries that we need
target_link_libraries(${UTILS_NAME} INTERFACE
  pico_stdlib
)

target_include_directories(${UTILS_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)