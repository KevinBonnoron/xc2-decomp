#pragma once
#include <stddef.h>

#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

struct CBdatWrapper;
namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

class GmkKizunaTalkGob;

class GmkKizunaTalk : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isCondMatched() const;

    u16 condition;
    u16 title;
    u16 eventCondition;
  };

  static const GmkType GMK_TYPE = GMK_TYPE_KIZUNA_TALK;

  ~GmkKizunaTalk() override { dispose(); }
  GmkType getGmkType() const override { return GMK_TYPE; }
  int getGameFlagId() const;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void disposeGfObjHandle();
  void update(f32 deltaTime) override;
  void createGfObjHandle();
  void debugDraw() const override;
  void validateDisp() const;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;

  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(createInfo.info); }

  gf::GF_OBJ_HANDLE *handle;
  DistCond distCond;
  bool isDisp;
};

static_assert(offsetof(GmkKizunaTalk, handle) == 0x48, "");
static_assert(offsetof(GmkKizunaTalk, distCond) == 0x50, "");
static_assert(offsetof(GmkKizunaTalk, isDisp) == 0x54, "");

static_assert(sizeof(GmkKizunaTalk::BdatInfo) == 0x6, "");
static_assert(sizeof(GmkKizunaTalk) == 0x58, "");

typedef TGmkList<GmkKizunaTalk, GmkKizunaTalk::BdatInfo, 0x544e5a4b, 1, GmkKizunaTalkGob> GmkKizunaTalkList;

} // namespace gmk
