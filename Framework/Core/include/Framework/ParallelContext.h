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

#ifndef O2_FRAMEWORK_PARALLELCONTEXT_H_
#define O2_FRAMEWORK_PARALLELCONTEXT_H_

#include "Framework/ServiceHandle.h"

namespace o2::framework
{

/// Purpose of this class is to provide DataProcessors which
/// have been instanciated in parallel via the o2::framework::parallel
/// function with information relevant to the parallel execution,
/// e.g. how many workers have been created by the above mentioned function
/// and what's the unique id the caller is associated with.
/// This context is exposed as a Service and it's therefore available
/// to both the init and the processing callbacks via:
///
///    auto ctx = services.get<ParallelContext>();
///
/// FIXME: should we have convenience methods to address workers using
///        different parallel topology (e.g. have a index2D, rather than index1D).
class ParallelContext
{
 public:
  constexpr static ServiceKind service_kind = ServiceKind::Global;
  // FIXME: find better names... rank1D and rank1DSize?
  ParallelContext(size_t index1D, size_t index1DSize)
    : mIndex1D{index1D},
      mIndex1DSize{index1DSize}
  {
  }

  size_t index1D() const { return mIndex1D; }
  size_t index1DSize() const { return mIndex1DSize; };

 private:
  size_t mIndex1D;
  size_t mIndex1DSize;
};

} // namespace o2::framework
#endif
