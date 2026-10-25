#pragma once
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_trigger.h"
#include "types.h"

struct CBdatWrapper;

namespace gmk {

class GmkMapGimmickGob;

class GmkMapGimmick : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isPopCondMatched() const;
    void debugDraw(const AGmkBase &gmk) const;

    u16 unknown00;           // Inferred role: condition; original member name unknown.
    u16 unknown02;           // Inferred role: name radius; original member name unknown.
    u16 unknown04;           // Inferred role: map object id; original member name unknown.
    bool unknown06;          // Inferred role: msg ray; original member name unknown.
    TimeCond unknown08;      // Inferred role: time cond; original member name unknown.
    WeatherCond unknown18;   // Inferred role: weather cond; original member name unknown.
    BootedGmkCond unknown28; // Inferred role: booted gmk; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_MAP_GIMMICK;

  ~GmkMapGimmick() override;
  GmkType getGmkType() const override;
  int getGameFlagId() const;
  void setSolved() const;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;

  u8 _48[0xb0 - 0x48];
};

static_assert(sizeof(GmkMapGimmick::BdatInfo) == 0x30, "");
static_assert(sizeof(GmkMapGimmick) == 0xb0, "");

class GmkMapGimmickList : public TGmkList<GmkMapGimmick, GmkMapGimmick::BdatInfo, 0x4750414d, 2, GmkMapGimmickGob> {
public:
  explicit GmkMapGimmickList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame), unknown230(0xffffffff) {}
  ~GmkMapGimmickList() override;

  const AGmkBase *getInst(u32 index) const override;
  void setUpdateGmkNumPerFrame(u32 num) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  bool updateImmediate() override;
  void debugUpdateMmf() override;
  void debugDraw() const override;

protected:
  void createGmk(void *data) override;

private:
  GmkTriggerList unknown230; // Inferred role: trigger list; original member name unknown.
};

static_assert(sizeof(GmkMapGimmickList) == 0x460, "");

} // namespace gmk
