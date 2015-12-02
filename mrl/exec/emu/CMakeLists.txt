
set(here ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(dev)
add_subdirectory(example)

set(MRL_EXEC_EMU_SOURCES ${MRL_EXEC_EMU_SOURCES}
  ${here}/board.c
  ${here}/processor.c
)

set(MRL_EXEC_EMU_LINK_LIBRARIES ${MRL_EXEC_EMU_LINK_LIBRARIES}
)

add_library(mrl_exec_emu STATIC ${MRL_EXEC_EMU_SOURCES})
target_link_libraries(mrl_exec_emu ${MRL_EXEC_EMU_LINK_LIBRARIES})

set(MRL_EXEC_SOURCES
  ${MRL_EXEC_SOURCES}
  ${MRL_EXEC_EMU_SOURCES}
  PARENT_SCOPE)

set(MRL_EXEC_LINK_LIBRARIES
  ${MRL_EXEC_LINK_LIBRARIES}
  ${MRL_EXEC_EMU_LINK_LIBRARIES}
  PARENT_SCOPE)

