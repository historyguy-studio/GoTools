PROJECT(GoImplicitization)


# Include directories

INCLUDE_DIRECTORIES(
  ${GoImplicitization_SOURCE_DIR}/include
  ${GoToolsCore_SOURCE_DIR}/include
  ${sisl_SOURCE_DIR}/include
  ${newmat_SOURCE_DIR}/include
  )


# Linked in libraries

SET(DEPLIBS
  sisl
  newmat
  GoToolsCore
  )


# Make the GoImplicitization library

FILE(GLOB GoImplicitization_SRCS src/*.C include/*.h)
ADD_LIBRARY(GoImplicitization ${GoImplicitization_SRCS})
TARGET_LINK_LIBRARIES(GoImplicitization ${DEPLIBS})

# This line may be needed only on AMD 64 bit
IF(NOT WIN32)
  SET_TARGET_PROPERTIES(GoImplicitization PROPERTIES COMPILE_FLAGS "-fPIC")
ENDIF(NOT WIN32)


# Apps, examples, tests, ...?

FILE(GLOB GoImplicitization_APPS app/*.C)
FILE(GLOB_RECURSE GoImplicitization_EXAMPLES examples/*.C)
FOREACH(app ${GoImplicitization_APPS} ${GoImplicitization_EXAMPLES})
  GET_FILENAME_COMPONENT(appname ${app} NAME_WE)
  ADD_EXECUTABLE(${appname} ${app})
  TARGET_LINK_LIBRARIES(${appname} GoImplicitization ${DEPLIBS})
ENDFOREACH(app)

# Copy data
ADD_CUSTOM_COMMAND(
  TARGET GoImplicitization
  POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy_directory ${GoImplicitization_SOURCE_DIR}/data 
  ${GoImplicitization_BINARY_DIR}/data
  )


# 'install' target

IF(WIN32)
  # Windows
  # lib
  INSTALL(TARGETS GoImplicitization DESTINATION ${GoTools_INSTALL_PREFIX}/lib)
  # include
  INSTALL(DIRECTORY include/GoTools/implicitization
    DESTINATION ${GoTools_INSTALL_PREFIX}/include/GoTools
    FILES_MATCHING PATTERN "*.h"
    PATTERN ".svn" EXCLUDE
    )
ELSE(WIN32)
  # Linux
  # lib
  INSTALL(TARGETS GoImplicitization DESTINATION lib/GoTools)
  # include
  INSTALL(DIRECTORY include/GoTools/implicitization
    DESTINATION include/GoTools
    FILES_MATCHING PATTERN "*.h"
    PATTERN ".hpp"
    PATTERN ".svn" EXCLUDE
    )
ENDIF(WIN32)