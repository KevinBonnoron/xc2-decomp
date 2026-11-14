#pragma once
#include <stddef.h>

#include "gf/field/gf_gmk_locator_atlas.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/array.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace mm {
struct Aabb;
} // namespace mm

namespace ui {
class UICtrlCursorSelect;
class UICtrlObject;
class UISelectObjList;
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuCallContext;
class GfMenuFieldSkillList;
class GfMenuIDList;
class GfMenuZoneMapList;
struct MenuZoneMapInfo;

class GfMenuObjWorldMap : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjWorldMap *unknown20; // Inferred role: owner; original member name unknown.
  };

  class WorldListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjWorldMap *unknown20; // Inferred role: owner; original member name unknown.
  };

  class WorldMapListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjWorldMap *unknown20; // Inferred role: owner; original member name unknown.
  };

  class MapSelectListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: step; original member name unknown.
    u8 _10[0x20 - 0x10];
    GfMenuObjWorldMap *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ZoneSelectListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: step; original member name unknown.
    u8 _10[0x20 - 0x10];
    GfMenuObjWorldMap *unknown20; // Inferred role: owner; original member name unknown.
  };

  class IconFilterListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjWorldMap *unknown20; // Inferred role: owner; original member name unknown.
  };

  struct MapJumpInfo {
    MapJumpInfo() : unknown00(0), unknown04(-1) {}

    u32 unknown00; // Inferred role: icon object of the jump point; original member name unknown.
    s32 unknown04; // Role and original member name unknown, -1 when not set.
  };

  GfMenuObjWorldMap(u32 handle);
  ~GfMenuObjWorldMap() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static int setFadeIn(u32 handle);
  void deleteMapImage();
  static int setFadeOut(u32 handle, bool);
  static void sendEvent(u32 handle, u32 type, u32 param, u32 delay);
  static int setFadeOutSub(u32 handle, bool);
  static void setupMapList(GfMenuIDList *list);
  static void setupWorldMap(ui::UIObjectAcc &acc, GfMenuIDList *list, ui::UISelectObjList *objects);
  static void setupMapSelect(ui::UIObjectAcc &acc, GfMenuIDList *list);
  static void refreshMapSelect(ui::UIObjectAcc &acc, GfMenuIDList *list, ui::UISelectObjList *objects, int index);
  static bool isEnterMap(u32 map);
  bool setupZoneList(GfMenuZoneMapList *list);
  static void ctrlScrollBar(u32 handle, bool);
  static void setupZoneSelect(ui::UIObjectAcc &acc, GfMenuZoneMapList *list);
  static void refreshZoneSelect(ui::UIObjectAcc &acc, GfMenuZoneMapList *list, ui::UISelectObjList *objects, int index);
  static int ctrlGroupUp(ui::UISelectObjList *objects, u32 count);
  static int ctrlGroupReturn(ui::UISelectObjList *objects, u32 count);
  static void setupPointSelect(ui::UIObjectAcc &acc, GfMenuZoneMapList *list);
  static void refreshPointSelect(ui::UIObjectAcc &acc, GfMenuZoneMapList *list, ui::UISelectObjList *objects, u32 point);
  void loadTex();
  static bool isEnableJump(const MenuZoneMapInfo &info);
  void clearTex();
  static void refreshPointText(ui::UIObjectAcc &acc, GfMenuZoneMapList *list, ui::UISelectObjList *objects);
  int getTotalFieldSkillLv(u32 skill);
  void refreshIconFilter();
  void updateDispIconNode();
  static u32 searchNodeId(u32 map);
  static void setMapPos(ui::UIObjectAcc &acc, u32 map);
  static bool isDispMap(u32 map);
  static bool chkMapCond(u32 map, mm::Pnt<s16> *pos);
  u32 getFloor();
  bool seqTexDelete();
  bool seqTexDeleteWait();
  bool seqTexLoad();
  bool seqTexLoadWait();
  bool seqTexDraw();
  bool seqGimik();
  bool seqNext();
  static void closeIconTable(ui::UIObjectAcc &acc, mm::mtl::FixedArray<mm::mtl::FixedVector<u32, 256>, 10> &icons);
  static void getFloorAABB(u32 map, u32 floor, mm::Aabb &aabb, mm::Pnt<s16> &center);
  static u32 getFieldSkillFromGimmik(u8 *bdat, u32 id, u32 type);
  void setupIconTable(ui::UIObjectAcc &acc, mm::mtl::FixedArray<mm::mtl::FixedVector<u32, 256>, 10> &icons, GfMenuZoneMapList *list, mm::Pnt<s16> pos, mm::Vec2 scale, mm::Pnt<s16> center, bool);
  static u32 setupIconTableSub(ui::UIObjectAcc &acc, mm::mtl::FixedVector<u32, 256> &icons, u32 type, mm::Pnt<s16> pos, mm::Vec2 scale);
  static const char *getIconNodeName(u32 type);
  static bool chkFloor(u32 map, u32 floor);
  static void setupZoneMap(ui::UIObjectAcc &acc, GfMenuZoneMapList *list, ui::UISelectObjList *objects, bool);

  GfMenuIDList *unknown28;                                            // Inferred role: world maps; original member name unknown.
  ui::UISelectObjList *unknown30;                                     // Inferred role: world map tag objects; original member name unknown.
  bool unknown38;                                                     // Role and original member name unknown, set by the constructor.
  GfMenuZoneMapList *unknown40;                                       // Inferred role: zones; original member name unknown.
  ui::UISelectObjList *unknown48;                                     // Inferred role: zone objects; original member name unknown.
  GfMenuSequence<GfMenuObjWorldMap, 8> unknown50;                     // Inferred role: queued steps; original member name unknown.
  ui::UICtrlObject *unknown2e0;                                       // Inferred role: map frame control; original member name unknown.
  f32 unknown2e8;                                                     // Inferred role: map scale; original member name unknown.
  GfMenuZoneMapList *unknown2f0;                                      // Inferred role: points; original member name unknown.
  ui::UISelectObjList *unknown2f8;                                    // Inferred role: point objects; original member name unknown.
  mm::mtl::Array<MapJumpInfo> unknown300;                             // Inferred role: jump point icons; original member name unknown.
  u32 unknown318;                                                     // Role and original member name unknown, cleared by the constructor.
  GfMenuZoneMapList *unknown320;                                      // Role and original member name unknown, a list cleared by setupIconTable.
  GfMenuZoneMapList *unknown328;                                      // Role and original member name unknown, a list cleared by setupIconTable.
  GfMenuFieldSkillList *unknown330;                                   // Inferred role: field skills of the pointed gimmick; original member name unknown.
  mm::mtl::FixedVector<u16, 422> unknown338;                          // Inferred role: blades counted for the field skills; original member name unknown.
  bool unknown690;                                                    // Inferred role: map image created flag; original member name unknown.
  mm::mtl::FixStr<32> unknown694;                                     // Inferred role: map image name; original member name unknown.
  ui::UISelectObjList *unknown6b8;                                    // Inferred role: icon objects; original member name unknown.
  mm::mtl::FixedArray<mm::mtl::FixedVector<u32, 256>, 10> unknown6c0; // Inferred role: icon objects of each node; original member name unknown.
  u32 unknown2f10;                                                    // Role and original member name unknown, cleared by the constructor.
  // seqGimik (0x71004ecb74) passes these fields by value to setupIconTable.
  mm::Pnt<s16> unknown2f14; // Inferred role: displayed map center; original member name unknown.
  mm::Vec2 unknown2f20;     // Inferred role: displayed map scale; original member name unknown.
  mm::Pnt<s16> unknown2f30; // Inferred role: floor bounds center; original member name unknown.
  u8 _2f34[0x2f60 - 0x2f34];
  bool unknown2f60;                          // Inferred role: player on the shown floor flag; original member name unknown.
  bool unknown2f61;                          // Role and original member name unknown, cleared by the constructor.
  GfMenuCallContext *unknown2f68;            // Inferred role: call context; original member name unknown.
  bool unknown2f70;                          // Role and original member name unknown, cleared by the constructor.
  u8 *unknown2f78;                           // Inferred role: map jump table; original member name unknown.
  u16 unknown2f80;                           // Inferred role: loaded floor; original member name unknown.
  u32 unknown2f84;                           // Inferred role: shown icon node bits; original member name unknown.
  ui::UISelectObjList *unknown2f88;          // Inferred role: icon filter objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown2f90;       // Inferred role: icon filter cursor; original member name unknown.
  GfGmkLocatorAtlas::CreateInfo unknown2fa0; // Inferred role: locator atlas area to restore; original member name unknown.
};

static_assert(offsetof(GfMenuObjWorldMap::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjWorldMap::WorldListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjWorldMap::WorldMapListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjWorldMap::MapSelectListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjWorldMap::MapSelectListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjWorldMap::ZoneSelectListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjWorldMap::ZoneSelectListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjWorldMap::IconFilterListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjWorldMap::MapJumpInfo) == 0x8, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown2e0) == 0x2e0, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown2e8) == 0x2e8, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown2f0) == 0x2f0, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown2f8) == 0x2f8, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown300) == 0x300, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown318) == 0x318, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown320) == 0x320, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown328) == 0x328, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown330) == 0x330, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown338) == 0x338, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown690) == 0x690, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown694) == 0x694, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown6b8) == 0x6b8, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown6c0) == 0x6c0, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown2f10) == 0x2f10, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown2f14) == 0x2f14, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown2f20) == 0x2f20, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown2f30) == 0x2f30, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown2f60) == 0x2f60, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown2f61) == 0x2f61, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown2f68) == 0x2f68, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown2f70) == 0x2f70, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown2f78) == 0x2f78, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown2f80) == 0x2f80, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown2f84) == 0x2f84, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown2f88) == 0x2f88, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown2f90) == 0x2f90, "");
static_assert(offsetof(GfMenuObjWorldMap, unknown2fa0) == 0x2fa0, "");
// GfMenuManager::reciveEvent passes 0x2fd0 to operator new at 0x71003c4930 before calling the constructor.
static_assert(sizeof(GfMenuObjWorldMap) == 0x2fd0, "");

} // namespace gf
