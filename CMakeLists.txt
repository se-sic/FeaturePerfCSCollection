cmake_minimum_required(VERSION 3.13)

project(FeaturePerformanceCaseStudie C CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(case_study_macros)

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Setup options
option(FPCSC_ENABLE_ALL
       "Override all project choices and enable all projects and test builds"
       OFF
)
option(FPCSC_ENABLE_SRC "Enable source builds" OFF)

option(FPCSC_USE_LIBCXX "Use libc++" ON)

set(VARA_TRACING_OPTIONS
    print
    perf_infl_trace
    trace_event
    udst
    udst_raw
    instr_verify
)
set(VARA_TRACE CACHE STRING "Enable VaRA Tracing")
set_property(CACHE VARA_TRACE PROPERTY STRINGS ${VARA_TRACING_OPTIONS})

if(VARA_TRACE)
  if(VARA_TRACE IN_LIST VARA_TRACING_OPTIONS)
    message(STATUS "Enabling VaRA Tracing with option '${VARA_TRACE}'")
    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -fvara-feature -fsanitize=vara \
        -fvara-instr=${VARA_TRACE} -flto -fuse-ld=lld \
        -flegacy-pass-manager -fno-omit-frame-pointer \
        -fvara-instruction-threshold=0 -g -O0"
    )
    add_link_options("-flto")
  else()
    message(WARNING "Unrecognized option for VARA_TRACE: '${VARA_TRACE}'.\
         Supported values: ${VARA_TRACING_OPTIONS}"
    )
  endif()
endif()

include_directories(external/FeaturePerfUtilities/include/)

if(FPCSC_ENABLE_SRC OR FPCSC_ENABLE_ALL)
  add_subdirectory(src)
endif()

if(FPCSC_USE_LIBCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()
add_subdirectory(projects)
