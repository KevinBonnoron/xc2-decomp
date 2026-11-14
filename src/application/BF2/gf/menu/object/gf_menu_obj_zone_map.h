#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/array.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlObject;
class UISelectObjList;
class UIObjectAcc;
} // namespace ui

namespace mm {
struct Aabb;
struct Vec2;
} // namespace mm

namespace gf {

class GfMenuCallContext;
class GfMenuZoneMapList;
struct MenuZoneMapInfo;

class GfMenuObjZoneMap : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjZoneMap *unknown20; // Inferred role: owner; original member name unknown.
  };

  class HelpListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjZoneMap *unknown20; // Inferred role: owner; original member name unknown.
  };

  class MapSelectListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjZoneMap *unknown20; // Inferred role: owner; original member name unknown.
  };

  struct MapJumpInfo {
    MapJumpInfo() : unknown00(0), unknown04(-1) {}

    s32 unknown00; // Role and original member name unknown.
    s32 unknown04; // Role and original member name unknown, -1 when not set.
  };

  GfMenuObjZoneMap(u32 handle);
  ~GfMenuObjZoneMap() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void setupMain(ui::UIObjectAcc &acc);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  static void setDispMapCursor(ui::UIObjectAcc &acc, bool isDisp);
  static void setupMapSelect(ui::UIObjectAcc &acc, GfMenuZoneMapList *list);
  static void refreshMapSelect(ui::UIObjectAcc &acc, GfMenuZoneMapList *list, ui::UISelectObjList *objects, u32 map);
  static void setupPointSelect(ui::UIObjectAcc &acc, GfMenuZoneMapList *list);
  static void refreshPointSelect(ui::UIObjectAcc &acc, GfMenuZoneMapList *list, ui::UISelectObjList *objects, u32 point);
  static bool isEnableJump(const MenuZoneMapInfo &info);
  static bool setupMapList(GfMenuZoneMapList *list);
  static void setupZoneMap(ui::UIObjectAcc &acc, GfMenuZoneMapList *list, ui::UISelectObjList *objects, bool);
  void clearTex();
  static void setupPoint(ui::UIObjectAcc &acc, GfMenuZoneMapList *list, ui::UISelectObjList *objects);
  static void setupHelp(ui::UIObjectAcc &acc);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static bool chkFloor(u32 map, u32 floor);
  static u32 setupIconTableSub(ui::UIObjectAcc &acc, mm::mtl::FixedVector<u32, 256> &icons, u32 type, mm::Pnt<s16> pos, mm::Vec2 scale);
  static const char *getIconNodeName(u32 type);
  static void setDispIconNode(ui::UIObjectAcc &acc, u32 node);
  static void closeIconTable(ui::UIObjectAcc &acc, mm::mtl::FixedArray<mm::mtl::FixedVector<u32, 256>, 12> &icons);
  u32 getFloor();
  bool seqTexDelete();
  bool seqTexDeleteWait();
  bool seqTexLoadWait();
  static void getFloorAABB(u32 map, u32 floor, mm::Aabb &aabb, mm::Pnt<s16> &center);

  u8 _24[0x28 - 0x24];
  GfMenuZoneMapList *unknown28;   // Inferred role: maps; original member name unknown.
  ui::UISelectObjList *unknown30; // Inferred role: map objects; original member name unknown.
  ui::UICtrlObject *unknown38;    // Inferred role: control; original member name unknown.
  f32 unknown40;                  // Role and original member name unknown, set to 1.0f by the constructor.
  u8 _44[0x48 - 0x44];
  GfMenuZoneMapList *unknown48;                                       // Inferred role: points; original member name unknown.
  ui::UISelectObjList *unknown50;                                     // Inferred role: point objects; original member name unknown.
  mm::mtl::Array<MapJumpInfo> unknown58;                              // Inferred role: map list entries; original member name unknown.
  bool unknown70;                                                     // Role and original member name unknown, cleared by the constructor.
  mm::mtl::FixStr<32> unknown74;                                      // Inferred role: map image name; original member name unknown.
  ui::UISelectObjList *unknown98;                                     // Inferred role: help objects; original member name unknown.
  mm::mtl::FixedArray<mm::mtl::FixedVector<u32, 256>, 12> unknown0a0; // Inferred role: icon nodes of each floor; original member name unknown.
  u32 unknown3100;                                                    // Role and original member name unknown, cleared by the constructor.
  u8 _3104[0x3124 - 0x3104];
  bool unknown3124; // Role and original member name unknown, cleared by the constructor.
  bool unknown3125; // Role and original member name unknown, cleared by the constructor.
  u8 _3126[0x3128 - 0x3126];
  GfMenuCallContext *unknown3128;                  // Inferred role: call context; original member name unknown.
  GfMenuSequence<GfMenuObjZoneMap, 8> unknown3130; // Inferred role: queued steps; original member name unknown.
  bool unknown33c0;                                // Role and original member name unknown, cleared by the constructor.
  u8 _33c1[0x33c8 - 0x33c1];
  u8 *unknown33c8; // Inferred role: map image table; original member name unknown.
  u16 unknown33d0; // Role and original member name unknown, cleared by the constructor.
};

static_assert(offsetof(GfMenuObjZoneMap::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjZoneMap, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjZoneMap, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjZoneMap, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjZoneMap, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjZoneMap, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjZoneMap, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjZoneMap, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjZoneMap, unknown70) == 0x70, "");
static_assert(offsetof(GfMenuObjZoneMap, unknown74) == 0x74, "");
static_assert(offsetof(GfMenuObjZoneMap, unknown98) == 0x98, "");
static_assert(offsetof(GfMenuObjZoneMap, unknown0a0) == 0xa0, "");
static_assert(offsetof(GfMenuObjZoneMap, unknown3100) == 0x3100, "");
static_assert(offsetof(GfMenuObjZoneMap, unknown3124) == 0x3124, "");
static_assert(offsetof(GfMenuObjZoneMap, unknown3125) == 0x3125, "");
static_assert(offsetof(GfMenuObjZoneMap, unknown3128) == 0x3128, "");
static_assert(offsetof(GfMenuObjZoneMap, unknown3130) == 0x3130, "");
static_assert(offsetof(GfMenuObjZoneMap, unknown33c0) == 0x33c0, "");
static_assert(offsetof(GfMenuObjZoneMap, unknown33c8) == 0x33c8, "");
static_assert(offsetof(GfMenuObjZoneMap, unknown33d0) == 0x33d0, "");

} // namespace gf
