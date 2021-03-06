// Copyright 2019-2020 CERN and copyright holders of ALICE O2.
// See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
// All rights not expressly granted are reserved.
//
// This software is distributed under the terms of the GNU General Public
// License v3 (GPL Version 3), copied verbatim in the file "COPYING".
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#if !defined(__CLING__) || defined(__ROOTCLING__)
#define MS_GSL_V3
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TGeoGlobalMagField.h>
#include <string>
#include <FairLogger.h>

#include "Field/MagneticField.h"
#include "DataFormatsParameters/GRPObject.h"
#include "DetectorsBase/GeometryManager.h"
#include "DetectorsBase/Propagator.h"

#include "GlobalTracking/MatchTOF.h"
#endif

#define _ALLOW_DEBUG_TREES_ // to allow debug and control tree output

void run_match_tof(std::string path = "./", std::string outputfile = "o2match_tof.root",
                   std::string outputfileCalib = "o2calib_tof.root",
                   std::string inputTracksTPCITS = "o2match_itstpc.root",
                   std::string inputTracksTPC = "tpctracks.root",
                   std::string inputClustersTOF = "tofclusters.root",
                   std::string inputGRP = "o2sim_grp.root")
{

  o2::globaltracking::MatchTOF matching;

  if (path.back() != '/') {
    path += '/';
  }

  //>>>---------- attach input data --------------->>>
  TChain tracks("matchTPCITS");
  tracks.AddFile((path + inputTracksTPCITS).data());
  matching.setInputTreeTracks(&tracks);

  TChain tpcTracks("events");
  tpcTracks.AddFile((path + inputTracksTPC).data());
  matching.setInputTreeTPCTracks(&tpcTracks);
  matching.setTPCTrackBranchName("TPCTracks");

  TChain tofClusters("o2sim");
  tofClusters.AddFile((path + inputClustersTOF).data());
  matching.setInputTreeTOFClusters(&tofClusters);

  //<<<---------- attach input data ---------------<<<

  // create/attach output tree
  TFile outFile((path + outputfile).data(), "recreate");
  TTree outTree("matchTOF", "Matched TOF-tracks");
  matching.setOutputTree(&outTree);
  TFile outFileCalib((path + outputfileCalib).data(), "recreate");
  TTree outTreeCalib("calibTOF", "Calib TOF infos");
  matching.setOutputTreeCalib(&outTreeCalib);

#ifdef _ALLOW_DEBUG_TREES_
  matching.setDebugTreeFileName(path + matching.getDebugTreeFileName());
  matching.setDebugFlag(o2::globaltracking::MatchTOF::MatchTreeAll);
#endif

  //-------- init geometry and field --------//
  o2::base::GeometryManager::loadGeometry(path);
  o2::base::Propagator::initFieldFromGRP(path + inputGRP);

  matching.init();

  matching.run();

  outFile.cd();
  outTree.Write();
  outFile.Close();
  outFileCalib.cd();
  outTreeCalib.Write();
  outFileCalib.Close();
}
