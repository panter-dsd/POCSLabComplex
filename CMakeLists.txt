project(POCSLabComplex)
set (PROJECT_FILE_NAME POCSLabComplex)

cmake_minimum_required( VERSION 2.6 )

SET (CMAKE_BUILD_TYPE Release)
#SET (CMAKE_BUILD_TYPE Debug)

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
	src/switchboardwidget.cpp
	src/inputwidget.cpp
	src/outputwidget.cpp
	src/microcircuitwidget.cpp
)

set (src_HEADERS
	src/mainwindow.h
	src/microprocessorwidget.h
	src/operations.h
	src/switchboardwidget.h
	src/inputwidget.h
	src/outputwidget.h
	src/microcircuitwidget.h
)

################################################################
# dialogs
################################################################

set (dialogs_SRC
	src/dialogs/operationdialog.cpp
	src/dialogs/inputdialog.cpp
	src/dialogs/switchboarddialog.cpp
	src/dialogs/reportdialog.cpp
	src/dialogs/aboutdialog.cpp
)

set (dialogs_HEADERS
	src/dialogs/operationdialog.h
	src/dialogs/inputdialog.h
	src/dialogs/switchboarddialog.h
	src/dialogs/reportdialog.h
	src/dialogs/aboutdialog.h
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

set (RESOURCES resource.qrc)

qt4_add_resources (QRC_SOURCES ${RESOURCES})

if(MINGW)
  ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/pocslabcomplex_rc.o
  COMMAND windres.exe -I${CMAKE_CURRENT_SOURCE_DIR}
  -i${CMAKE_CURRENT_SOURCE_DIR}/pocslabcomplex.rc
   -o ${CMAKE_CURRENT_BINARY_DIR}/pocslabcomplex_rc.o)
	SET(pocslabcomplex_RC ${pocslabcomplex_RC} ${CMAKE_CURRENT_BINARY_DIR}/pocslabcomplex_rc.o)
else(MINGW)
	SET(pocslabcomplex_RC ${pocslabcomplex_RC} pocslabcomplex.rc)
endif(MINGW)


add_executable( ${PROJECT_FILE_NAME} WIN32 ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES} ${pocslabcomplex_RC})
#add_executable( ${PROJECT_FILE_NAME} ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES} ${pocslabcomplex_RC})

target_link_libraries( ${PROJECT_FILE_NAME} ${QT_LIBRARIES} )


