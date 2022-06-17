find_path(LP_SOLVE_INCLUDE_DIR
    NAMES
    lp_Hash.h
    lp_SOS.h
    lp_lib.h
    lp_matrix.h
    lp_mipbb.h
    lp_types.h
    lp_utils.h
    PATHS
    /usr/include
    /usr/local/include
)

find_library(LP_SOLVE_LIBRARY
    NAMES
    lpsolve55
    PATHS
    /usr/lib
    /usr/local/lib
)

if(LP_SOLVE_INCLUDE_DIR AND LP_SOLVE_LIBRARY)
    message(STATUS "Library lp solve has found: ${LP_SOLVE_INCLUDE_DIR}")
    set(LP_SOLVE_FOUND TRUE)
    include_directories(${LP_SOLVE_INCLUDE_DIR})
else()
    message(WARNING "Could NOT find library: lp solve.")
endif(LP_SOLVE_INCLUDE_DIR AND LP_SOLVE_LIBRARY)