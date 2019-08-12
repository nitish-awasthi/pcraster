
set(CMAKE_C_COMPILER gcc-7)
set(CMAKE_CXX_COMPILER g++-7)


include(${CMAKE_CURRENT_LIST_DIR}/gcc.cmake)



set(CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} ${PCR_C_FLAGS_GCC7}"
)

set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} ${PCR_CXX_FLAGS_GCC7}"
)
