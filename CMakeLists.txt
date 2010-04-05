project(POCSLabComplex)
set (PROJECT_FILE_NAME POCSLabComplex)

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
	src/blocks
)

################################################################
# src
################################################################

set (src_SRC
	src/main.cpp
	src/mainwindow.cpp
	src/microprocessorwidget.cpp
	src/operations.cpp
)

set (src_HEADERS
	src/mainwindow.h
	src/microprocessorwidget.h
	src/operations.h
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
# blocks
################################################################

set (blocks_SRC
	src/blocks/abstractblock.cpp
	src/blocks/alb1block.cpp
	src/blocks/alb2block.cpp
	src/blocks/alb3block.cpp
	src/blocks/mb1block.cpp
	src/blocks/mb2block.cpp
)

set (blocks_HEADERS
	src/blocks/abstractblock.h
	src/blocks/alb1block.h
	src/blocks/alb2block.h
	src/blocks/alb3block.h
	src/blocks/mb1block.h
	src/blocks/mb2block.h
)


################################################################
# all
################################################################

set (SOURCES
	${src_SRC}
	${dialogs_SRC}
	${blocks_SRC}
)

set (HEADERS
	${src_HEADERS}
	${dialogs_HEADERS}
	${blocks_HEADERS}
)

qt4_wrap_cpp( MOC_SOURCES ${HEADERS} )

#set (RESOURCES resource.qrc)

qt4_add_resources (QRC_SOURCES ${RESOURCES})

#add_executable( ${PROJECT_FILE_NAME} WIN32 ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES})
add_executable( ${PROJECT_FILE_NAME} ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES})

target_link_libraries( ${PROJECT_FILE_NAME} ${QT_LIBRARIES} )


