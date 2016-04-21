
set(here ${CMAKE_CURRENT_LIST_DIR})

add_executable(neural ${here}/neural.c)
target_link_libraries(neural mrl m)
