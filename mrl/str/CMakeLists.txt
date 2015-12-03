
set(here ${CMAKE_CURRENT_LIST_DIR})

set(MRL_STR_SOURCES ${MRL_STR_SOURCES}
  ${here}/strsplit.c
  ${here}/strtrim.c
)

set(MRL_STR_LINK_LIBRARIES ${MRL_STR_LINK_LIBRARIES}
)

add_library(mrl_str STATIC ${MRL_STR_SOURCES})
add_dependencies(mrl_str mrl_gen)
target_link_libraries(mrl_str mrl_gen ${MRL_STR_LINK_LIBRARIES})

set(MRL_SOURCES
  ${MRL_SOURCES}
  ${MRL_STR_SOURCES}
  PARENT_SCOPE)

set(MRL_LINK_LIBRARIES
  ${MRL_LINK_LIBRARIES}
  ${MRL_STR_LINK_LIBRARIES}
  PARENT_SCOPE)

