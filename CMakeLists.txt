cmake_minimum_required(VERSION 3.13)

include(pico_sdk.cmake)

# Esnures that threads can be found
IF(UNIX)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
ENDIF()

project(ChristmasClock C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

enable_testing()

add_subdirectory(drivers)
add_subdirectory(tests)
add_subdirectory(app)



