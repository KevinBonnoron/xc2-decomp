#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
class UIObjectNumberPlugin;
class UIObjectTextPlugin;
class UIObjectTimePlugin;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuBladeList;
class GfMenuCallContext;
class GfMenuDriverList;
class GfMenuReferenceNumber;

class GfMenuObjSaveLoad2 : public GfMenuObject {
public:
  GfMenuObjSaveLoad2(u32 handle);
  ~GfMenuObjSaveLoad2() override;
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle, u32 type);
  static int setFadeOut(u32 handle, u32 type);
  void refreshSave(ui::UIObjectAcc &acc, u32 flag);
  bool seqSave();
  bool seqSaveWait();
  bool seqSaveWaitToClose();
  void initialize() override;
  void finalize() override;
  void update() override;
  struct OpenParam {
    u16 unknown00; // Inferred role: mode; original member name unknown.
  };

  static void registOpenParam(const OpenParam &param);

  u8 _24[0x28 - 0x24];
  GfMenuCallContext *unknown28;                    // Inferred role: call context; original member name unknown.
  GfMenuSequence<GfMenuObjSaveLoad2, 8> unknown30; // Inferred role: queued steps; original member name unknown.
  int unknown2c0;                                  // Role and original member name unknown, set to -1 by the constructor.
  u16 unknown2c4;                                  // Role and original member name unknown, cleared by the constructor.
  u8 _2c6[0x2c8 - 0x2c6];
  ui::UISelectObjList *unknown2c8;                            // Inferred role: slot objects; original member name unknown.
  ui::UIObjectTimePlugin *unknown2d0;                         // Inferred role: time plugin; original member name unknown.
  ui::UIObjectTimePlugin *unknown2d8;                         // Inferred role: time plugin; original member name unknown.
  ui::UIObjectNumberPlugin *unknown2e0;                       // Inferred role: number plugin; original member name unknown.
  ui::UIObjectTimePlugin *unknown2e8;                         // Inferred role: time plugin; original member name unknown.
  ui::UIObjectTextPlugin *unknown2f0;                         // Inferred role: text plugin; original member name unknown.
  GfMenuDriverList *unknown2f8;                               // Inferred role: drivers; original member name unknown.
  GfMenuBladeList *unknown300;                                // Inferred role: blades; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown308[3]; // Inferred role: reference numbers; original member name unknown.
};

static_assert(offsetof(GfMenuObjSaveLoad2, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjSaveLoad2, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjSaveLoad2, unknown2c0) == 0x2c0, "");
static_assert(offsetof(GfMenuObjSaveLoad2, unknown2c4) == 0x2c4, "");
static_assert(offsetof(GfMenuObjSaveLoad2, unknown2c8) == 0x2c8, "");
static_assert(offsetof(GfMenuObjSaveLoad2, unknown2d0) == 0x2d0, "");
static_assert(offsetof(GfMenuObjSaveLoad2, unknown2d8) == 0x2d8, "");
static_assert(offsetof(GfMenuObjSaveLoad2, unknown2e0) == 0x2e0, "");
static_assert(offsetof(GfMenuObjSaveLoad2, unknown2e8) == 0x2e8, "");
static_assert(offsetof(GfMenuObjSaveLoad2, unknown2f0) == 0x2f0, "");
static_assert(offsetof(GfMenuObjSaveLoad2, unknown2f8) == 0x2f8, "");
static_assert(offsetof(GfMenuObjSaveLoad2, unknown300) == 0x300, "");
static_assert(offsetof(GfMenuObjSaveLoad2, unknown308) == 0x308, "");
static_assert(sizeof(GfMenuObjSaveLoad2) == 0x320, "");

} // namespace gf
