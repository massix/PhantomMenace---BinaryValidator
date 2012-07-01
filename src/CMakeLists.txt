# src folder

file(GLOB SOURCES *.cpp)

set(PhantomMenaceVersionMajor 1)
set(PhantomMenaceVersionBinComp 3)
set(PhantomMenaceVersionMinor 1)
set(PhantomMenaceVersion 
    ${PhantomMenaceVersionMajor}.${PhantomMenaceVersionBinComp}.${PhantomMenaceVersionMinor})

add_definitions(-Wall 
    -DVALIDATORVERSIONMAJ=${PhantomMenaceVersionMajor}
    -DVALIDATORVERSIONBIN=${PhantomMenaceVersionBinComp}
    -DVALIDATORVERSIONMIN=${PhantomMenaceVersionMinor})

find_package(PhantomMenace REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

add_executable(PhantomMenaceValidator ${SOURCES})

include_directories(${PhantomMenace_INCLUDE_DIR} 
    ${Boost_LIBRARIES})

target_link_libraries(PhantomMenaceValidator 
    ${PhantomMenace_LIBRARY} ${Boost_LIBRARIES})

set_target_properties(PhantomMenaceValidator PROPERTIES VERSION ${PhantomMenaceVersion})

install(TARGETS PhantomMenaceValidator RUNTIME DESTINATION bin)
