
set(here ${CMAKE_CURRENT_LIST_DIR})

#set(MRL_NET_SOURCES ${MRL_NET_SOURCES}
#  ${here}/udp.c
#  ${here}/tcp.c
#  ${here}/http.c
#  ${here}/ftp.c
#  ${here}/nsp.c #network sync protocol
#  ${here}/rtnsp.c #realtime network sync protocol
#  ${here}/i2p.c #i2p support! yay!
#)

#set(MRL_GEN_LINK_LIBRARIES ${MRL_NET_LINK_LIBRARIES}
#)

#add_library(mrl_net STATIC ${MRL_NET_SOURCES})
#target_link_libraries(mrl_net ${MRL_NET_LINK_LIBRARIES})

set(MRL_SOURCES
  ${MRL_SOURCES}
  ${MRL_NET_SOURCES}
  PARENT_SCOPE)

set(MRL_LINK_LIBRARIES
  ${MRL_LINK_LIBRARIES}
  ${MRL_NET_LINK_LIBRARIES}
  PARENT_SCOPE)

