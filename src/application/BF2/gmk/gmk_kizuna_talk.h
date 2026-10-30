#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_handle.h"
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

    u16 unknown00; // Inferred role: condition; original member name unknown.
    u16 unknown02; // Inferred role: title; original member name unknown.
    u16 unknown04; // Inferred role: event condition; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_KIZUNA_TALK;

  GmkKizunaTalk() : unknown48(gf::INVALID_HANDLE), unknown50(), unknown54(true) {}
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

  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(unknown20.unknown10); }

  gf::GF_OBJ_HANDLE *unknown48; // Inferred role: handle; original member name unknown.
  DistCond unknown50;           // Inferred role: dist cond; original member name unknown.
  bool unknown54;               // Inferred role: disp; original member name unknown.
};

static_assert(offsetof(GmkKizunaTalk, unknown48) == 0x48, "");
static_assert(offsetof(GmkKizunaTalk, unknown50) == 0x50, "");
static_assert(offsetof(GmkKizunaTalk, unknown54) == 0x54, "");

static_assert(sizeof(GmkKizunaTalk::BdatInfo) == 0x6, "");
static_assert(sizeof(GmkKizunaTalk) == 0x58, "");

typedef TGmkList<GmkKizunaTalk, GmkKizunaTalk::BdatInfo, 0x544e5a4b, 1, GmkKizunaTalkGob> GmkKizunaTalkList;

} // namespace gmk
