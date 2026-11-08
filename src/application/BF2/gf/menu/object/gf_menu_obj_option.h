#pragma once
#include <stddef.h>

#include "gf/data/gf_data_option.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace ui {
class UICtrlCursorSelect;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuCallContext;

class GfMenuObjOption : public GfMenuObject {
public:
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
  u32 unknown48;                                 // Role and original member name unknown, cleared by the constructor.
  u32 unknown4c;                                 // Role and original member name unknown, cleared by the constructor.
  mm::mtl::FixedVector<u16, 32> unknown50;       // Inferred role: option levels; original member name unknown.
  SDataOption unknown98;                         // Inferred role: option data being edited; original member name unknown.
  GfMenuCallContext *unknown120;                 // Inferred role: call context; original member name unknown.
  GfMenuSequence<GfMenuObjOption, 8> unknown128; // Inferred role: queued steps; original member name unknown.
  bool unknown3b8;                               // Role and original member name unknown, cleared by the constructor.
  int unknown3bc;                                // Role and original member name unknown, -1 at start.
  u16 unknown3c0;                                // Role and original member name unknown, cleared by the constructor.
  u8 unknown3c2;                                 // Role and original member name unknown, 0xff at start.
  u8 _3c3[0x3c8 - 0x3c3];
};

static_assert(offsetof(GfMenuObjOption, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjOption, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjOption, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjOption, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjOption, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjOption, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjOption, unknown98) == 0x98, "");
static_assert(offsetof(GfMenuObjOption, unknown120) == 0x120, "");
static_assert(offsetof(GfMenuObjOption, unknown128) == 0x128, "");
static_assert(offsetof(GfMenuObjOption, unknown3b8) == 0x3b8, "");
static_assert(offsetof(GfMenuObjOption, unknown3bc) == 0x3bc, "");
static_assert(offsetof(GfMenuObjOption, unknown3c0) == 0x3c0, "");
static_assert(sizeof(GfMenuObjOption) == 0x3c8, "");

} // namespace gf
