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
	src/dialogs
)

################################################################
# src
################################################################

set (src_SRC
	src/main.cpp
	src/mainwindow.cpp
	src/abstractblock.cpp
	src/microprocessorwidget.cpp
	src/operations.cpp
	src/alb1block.cpp
)

set (src_HEADERS
	src/mainwindow.h
	src/abstractblock.h
	src/microprocessorwidget.h
	src/operations.h
	src/alb1block.h
)

################################################################
# dialogs
################################################################

set (dialogs_SRC
	src/dialogs/operationdialog.cpp
)

set (dialogs_HEADERS
	src/dialogs/operationdialog.h
)


################################################################
# all
################################################################

set (SOURCES
	${src_SRC}
	${dialogs_SRC}
)

set (HEADERS
	${src_HEADERS}
	${dialogs_HEADERS}
)

qt4_wrap_cpp( MOC_SOURCES ${HEADERS} )

#set (RESOURCES resource.qrc)

qt4_add_resources (QRC_SOURCES ${RESOURCES})

#add_executable( POCSLabComplex WIN32 ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES})
add_executable( POCSLabComplex ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES})

target_link_libraries( POCSLabComplex ${QT_LIBRARIES} )


