
set(here ${CMAKE_CURRENT_LIST_DIR})

#add_subdirectory(autogui)
#add_subdirectory(opengl)
#add_subdirectory(sound)

#set(MRL_UI_SOURCES ${MRL_UI_SOURCES})

#set(MRL_UI_LINK_LIBRARIES ${MRL_UI_LINK_LIBRARIES))

#add_library(mrl_ui STATIC ${MRL_UI_SOURCES})
#target_link_libraries(mrl_ui ${MRL_UI_LINK_LIBRARIES})

set(MRL_SOURCES
  ${MRL_SOURCES}
  ${MRL_UI_SOURCES}
  PARENT_SCOPE)

set(MRL_LINK_LIBRARIES
  ${MRL_LINK_LIBRARIES}
  ${MRL_UI_LINK_LIBRARIES}
  PARENT_SCOPE)

