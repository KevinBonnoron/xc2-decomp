#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"

namespace gmk {

class GmkFieldVolumeGob;

class GmkFieldVolume : public AGmkBase {
public:
  struct BdatInfo {};

  static const GmkType GMK_TYPE = GMK_TYPE_FIELD_VOLUME;

  ~GmkFieldVolume() override { dispose(); }
  GmkType getGmkType() const override { return GMK_TYPE; }
  bool isValid() const override { return baseInfo.list != nullptr && createInfo.data != nullptr; }
  void create(const CreateInfo &info) override;
};

static_assert(sizeof(GmkFieldVolume) == 0x48, "");

typedef TGmkList<GmkFieldVolume, GmkFieldVolume::BdatInfo, 0x4d4c5646, 2, GmkFieldVolumeGob> GmkFieldVolumeList;

} // namespace gmk
