
set(here ${CMAKE_CURRENT_LIST_DIR})

add_executable(eup ${here}/eup.c)

find_package(OpenGL REQUIRED)

target_link_libraries(eup
  mrl
  glfw
  ${OPENGL_LIBRARIES}
  ${OPENGL_glu_LIBRARY}
  ${GLFW_LIBRARIES}
)
