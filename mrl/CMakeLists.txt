
add_subdirectory(gen)
add_subdirectory(exec)
add_subdirectory(net)
add_subdirectory(ui)
add_subdirectory(3d)
add_subdirectory(test)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")
add_library(mrl STATIC ${MRL_SOURCES})
target_link_libraries(mrl ${MRL_LINK_LIBRARIES})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
foreach(test_source ${MRL_TEST_SOURCES})
    string(REPLACE ".c" "" testname ${test_source})
    string(REPLACE ${PROJECT_SOURCE_DIR} "" testname ${testname})
    string(REPLACE "/" "_" testname ${testname})
    add_executable(${testname}_test ${test_source})
    target_link_libraries(${testname}_test ${MRL_LINK_TEST})
    add_test(${testname} ${testname}_test)
endforeach(test_source ${MRL_TEST_SOURCES})

