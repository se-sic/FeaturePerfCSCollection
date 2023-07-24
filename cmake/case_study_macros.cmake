# Adds a new test binary to the collection
macro(ADD_TEST_BINARY name)
  message(STATUS "Adding test binary ${name}")
endmacro(ADD_TEST_BINARY)

# Adds a larger synthetic project to the collection
macro(ADD_PROJECT name)
  string(TOUPPER ${name} NAME)

  option(FPCSC_ENABLE_PROJECT_${NAME}
         "Enable synthetic context senstivitiy cases study." OFF
  )

  if(FPCSC_ENABLE_PROJECT_${NAME} OR FPCSC_ENABLE_ALL)
    message(STATUS "Adding project ${name}")

    add_subdirectory(${name})
  endif()
endmacro(ADD_PROJECT)
