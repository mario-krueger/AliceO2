# Copyright 2019-2020 CERN and copyright holders of ALICE O2.
# See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
# All rights not expressly granted are reserved.
#
# This software is distributed under the terms of the GNU General Public
# License v3 (GPL Version 3), copied verbatim in the file "COPYING".
#
# In applying this license CERN does not waive the privileges and immunities
# granted to it by virtue of its status as an Intergovernmental Organization
# or submit itself to any jurisdiction.

#
# Build the doxygen
#

include(FindDoxygen)

if(NOT DOXYGEN_DOT_FOUND)
  message(
    WARNING
      "Graphviz doesn't seem to be installed. Doxygen will not be able to generate graphs. Consider installing this package."
    )
endif(NOT DOXYGEN_DOT_FOUND)

if(DOXYGEN_FOUND)
  # Configure the doxygen config file with current settings
  set("DOC_OUTPUT_DIR" "${CMAKE_CURRENT_BINARY_DIR}")
  configure_file(doxyfile.in
                 ${CMAKE_CURRENT_BINARY_DIR}/documentation-config.doxygen @ONLY)
  option(DOC_INSTALL "Install the documentation when calling \"make install\""
         OFF)
  set(DOC_TARGET_ALL "") # ensure that we build the doc if doc must be installed
  if(DOC_INSTALL)
    set(DOC_TARGET_ALL "ALL")
  endif(DOC_INSTALL)

  # target doc
  add_custom_target(
    doc ${DOC_TARGET_ALL} ${DOXYGEN_EXECUTABLE}
    ${CMAKE_CURRENT_BINARY_DIR}/documentation-config.doxygen
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation using doxygen for ${PROJECT_NAME}
                     \n  Output will be available in ${DOC_OUTPUT_DIR}/html"
    VERBATIM)

  # installation
  if(DOC_INSTALL)
    message(STATUS "Documentation will be installed")
    install(DIRECTORY ${DOC_OUTPUT_DIR}/html
            DESTINATION share/doc/${PROJECT_NAME}
            COMPONENT doc)
  endif(DOC_INSTALL)
endif(DOXYGEN_FOUND)
