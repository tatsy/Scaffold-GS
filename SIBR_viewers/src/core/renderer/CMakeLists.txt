# Copyright (C) 2020, Inria
# GRAPHDECO research group, https://team.inria.fr/graphdeco
# All rights reserved.
#
# This software is free for non-commercial, research and evaluation use
# under the terms of the LICENSE.md file.
#
# For inquiries contact sibr@inria.fr and/or George.Drettakis@inria.fr

cmake_minimum_required(VERSION 3.18)
project(sibr_renderer)

file(GLOB SOURCES "*.cpp" "*.h" "*.hpp")
source_group("Source Files" FILES ${SOURCES})

file(GLOB SHADERS "shaders/*.frag" "shaders/*.vert" "shaders/*.geom" "shaders/*.fp" "shaders/*.gp" "shaders/*.vp")
source_group("Source Files\\shaders" FILES ${SHADERS})

file(GLOB SOURCES "*.cpp" "*.h" "*.hpp" "shaders/*.frag" "shaders/*.vert" "shaders/*.geom" "shaders/*.fp" "shaders/*.gp" "shaders/*.vp")

# # Specify target rules
add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${Python_INCLUDE_DIRS}
  ${TORCH_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  GLEW::GLEW
  opencv_core
  opencv_imgproc
  opencv_imgcodecs
)

set_property(TARGET ${PROJECT_NAME} PROPERTY LINK_WHAT_YOU_USE ON)

if(UNIX AND NOT APPLE)
  target_link_options(${PROJECT_NAME} PRIVATE "-Wl,--no-as-needed")
endif()

add_definitions(-DSIBR_EXP_RENDERER_EXPORTS -DBOOST_ALL_DYN_LINK)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${SIBR_FOLDER})

# # High level macro to install in an homogen way all our ibr targets
include(install_runtime)
ibr_install_target(${PROJECT_NAME}
  INSTALL_PDB # # mean install also MSVC IDE *.pdb file (DEST according to target type)
  SHADERS "${SHADERS}"
  RSC_FOLDER "core"
  COMPONENT ${PROJECT_NAME}_install # # will create custom target to install only this project
)
