# Copyright (C) 2020, Inria
# GRAPHDECO research group, https://team.inria.fr/graphdeco
# All rights reserved.
#
# This software is free for non-commercial, research and evaluation use
# under the terms of the LICENSE.md file.
#
# For inquiries contact sibr@inria.fr and/or George.Drettakis@inria.fr

project(sibr_video)

file(GLOB SOURCES "*.cpp" "*.h" "*.hpp")
source_group("Source Files" FILES ${SOURCES})

# # Specify target rules
add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${Boost_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  ${FFMPEG_LIBRARIES}
  ${OpenCV_LIBS}
  OpenMP::OpenMP_CXX
)

set_property(TARGET ${PROJECT_NAME} PROPERTY LINK_WHAT_YOU_USE ON)

if(UNIX AND NOT APPLE)
  target_link_options(${PROJECT_NAME} PRIVATE "-Wl,--no-as-needed")
endif()

add_definitions(-DSIBR_VIDEO_EXPORTS -DBOOST_ALL_DYN_LINK)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${SIBR_FOLDER})

# # High level macro to install in an homogen way all our ibr targets
include(install_runtime)
ibr_install_target(${PROJECT_NAME}
  INSTALL_PDB # # mean install also MSVC IDE *.pdb file (DEST according to target type)
)
