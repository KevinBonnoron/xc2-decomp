#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace ui {
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuBladeList;
class GfMenuCallContext;
class GfMenuItemList;
class GfMenuReferenceNumber;

class GfMenuObjBlWeapon2 : public GfMenuObject {
public:
  GfMenuObjBlWeapon2(u32 handle);
  ~GfMenuObjBlWeapon2() override;

  struct OpenParam {
    u16 unknown00; // Inferred role: open mode; original member name unknown.
    u32 unknown04; // Inferred role: weapon; original member name unknown.
  };

  // Inferred role: layer parameter built from OpenParam; original type name unknown.
  struct unknown002 {
    u16 unknown00; // Inferred role: open mode; original member name unknown.
    u16 unknown02; // Inferred role: weapon; original member name unknown.
  };

  static void registOpenParam(const OpenParam &param);
  static void openForShop(u32 weapon);
  static bool attach(GfMenuCallContext *context);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  static bool isSameWeapon(u32 blade, u32 chip);
  static bool isDownWeapon(u32 blade, u32 chip);
  void initialize() override;
  void finalize() override;
  void update() override;
  void closeCharChange();
  void openCharChange();
  bool seqStart();
  bool seqSrcLeave();
  bool seqSrcAppear();
  bool seqDstResume();
  bool seqEnd();

  u8 _24[0x28 - 0x24];
  GfMenuItemList *unknown28;                              // Inferred role: blade chips; original member name unknown.
  ui::UISelectObjList *unknown30;                         // Inferred role: chip objects; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown38; // Inferred role: reference number; original member name unknown.
  GfMenuCallContext *unknown40;                           // Inferred role: call context; original member name unknown.
  u8 _48[0x50 - 0x48];
  GfMenuCallContext *unknown50;                    // Inferred role: call context; original member name unknown.
  GfMenuSequence<GfMenuObjBlWeapon2, 8> unknown58; // Inferred role: weapon change steps; original member name unknown.
  bool unknown2e8;                                 // Inferred role: control started flag; original member name unknown.
  u8 _2e9[0x2ec - 0x2e9];
  u32 unknown2ec; // Role and original member name unknown, cleared by the constructor.
  u32 unknown2f0; // Role and original member name unknown, cleared by the constructor.
  u8 _2f4[0x2f8 - 0x2f4];
  GfMenuBladeList *unknown2f8; // Inferred role: blades; original member name unknown.
  bool unknown300;             // Role and original member name unknown, cleared by the constructor.
  u8 _301[0x308 - 0x301];
};

static_assert(offsetof(GfMenuObjBlWeapon2::OpenParam, unknown04) == 0x04, "");
static_assert(sizeof(GfMenuObjBlWeapon2::OpenParam) == 0x08, "");
static_assert(offsetof(GfMenuObjBlWeapon2::unknown002, unknown02) == 0x02, "");
static_assert(sizeof(GfMenuObjBlWeapon2::unknown002) == 0x04, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown2e8) == 0x2e8, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown2ec) == 0x2ec, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown2f0) == 0x2f0, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown2f8) == 0x2f8, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown300) == 0x300, "");
static_assert(sizeof(GfMenuObjBlWeapon2) == 0x308, "");

} // namespace gf
