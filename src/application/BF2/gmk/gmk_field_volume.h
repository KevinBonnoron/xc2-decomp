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

  ~GmkFieldVolume() override;
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
};

static_assert(sizeof(GmkFieldVolume) == 0x48, "");

typedef TGmkList<GmkFieldVolume, GmkFieldVolume::BdatInfo, 0x4d4c5646, 2, GmkFieldVolumeGob> GmkFieldVolumeList;

} // namespace gmk
