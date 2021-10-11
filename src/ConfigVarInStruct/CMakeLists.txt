add_test_binary("ConfigVarInStruct")

add_executable(
  CVISLocal

  CVIS_local_main.c
)

add_executable(
  CVISGlobal

  CVIS_global_main.c
)

add_executable(
  CVISPointer

  CVIS_pointer_main.c
)
