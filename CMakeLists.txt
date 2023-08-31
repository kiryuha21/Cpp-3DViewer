cmake_minimum_required(VERSION 3.26)
project(3d_viewer_template)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(app
        src/main.cc
        src/view/MainWindow.cc
        src/view/MainWindow.h
        src/controller/VisualizationController.cc
        src/controller/VisualizationController.h
        src/model/VisualizationModel.cc
        src/model/VisualizationModel.h
        src/model/utils.cc
        src/model/utils.h)

add_executable(test
        src/tests/tests_main.cc
        src/model/utils.cc
        src/model/utils.h)

target_link_libraries(app ${GTKMM_LIBRARIES} boost_iostreams)
target_link_libraries(test gtest boost_iostreams)
