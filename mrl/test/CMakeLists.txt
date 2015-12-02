
set(here ${CMAKE_CURRENT_LIST_DIR})

set(MRL_TEST_SOURCES ${MRL_TEST_SOURCES}
  ${here}/list_cons.c
  ${here}/list_iter.c  
  ${here}/list_reverse.c
  ${here}/list_last.c
  ${here}/list_append.c
  ${here}/alist_get_set.c
  ${here}/pool_basic.c
  ${here}/pool_full.c
  ${here}/pool_refill.c
  ${here}/pool_advanced.c
  ${here}/byteblob_big.c
  ${here}/emu_boardtest.c
  ${here}/emu_proctest.c
  ${here}/emu_ex_tp_test.c
  PARENT_SCOPE)

set(MRL_LINK_TEST ${MRL_LINK_TEST}
  mrl
  PARENT_SCOPE)
