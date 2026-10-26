#pragma once
#include "gf/data/gf_bdat_wrapper.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"

namespace gmk {

class GmkFieldVolumeGob;

class GmkFieldVolume : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper, int, const AGmkBase &) {}
  };

  static const GmkType GMK_TYPE = GMK_TYPE_FIELD_VOLUME;

  ~GmkFieldVolume() override { dispose(); }
  GmkType getGmkType() const override { return GMK_TYPE; }
  bool isValid() const override { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }
  void create(const CreateInfo &info) override;
};

static_assert(sizeof(GmkFieldVolume) == 0x48, "");

typedef TGmkList<GmkFieldVolume, GmkFieldVolume::BdatInfo, 0x4d4c5646, 2, GmkFieldVolumeGob> GmkFieldVolumeList;

} // namespace gmk
