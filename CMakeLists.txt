cmake_minimum_required( VERSION 2.6 )

set( APP_NAME lift )
project( ${APP_NAME} )

set( SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/source )
set( DEP_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dependencies )
set( APP_HELPERS_SRC ${DEP_PATH}/ApplicationHelpers/Source )
set( STATE_MACHINE_SRC ${DEP_PATH}/state_machine/src )

file( GLOB_RECURSE SOURCES ${SRC_PATH}/*.c ${SRC_PATH}/*.cpp ${APP_HELPERS_SRC}/*.cpp ${STATE_MACHINE_SRC}/*.c )
file( GLOB_RECURSE HEADERS ${SRC_PATH}/*.h ${SRC_PATH}/*.hpp ${APP_HELPERS_SRC}/*.h ${STATE_MACHINE_SRC}/*.h )

include_directories( ${SRC_PATH} ${APP_HELPERS_SRC} ${STATE_MACHINE_SRC} )

add_executable( ${APP_NAME} ${SOURCES} )
