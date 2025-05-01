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

option(FPCSC_USE_LIBCXX "Use libc++" OFF)

include_directories(external/FeaturePerfUtilities/include/)

if(FPCSC_ENABLE_SRC OR FPCSC_ENABLE_ALL)
  add_subdirectory(src)
endif()

if(FPCSC_USE_LIBCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()
add_subdirectory(projects)
