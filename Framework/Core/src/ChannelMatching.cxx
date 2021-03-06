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
#include "Framework/ChannelMatching.h"
#include "Framework/DataSpecUtils.h"

namespace o2::framework
{

LogicalChannelRange::LogicalChannelRange(const OutputSpec& spec)
{
  name = std::string("out_") + std::string(DataSpecUtils::label(spec));
}

bool LogicalChannelRange::operator<(LogicalChannelRange const& other) const
{
  return this->name < other.name;
}

LogicalChannelDomain::LogicalChannelDomain(const InputSpec& spec)
{
  name.value = std::string("out_") + std::string(DataSpecUtils::label(spec));
}

bool LogicalChannelDomain::operator<(LogicalChannelDomain const& other) const
{
  return this->name.value < other.name.value;
}

PhysicalChannelRange::PhysicalChannelRange(const OutputSpec& spec, int count)
{
  char buffer[16];
  auto channel = LogicalChannelRange(spec);
  id = channel.name + (snprintf(buffer, 16, "_%d", count), buffer);
}

bool PhysicalChannelRange::operator<(PhysicalChannelRange const& other) const
{
  return this->id < other.id;
}

PhysicalChannelDomain::PhysicalChannelDomain(const InputSpec& spec, int count)
{
  char buffer[16];
  auto channel = LogicalChannelDomain(spec);
  id.value = channel.name.value + (snprintf(buffer, 16, "_%d", count), buffer);
}

bool PhysicalChannelDomain::operator<(PhysicalChannelDomain const& other) const
{
  return this->id.value < other.id.value;
}
} // namespace o2::framework
