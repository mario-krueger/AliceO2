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
///
/// \file Cluster.cxx
/// \brief
///

#include "ITStracking/Cluster.h"
#include "ITStracking/MathUtils.h"
#include "ITStracking/IndexTableUtils.h"

namespace o2
{
namespace its
{

using math_utils::calculatePhiCoordinate;
using math_utils::calculateRCoordinate;
using math_utils::getNormalizedPhiCoordinate;

Cluster::Cluster(const float x, const float y, const float z, const int index)
  : xCoordinate{x},
    yCoordinate{y},
    zCoordinate{z},
    phiCoordinate{getNormalizedPhiCoordinate(calculatePhiCoordinate(x, y))},
    rCoordinate{calculateRCoordinate(x, y)},
    clusterId{index},
    indexTableBinIndex{0}
{
  // Nothing to do
}

Cluster::Cluster(const int layerIndex, const IndexTableUtils& utils, const Cluster& other)
  : xCoordinate{other.xCoordinate},
    yCoordinate{other.yCoordinate},
    zCoordinate{other.zCoordinate},
    phiCoordinate{getNormalizedPhiCoordinate(calculatePhiCoordinate(other.xCoordinate, other.yCoordinate))},
    rCoordinate{calculateRCoordinate(other.xCoordinate, other.yCoordinate)},
    clusterId{other.clusterId},
    indexTableBinIndex{utils.getBinIndex(utils.getZBinIndex(layerIndex, zCoordinate),
                                         utils.getPhiBinIndex(phiCoordinate))}
//, montecarloId{ other.montecarloId }
{
  // Nothing to do
}

Cluster::Cluster(const int layerIndex, const float3& primaryVertex, const IndexTableUtils& utils, const Cluster& other)
  : xCoordinate{other.xCoordinate},
    yCoordinate{other.yCoordinate},
    zCoordinate{other.zCoordinate},
    phiCoordinate{getNormalizedPhiCoordinate(
      calculatePhiCoordinate(xCoordinate - primaryVertex.x, yCoordinate - primaryVertex.y))},
    rCoordinate{calculateRCoordinate(xCoordinate - primaryVertex.x, yCoordinate - primaryVertex.y)},
    clusterId{other.clusterId},
    indexTableBinIndex{utils.getBinIndex(utils.getZBinIndex(layerIndex, zCoordinate),
                                         utils.getPhiBinIndex(phiCoordinate))}
{
  // Nothing to do
}

void Cluster::Init(const int layerIndex, const float3& primaryVertex, const IndexTableUtils& utils, const Cluster& other)
{
  xCoordinate = other.xCoordinate;
  yCoordinate = other.yCoordinate;
  zCoordinate = other.zCoordinate;
  phiCoordinate = getNormalizedPhiCoordinate(
    calculatePhiCoordinate(xCoordinate - primaryVertex.x, yCoordinate - primaryVertex.y));
  rCoordinate = calculateRCoordinate(xCoordinate - primaryVertex.x, yCoordinate - primaryVertex.y);
  clusterId = other.clusterId;
  indexTableBinIndex = utils.getBinIndex(utils.getZBinIndex(layerIndex, zCoordinate),
                                         utils.getPhiBinIndex(phiCoordinate));
}

TrackingFrameInfo::TrackingFrameInfo(float x, float y, float z, float xTF, float alpha, GPUArray<float, 2>&& posTF,
                                     GPUArray<float, 3>&& covTF)
  : xCoordinate{x}, yCoordinate{y}, zCoordinate{z}, xTrackingFrame{xTF}, alphaTrackingFrame{alpha},
#ifndef __OPENCL__
    positionTrackingFrame{posTF},
    covarianceTrackingFrame{covTF}
{
  // Nothing to do
}
#else
    positionTrackingFrame{},
    covarianceTrackingFrame{}
{
  positionTrackingFrame.copy(posTF);
  covarianceTrackingFrame.copy(covTF);
}
#endif

} // namespace its
} // namespace o2
