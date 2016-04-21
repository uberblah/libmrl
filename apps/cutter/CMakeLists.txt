
set(here ${CMAKE_CURRENT_LIST_DIR})

add_executable(cutter ${here}/cutter.c)

find_package(OpenGL REQUIRED)

target_link_libraries(cutter
  mrl
  glfw
  ${OPENGL_LIBRARIES}
  ${OPENGL_glu_LIBRARY}
  ${GLFW_LIBRARIES}
)
