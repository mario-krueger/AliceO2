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

o2_add_header_only_library(Algorithm INTERFACE_LINK_LIBRARIES O2::Headers)

o2_target_man_page(Algorithm NAME Algorithm SECTION 3)
o2_target_man_page(Algorithm NAME algorithm_parser SECTION 3)

o2_add_test(o2formatparser
            SOURCES test/o2formatparser.cxx
            COMPONENT_NAME Algorithm
            PUBLIC_LINK_LIBRARIES O2::Algorithm
            LABELS algorithm)

o2_add_test(headerstack
            SOURCES test/headerstack.cxx
            COMPONENT_NAME Algorithm
            PUBLIC_LINK_LIBRARIES O2::Algorithm
            LABELS algorithm)

o2_add_test(parser
            SOURCES test/parser.cxx
            COMPONENT_NAME Algorithm
            PUBLIC_LINK_LIBRARIES O2::Algorithm
            LABELS algorithm)

o2_add_test(tableview
            SOURCES test/tableview.cxx
            COMPONENT_NAME Algorithm
            PUBLIC_LINK_LIBRARIES O2::Algorithm
            LABELS algorithm)

o2_add_test(pageparser
            SOURCES test/pageparser.cxx
            COMPONENT_NAME Algorithm
            PUBLIC_LINK_LIBRARIES O2::Algorithm
            LABELS algorithm)

o2_add_test(mpl_tools
            SOURCES test/test_mpl_tools.cxx
            COMPONENT_NAME Algorithm
            LABELS algorithm)

o2_add_test(RangeTokenizer
            SOURCES test/test_RangeTokenizer.cxx
            COMPONENT_NAME Algorithm
            LABELS algorithm)


o2_add_test(FlattenRestore
            SOURCES test/test_FlattenRestore.cxx
            COMPONENT_NAME Algorithm
            LABELS algorithm)
