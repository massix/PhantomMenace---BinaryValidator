# src folder

include_directories(../include /usr/local/include)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS ../include/*.h)

add_definitions(-Wall)

link_directories(/usr/local/include)

add_executable(PhantomMenaceValidator ${SOURCES})
target_link_libraries(PhantomMenaceValidator PhantomMenace)

set_target_properties(PhantomMenaceValidator PROPERTIES VERSION 1.0.1)

install(TARGETS PhantomMenaceValidator RUNTIME DESTINATION bin)
