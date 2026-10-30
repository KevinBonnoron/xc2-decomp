#pragma once
#include <stddef.h>

#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_phantom.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

struct CBdatWrapper;

namespace gmk {

class GmkAntiBladeAreaGob;

class GmkAntiBladeArea : public AGmkBase, public IGmkPhantomEventListener, public mm::mtl::IntrusiveListNode<GmkAntiBladeArea> {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    void dispose() { unknown00 = 0; }

    u16 unknown00; // Inferred role: map rev id; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_ANTI_BLADE_AREA;

  GmkAntiBladeArea() : unknown60(nullptr) {}
  ~GmkAntiBladeArea() override { dispose(); }
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void debugDraw() const override;
  void onEnterPhantom(const IGmkPhantomEventListener::OnEnterInfo &info) override;
  void onLeavePhantom(const IGmkPhantomEventListener::OnLeaveInfo &info) override;
  void createGmkPhantom();

  GmkPhantom unknown60; // Inferred role: phantom; original member name unknown.
};

static_assert(sizeof(GmkAntiBladeArea::BdatInfo) == 0x2, "");
static_assert(offsetof(GmkAntiBladeArea, unknown60) == 0x60, "");
static_assert(sizeof(GmkAntiBladeArea) == 0xf0, "");

typedef TGmkList<GmkAntiBladeArea, GmkAntiBladeArea::BdatInfo, 0x414c4241, 2, GmkAntiBladeAreaGob> GmkAntiBladeAreaList;

class GmkAntiBladeAreaManager : public mm::mtl::PtrSingleton<GmkAntiBladeAreaManager> {
public:
  GmkAntiBladeAreaManager() : unknown20(nullptr) {}
  ~GmkAntiBladeAreaManager() override { dispose(); }
  void dispose();
  static void addGmk(GmkAntiBladeArea *gmk);
  static void removeGmk(GmkAntiBladeArea *gmk);

  mm::mtl::IntrusiveList<GmkAntiBladeArea> unknown08; // Inferred role: gimmicks inside; original member name unknown.
  GmkAntiBladeArea *unknown20;                        // Inferred role: front gimmick; original member name unknown.
};

static_assert(offsetof(GmkAntiBladeAreaManager, unknown08) == 0x08, "");
static_assert(offsetof(GmkAntiBladeAreaManager, unknown20) == 0x20, "");

} // namespace gmk
