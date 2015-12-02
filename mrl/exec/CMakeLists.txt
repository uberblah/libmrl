
set(here ${CMAKE_CURRENT_LIST_DIR})

#add_subdirectory(eqtpool)
#add_subdirectory(ecs) #entity component system
include_directories(${here})
add_subdirectory(emu)
#add_subdirectory(firth)
#add_subdirectory(schyme)

set(MRL_EXEC_SOURCES ${MRL_EXEC_SOURCES}
)

set(MRL_EXEC_LINK_LIBRARIES ${MRL_EXEC_LINK_LIBRARIES}
)

add_library(mrl_exec STATIC ${MRL_EXEC_SOURCES})
target_link_libraries(mrl_exec ${MRL_EXEC_LINK_LIBRARIES})

set(MRL_SOURCES
  ${MRL_SOURCES}
  ${MRL_EXEC_SOURCES}
  PARENT_SCOPE)

set(MRL_LINK_LIBRARIES
  ${MRL_LINK_LIBRARIES}
  ${MRL_EXEC_LINK_LIBRARIES}
  PARENT_SCOPE)

