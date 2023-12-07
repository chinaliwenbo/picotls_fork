CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
CMAKE_POLICY(SET CMP0003 NEW)

PROJECT(picotls)

IF (CMAKE_VERSION VERSION_LESS 3.13.0)
  MACRO (TARGET_LINK_DIRECTORIES target scope)
    link_directories(${ARGN})
  ENDMACRO ()
ENDIF ()


SET(CMAKE_C_FLAGS "-std=c99 -Wall -O2 -g ${CC_WARNING_FLAGS} ${CMAKE_C_FLAGS}")
INCLUDE_DIRECTORIES(
    deps/cifra/src/ext
    deps/cifra/src
    deps/micro-ecc
    deps/picotest
    include
    ${CMAKE_CURRENT_BINARY_DIR})

SET(CORE_FILES
    lib/hpke.c
    lib/picotls.c
    lib/pembase64.c)

ADD_LIBRARY(picotls-core ${CORE_FILES})

INCLUDE_DIRECTORIES(${OPENSSL_INC_DIR})
ADD_LIBRARY(picotls-openssl lib/openssl.c ${OPENSLL_LIB_DIR}/libcrypto.a)
