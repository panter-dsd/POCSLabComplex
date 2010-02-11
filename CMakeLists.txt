project(POCSLabComplex)
cmake_minimum_required( VERSION 2.6 )

#SET (CMAKE_BUILD_TYPE Release)
SET (CMAKE_BUILD_TYPE Debug)

INCLUDE(FindQt4)
find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE})
add_definitions(-DUNICODE)

include_directories(
	src
	src/core
)

################################################################
# src
################################################################

set (src_SRC
	src/main.cpp
	src/mainwindow.cpp
)

set (src_HEADERS
	src/mainwindow.h
)

################################################################
# core
################################################################

set (core_SRC
	src/core/adder.cpp
	src/core/multiplier.cpp
)

set (core_HEADERS
	src/core/abstractcomputerunit.h
	src/core/adder.h
	src/core/multiplier.h
)

################################################################
# all
################################################################

set (SOURCES
	${src_SRC}
	${core_SRC}
)

set (HEADERS
	${src_HEADERS}
	${core_HEADERS}
)

qt4_wrap_cpp( MOC_SOURCES ${HEADERS} )

#set (RESOURCES resource.qrc)

qt4_add_resources (QRC_SOURCES ${RESOURCES})

#add_executable( POCSLabComplex WIN32 ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES})
add_executable( POCSLabComplex ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES})

target_link_libraries( POCSLabComplex ${QT_LIBRARIES} )


