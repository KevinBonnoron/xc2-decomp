#pragma once
#include <stddef.h>

#include "gf/data/gf_data_option.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlCursorSelect;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuCallContext;

class GfMenuObjOption : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjOption *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjOption *unknown20; // Inferred role: owner; original member name unknown.
  };

  class SubMenuListener : public ui::UIObjectListener {
  public:
    SubMenuListener(GfMenuObjOption *owner) : unknown0c(0), _10(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u32 unknown0c; // Inferred role: state, 1 once the sub menu is closed for good; original member name unknown.
    u8 _10[0x1c - 0x10];
    GfMenuObjOption *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ItemListListener : public ui::UIObjectListener {
  public:
    ItemListListener(GfMenuObjOption *owner) : unknown0c(0), _10(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u32 unknown0c; // Inferred role: option type, 0 camera, 1 sound and 2 display; original member name unknown.
    u8 _10[0x1c - 0x10];
    GfMenuObjOption *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ItemSettingListener : public ui::UIObjectListener {
  public:
    ItemSettingListener(GfMenuObjOption *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjOption *unknown20; // Inferred role: owner; original member name unknown.
  };

  // Inferred role: current and maximum level of an option item; original type name unknown.
  struct Level {
    u8 unknown00; // Inferred role: current level; original member name unknown.
    u8 unknown01; // Inferred role: maximum level; original member name unknown.
  };

  GfMenuObjOption(u32 handle);
  ~GfMenuObjOption() override;
  static bool attach(GfMenuCallContext *context);
  void initialize() override;
  void finalize() override;
  void update() override;

  static void initOptionData(SDataOption &option);
  static void getDefaultLevel(u32 type, mm::mtl::FixedVector<Level, 32> &levels);
  static void convLevelListToOptionData(u32 type, const mm::mtl::FixedVector<Level, 32> &levels, SDataOption &option);
  void convOptionDataToLevelList(u32 type, const SDataOption &option);
  void refreshLevel(u32 type);
  bool seqSave();
  bool seqSaveWait();
  void updateInfo(u32 index);
  void dispItemBase(u32 type, u32 index, bool isDisp);
  static int getVolumeValue(u8 level, u8 levelMax);
  static u32 getGammaValue(u8 level, u8 levelMax);
  static u8 getVolumeLevel(u8 value, u8 levelMax);
  static u8 getGammaLevel(u16 value, u8 levelMax);

  u8 _24[0x28 - 0x24];
  ui::UISelectObjList *unknown28;                // Inferred role: option objects; original member name unknown.
  ui::UISelectObjList *unknown30;                // Inferred role: level objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown38;             // Inferred role: option cursor; original member name unknown.
  u8 *unknown40;                                 // Inferred role: option table; original member name unknown.
  u32 unknown48;                                 // Inferred role: option description text object; original member name unknown.
  u32 unknown4c;                                 // Inferred role: option setting layout object; original member name unknown.
  mm::mtl::FixedVector<Level, 32> unknown50;     // Inferred role: option levels; original member name unknown.
  SDataOption unknown98;                         // Inferred role: option data being edited; original member name unknown.
  GfMenuCallContext *unknown120;                 // Inferred role: call context; original member name unknown.
  GfMenuSequence<GfMenuObjOption, 8> unknown128; // Inferred role: queued steps; original member name unknown.
  bool unknown3b8;                               // Role and original member name unknown, cleared by the constructor.
  int unknown3bc;                                // Role and original member name unknown, -1 at start.
  bool unknown3c0;                               // Inferred role: advertize mode; original member name unknown.
  bool unknown3c1;                               // Inferred role: guide text parameter, the advertize mode; original member name unknown.
  s8 unknown3c2;                                 // Inferred role: option type being edited, -1 for none; original member name unknown.
  u8 _3c3[0x3c8 - 0x3c3];
};

static_assert(offsetof(GfMenuObjOption::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjOption::SubMenuListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjOption::SubMenuListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjOption::ItemListListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjOption::ItemListListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjOption::ItemSettingListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjOption::MainListener) == 0x28, "");
static_assert(sizeof(GfMenuObjOption::SubMenuListener) == 0x28, "");
static_assert(sizeof(GfMenuObjOption::ItemListListener) == 0x28, "");
static_assert(sizeof(GfMenuObjOption::ItemSettingListener) == 0x28, "");
static_assert(offsetof(GfMenuObjOption, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjOption, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjOption, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjOption, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjOption, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjOption, unknown4c) == 0x4c, "");
static_assert(offsetof(GfMenuObjOption, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjOption, unknown98) == 0x98, "");
static_assert(offsetof(GfMenuObjOption, unknown120) == 0x120, "");
static_assert(offsetof(GfMenuObjOption, unknown128) == 0x128, "");
static_assert(offsetof(GfMenuObjOption, unknown3b8) == 0x3b8, "");
static_assert(offsetof(GfMenuObjOption, unknown3bc) == 0x3bc, "");
static_assert(offsetof(GfMenuObjOption, unknown3c0) == 0x3c0, "");
static_assert(offsetof(GfMenuObjOption, unknown3c1) == 0x3c1, "");
static_assert(offsetof(GfMenuObjOption, unknown3c2) == 0x3c2, "");
static_assert(sizeof(GfMenuObjOption::Level) == 2, "");
static_assert(sizeof(GfMenuObjOption) == 0x3c8, "");

} // namespace gf
