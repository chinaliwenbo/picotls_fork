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
SET(MINICRYPTO_LIBRARY_FILES
    deps/micro-ecc/uECC.c
    deps/cifra/src/aes.c
    deps/cifra/src/blockwise.c
    deps/cifra/src/chacha20.c
    deps/cifra/src/chash.c
    deps/cifra/src/curve25519.c
    deps/cifra/src/drbg.c
    deps/cifra/src/hmac.c
    deps/cifra/src/gcm.c
    deps/cifra/src/gf128.c
    deps/cifra/src/modes.c
    deps/cifra/src/poly1305.c
    deps/cifra/src/sha256.c
    deps/cifra/src/sha512.c)
SET(CORE_FILES
    lib/hpke.c
    lib/picotls.c
    lib/pembase64.c)
SET(CORE_TEST_FILES
    t/hpke.c
    t/picotls.c)

ADD_LIBRARY(picotls-core ${CORE_FILES})
TARGET_LINK_LIBRARIES(picotls-core ${CORE_EXTRA_LIBS})
TARGET_LINK_DIRECTORIES(picotls-core PUBLIC ${CORE_EXTRA_LIBS_DIRS})


INCLUDE_DIRECTORIES(${OPENSSL_INC_DIR})
ADD_LIBRARY(picotls-openssl lib/openssl.c)
TARGET_LINK_LIBRARIES(picotls-openssl ${OPENSSL_CRYPTO_LIBRARIES} ${AEGIS_LIBRARIES} picotls-core ${CMAKE_DL_LIBS})
