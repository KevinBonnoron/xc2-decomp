#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/intrusive_list.h"
#include "types.h"

struct CBdatWrapper;
namespace gf {
class GfMenuCallContext;
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

class GmkPreciousGob;

class GmkPrecious : public AGmkBase, public mm::mtl::IntrusiveListNode<GmkPrecious> {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    void dispose();
    bool isPopCondMatched() const;
    void validateDisp() const;

    u16 unknown00;              // Inferred role: item id; original member name unknown.
    u16 unknown02;              // Inferred role: condition; original member name unknown.
    u16 unknown04;              // Inferred role: quest id; original member name unknown.
    ScenarioFlagCond unknown06; // Inferred role: scenario flag; original member name unknown.
    QuestFlagCond unknown0a;    // Inferred role: quest flag; original member name unknown.
    TimeCond unknown10;         // Inferred role: time cond; original member name unknown.
    WeatherCond unknown20;      // Inferred role: weather cond; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_PRECIOUS;

  GmkPrecious();
  ~GmkPrecious() override { dispose(); }
  GmkType getGmkType() const override;
  int getGameFlagId() const;
  bool isObtained() const;
  bool isPopCondMatched() const;
  void validateDisp() const;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void disposeMenuIcon();
  void disposeEffectIcon(bool isFadeOut);
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;

  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(unknown20.unknown10); }

  gf::GF_OBJ_HANDLE *unknown58; // Inferred role: gob instance handle; original member name unknown.
  u32 unknown60;                // Inferred role: effect handle; original member name unknown.
  u8 _64[0x68 - 0x64];
  gf::GfMenuCallContext *unknown68; // Inferred role: menu icon; original member name unknown.
  DistCond unknown70;               // Inferred role: pop dist; original member name unknown.
  bool unknown74;                   // Inferred role: visible; original member name unknown.
  u8 _75[0x78 - 0x75];
};

static_assert(sizeof(GmkPrecious::BdatInfo) == 0x30, "");
static_assert(offsetof(GmkPrecious, unknown58) == 0x58, "");
static_assert(offsetof(GmkPrecious, unknown60) == 0x60, "");
static_assert(offsetof(GmkPrecious, unknown68) == 0x68, "");
static_assert(offsetof(GmkPrecious, unknown70) == 0x70, "");
static_assert(offsetof(GmkPrecious, unknown74) == 0x74, "");
static_assert(sizeof(GmkPrecious) == 0x78, "");

typedef TGmkList<GmkPrecious, GmkPrecious::BdatInfo, 0x53435250, 2, GmkPreciousGob> GmkPreciousList;

} // namespace gmk
