CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
CMAKE_POLICY(SET CMP0003 NEW)

PROJECT(picotls)

IF (CMAKE_VERSION VERSION_LESS 3.13.0)
  MACRO (TARGET_LINK_DIRECTORIES target scope)
    link_directories(${ARGN})
  ENDMACRO ()
ENDIF ()

# SET(CMAKE_C_FLAGS "-std=c99 -Wall -O2 -g ${CC_WARNING_FLAGS} ${CMAKE_C_FLAGS}")
SET(CMAKE_C_FLAGS "-std=c99 -Wall -O0 -g3 ${CC_WARNING_FLAGS} ${CMAKE_C_FLAGS}")


ADD_LIBRARY(picotls-core lib/hpke.c lib/picotls.c lib/pembase64.c)
target_include_directories(picotls-core
    PUBLIC deps/cifra/src/ext
    PUBLIC deps/cifra/src
    PUBLIC deps/micro-ecc
    PUBLIC deps/picotest
    PUBLIC include
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# 加密库的编译, 使用openssl的库来做
ADD_LIBRARY(picotls-openssl lib/openssl.c)
target_include_directories(picotls-openssl
    PUBLIC /opt/openssl/3.0.10/include
    PUBLIC include
)

