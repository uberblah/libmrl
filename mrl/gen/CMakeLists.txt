
set(here ${CMAKE_CURRENT_LIST_DIR})

set(MRL_GEN_SOURCES
  ${here}/pair.c
  ${here}/list.c
  ${here}/alist.c
  ${here}/pool.c
  ${here}/byteblob.c
#  ${here}/hashtable.c
#  ${here}/hashset.c
)

set(MRL_GEN_LINK_LIBRARIES
)

add_library(mrl_gen STATIC ${MRL_GEN_SOURCES})
target_link_libraries(mrl_gen ${MRL_GEN_LINK_LIBRARIES})

set(MRL_SOURCES
  ${MRL_SOURCES}
  ${MRL_GEN_SOURCES}
  PARENT_SCOPE)

set(MRL_LINK_LIBRARIES
  ${MRL_LINK_LIBRARIES}
  ${MRL_GEN_LINK_LIBRARIES}
  PARENT_SCOPE)

