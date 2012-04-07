# src folder

include_directories(../include /usr/local/include)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS ../include/*.h)

add_definitions(-Wall)

link_directories(/usr/local/include)
link_libraries(PhantomMenace)

add_executable(PhantomMenaceValidator ${SOURCES})

install(TARGETS PhantomMenaceValidator RUNTIME DESTINATION bin)
