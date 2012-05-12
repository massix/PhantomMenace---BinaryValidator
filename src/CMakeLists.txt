# src folder

include_directories(../include /usr/local/include)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS ../include/*.h)

add_definitions(-Wall)

find_package(PhantomMenace REQUIRED)
add_executable(PhantomMenaceValidator ${SOURCES})

include_directories(${PhantomMenace_INCLUDE_DIR})
target_link_libraries(PhantomMenaceValidator ${PhantomMenace_LIBRARY})

set_target_properties(PhantomMenaceValidator PROPERTIES VERSION 1.0.1)

install(TARGETS PhantomMenaceValidator RUNTIME DESTINATION bin)
