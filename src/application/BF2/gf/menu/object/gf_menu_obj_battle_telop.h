#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuReferenceNumber;

class GfMenuObjBattleTelop : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjBattleTelop *owner) : unknown0c(0), unknown10(), _18(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: fade control; original member name unknown.
    // Inferred role: display flags; original type name unknown.
    struct unknown004 {
      int unknown00; // Inferred role: telop shown flag; original member name unknown.
      int unknown04; // Inferred role: fade in flag; original member name unknown.
    } unknown10;
    u8 _18[0x1c - 0x18];
    GfMenuObjBattleTelop *unknown20; // Inferred role: owner; original member name unknown.
  };

  class UniteComboListener : public ui::UIObjectListener {
  public:
    UniteComboListener(GfMenuObjBattleTelop *owner) : unknown0c(0), unknown10(0), unknown14(0), unknown18(0), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c;                   // Inferred role: combo display state (1 fight combo shown, 2 bonus shown, 4 elemental combo shown); original member name unknown.
    int unknown10;                   // Inferred role: combo shown flag; original member name unknown.
    int unknown14;                   // Inferred role: number of combo steps; original member name unknown.
    int unknown18;                   // Inferred role: element combo control, -1 when none; original member name unknown.
    GfMenuObjBattleTelop *unknown20; // Inferred role: owner; original member name unknown.
  };

  struct OpenParam {
    u16 unknown00; // Inferred role: telop message; original member name unknown.
  };

  // Evidence: btl::UIManager::DispUniteComboUI (0x710008fb9c) builds it on the stack from its eight arguments; the elements are 4 bytes
  // (index byte, u8 argument, u16 argument) and the size is the u64 at 0x18.
  struct OpenUniteParam {
    // Inferred role: combo step; original type name unknown.
    struct unknown008 {
      u8 unknown00;  // Inferred role: step index; original member name unknown.
      u8 unknown01;  // Role and original member name unknown.
      u16 unknown02; // Role and original member name unknown.
    };

    OpenUniteParam() : unknown00(0), unknown04(0) {}

    int unknown00;                                 // Role and original member name unknown.
    int unknown04;                                 // Role and original member name unknown.
    mm::mtl::FixedVector<unknown008, 3> unknown08; // Inferred role: combo steps; original member name unknown.
  };

  GfMenuObjBattleTelop(u32 handle);
  ~GfMenuObjBattleTelop() override;
  static void open(const OpenParam &param);
  static void close();
  static void openUniteCombo(const OpenUniteParam &param);
  static void closeUniteCombo();
  void initialize() override;
  void finalize() override;
  void update() override;

  u32 unknown24;                                     // Role and original member name unknown, cleared by the constructor.
  GfMenuSequence<GfMenuObjBattleTelop, 8> unknown28; // Inferred role: queued steps; original member name unknown.
  bool unknown2b8;                                   // Role and original member name unknown, cleared by the constructor.
  u8 _2b9[0x2c0 - 0x2b9];
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown2c0[3];     // Inferred role: reference numbers; original member name unknown.
  mm::mtl::FixedVector<OpenUniteParam::unknown008, 3> unknown2d8; // Inferred role: unite combo steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjBattleTelop::MainListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjBattleTelop::MainListener, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjBattleTelop::MainListener::unknown004, unknown04) == 0x04, "");
static_assert(offsetof(GfMenuObjBattleTelop::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjBattleTelop::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjBattleTelop::UniteComboListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjBattleTelop::UniteComboListener, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjBattleTelop::UniteComboListener, unknown14) == 0x14, "");
static_assert(offsetof(GfMenuObjBattleTelop::UniteComboListener, unknown18) == 0x18, "");
static_assert(offsetof(GfMenuObjBattleTelop::UniteComboListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjBattleTelop::UniteComboListener) == 0x28, "");
static_assert(sizeof(GfMenuObjBattleTelop::OpenUniteParam::unknown008) == 0x04, "");
static_assert(offsetof(GfMenuObjBattleTelop::OpenUniteParam, unknown08) == 0x08, "");
static_assert(sizeof(GfMenuObjBattleTelop::OpenUniteParam) == 0x20, "");
static_assert(offsetof(GfMenuObjBattleTelop, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjBattleTelop, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBattleTelop, unknown2b8) == 0x2b8, "");
static_assert(offsetof(GfMenuObjBattleTelop, unknown2c0) == 0x2c0, "");
static_assert(offsetof(GfMenuObjBattleTelop, unknown2d8) == 0x2d8, "");
static_assert(sizeof(GfMenuObjBattleTelop) == 0x2f0, "");

} // namespace gf
