#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace gmk {

class GmkKizunaTalkGob;

class GmkKizunaTalk : public AGmkBase {
public:
  struct BdatInfo {
    u8 _00[0x6];
  };

  static const GmkType GMK_TYPE = GMK_TYPE_KIZUNA_TALK;

  ~GmkKizunaTalk() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;

  u8 _48[0x58 - 0x48];
};

static_assert(sizeof(GmkKizunaTalk::BdatInfo) == 0x6, "");
static_assert(sizeof(GmkKizunaTalk) == 0x58, "");

typedef TGmkList<GmkKizunaTalk, GmkKizunaTalk::BdatInfo, 0x544e5a4b, 1, GmkKizunaTalkGob> GmkKizunaTalkList;

} // namespace gmk
