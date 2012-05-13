# src folder

include_directories(../include /usr/local/include)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS ../include/*.h)

set(PhantomMenaceVersionMajor 1)
set(PhantomMenaceVersionBinComp 3)
set(PhantomMenaceVersionMinor 0)
set(PhantomMenaceVersion 
    ${PhantomMenaceVersionMajor}.${PhantomMenaceVersionBinComp}.${PhantomMenaceVersionMinor})

add_definitions(-Wall 
    -DVALIDATORVERSIONMAJ=${PhantomMenaceVersionMajor}
    -DVALIDATORVERSIONBIN=${PhantomMenaceVersionBinComp}
    -DVALIDATORVERSIONMIN=${PhantomMenaceVersionMinor})

find_package(PhantomMenace REQUIRED)
find_package(Boost REQUIRED)

add_executable(PhantomMenaceValidator ${SOURCES})

include_directories(${PhantomMenace_INCLUDE_DIR} 
    ${Boost_LIBRARIES})

target_link_libraries(PhantomMenaceValidator 
    ${PhantomMenace_LIBRARY} ${Boost_LIBRARIES})

set_target_properties(PhantomMenaceValidator PROPERTIES VERSION ${PhantomMenaceVersion})

install(TARGETS PhantomMenaceValidator RUNTIME DESTINATION bin)
