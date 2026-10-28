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
struct GF_OBJ_HANDLE;
} // namespace gf
namespace mm {
struct Vec3;
} // namespace mm

namespace gmk {

class GmkNpcGob;
class GmkNpcIdInfo;

class AGmkNpc : public mm::mtl::IntrusiveListNode<AGmkNpc> {
public:
  virtual ~AGmkNpc() {}
  virtual bool isPopCondMatched() const = 0;
  virtual bool isDepopCondMatched() const = 0;
  virtual bool isPopDistCondMatched() const = 0;
  virtual bool isDepopDistCondMatched() const = 0;
  virtual u8 *getBindedBdatFp() const = 0;
  virtual int getBindedBdatId() const = 0;
  virtual bool findPopPosRot(mm::Vec3 &position, mm::Vec3 &rotation) const = 0;
  virtual void bindToGameObj(gf::GF_OBJ_HANDLE *handle) const = 0;
  virtual void unbindToGameObj(gf::GF_OBJ_HANDLE *handle) const = 0;
  virtual void validateDisp() const = 0;
  virtual void debugUpdate(f32 deltaTime);

  GmkNpcIdInfo *unknown18; // Inferred role: shared NPC instance information; original member name unknown.
};

static_assert(offsetof(AGmkNpc, unknown18) == 0x18, "");
static_assert(sizeof(AGmkNpc) == 0x20, "");

class GmkNpc : public AGmkBase, public AGmkNpc {
public:
  struct BdatInfo {
    BdatInfo() : unknown00(0), unknown02(0), unknown04(0), unknown20(), unknown28() {}
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isPopCommonCondMatched(const AGmkBase &gmk) const;
    void debugDraw(const AGmkBase &gmk) const;

    u16 unknown00;              // Inferred role: condition; original member name unknown.
    u16 unknown02;              // Inferred role: group; original member name unknown.
    u16 unknown04;              // Inferred role: battle reaction; original member name unknown.
    ScenarioFlagCond unknown06; // Inferred role: scenario flag; original member name unknown.
    QuestFlagCond unknown0a;    // Inferred role: quest flag; original member name unknown.
    TimeCond unknown10;         // Inferred role: time cond; original member name unknown.
    DistHvCond unknown20;       // Inferred role: pop dist; original member name unknown.
    DistHvCond unknown28;       // Inferred role: depop dist; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_NPC;

  ~GmkNpc() override { dispose(); }
  GmkType getGmkType() const override;
  gf::GF_OBJ_HANDLE *getGobInst() const;
  bool isPopCondMatchedExceptDist() const;
  bool isPopCondMatched() const override;
  bool isDepopCondMatched() const override;
  bool isPopDistCondMatched() const override;
  bool isDepopDistCondMatched() const override;
  u8 *getBindedBdatFp() const override;
  int getBindedBdatId() const override { return AGmkBase::unknown20.unknown18; }
  bool findPopPosRot(mm::Vec3 &position, mm::Vec3 &rotation) const override;
  void bindToGameObj(gf::GF_OBJ_HANDLE *handle) const override;
  void unbindToGameObj(gf::GF_OBJ_HANDLE *handle) const override { AGmkBase::unbindToGameObj(handle); }
  void validateDisp() const override;
  void debugDraw() const override;
  void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) override;
  void debugUpdate(f32 deltaTime) override {}

  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(AGmkBase::unknown20.unknown10); }

  bool unknown68; // Inferred role: display enabled; original member name unknown.
};

static_assert(sizeof(GmkNpc::BdatInfo) == 0x30, "");
static_assert(offsetof(GmkNpc, unknown68) == 0x68, "");
static_assert(sizeof(GmkNpc) == 0x70, "");

class GmkNpcList : public TGmkList<GmkNpc, GmkNpc::BdatInfo, 0x43504e, 4, GmkNpcGob> {
public:
  explicit GmkNpcList(u32 updateGmkNumPerFrame);
  ~GmkNpcList() override { dispose(); }

protected:
  void createGmk(void *data) override;
  void disposeGmk() override;
};

} // namespace gmk
