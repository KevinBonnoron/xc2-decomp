#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlCursorSelect;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuBladeList;
class GfMenuCallContext;
class GfMenuIDList;
struct GAME_VOICE_HANDLE;
class GfMenuReferenceNumber;

class GfMenuObjMercenaryForm : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;
  };

  class FormListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Role and original member name unknown, cleared by the opening event.
    int unknown10; // Role and original member name unknown, cleared by the opening event.
    u8 _14[0x20 - 0x14];
    GfMenuObjMercenaryForm *unknown20; // Inferred role: owner; original member name unknown.
  };

  // Only the member that reciveEvent (1.0.0: 0x7100494870) reads or writes is declared: the constructor is inlined in GfMenuObjMercenaryForm::initialize, which is not matched, so the rest of the
  // layout and the size are not proven.
  class ApplyListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: caption shown flag; original member name unknown.
  };

  class BlImgListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjMercenaryForm *unknown20; // Inferred role: owner; original member name unknown.
  };

  class StartListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjMercenaryForm *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjMercenaryForm(u32 handle);
  ~GfMenuObjMercenaryForm() override;
  bool chkTempUnlink(u32 blade);
  void addTempUnlink(u32 blade);
  void delTempUnlink(u32 blade);
  bool chkUnitBladeList(u32 blade);
  void addUnitBladeList(u32 blade);
  void refreshBladeInfo();
  void setDetailBladePos(u32 handle);
  void updateReserveBlade(u32 index);
  void refreshBladeList();
  void updateBladeCount(bool isDisp, bool isUpdate);
  bool seqApperBlade();
  bool seqConfirmRemoveBladeSet();
  bool seqDepartureEnd();
  bool seqDepartureNotice();
  bool seqDepartureStart();
  bool seqDispActiveFS();
  bool seqEndActiveFS();
  bool seqLeaveBlade();
  bool seqOpenActiveFS();
  bool seqOpenImage();
  bool seqPresetEnd();
  bool seqPresetLoad();
  bool seqPresetSave();
  bool seqReturnMissionSelect();
  bool seqRevertBladeSet();
  bool seqStartActiveFS();
  void sendOpenEvent(u32 handle, int type, f32 delay);
  void sendCloseEvent(u32 handle, int type, f32 delay);
  void initialize() override;
  void finalize() override;
  void update() override;

  u32 unknown24;                 // Inferred role: team; original member name unknown.
  GfMenuBladeList *unknown28;    // Inferred role: blades of the unit; original member name unknown.
  GfMenuBladeList *unknown30;    // Inferred role: reserve blades; original member name unknown.
  GfMenuBladeList *unknown38;    // Inferred role: blade list; original member name unknown.
  GfMenuBladeList *unknown40;    // Inferred role: blade list; original member name unknown.
  GfMenuBladeList *unknown48;    // Inferred role: blade list; original member name unknown.
  GfMenuBladeList *unknown50[3]; // Inferred role: blades of the presets; original member name unknown.
  GfMenuIDList *unknown68;       // Inferred role: preset ids; original member name unknown.
  u8 _70[0x78 - 0x70];
  ui::UISelectObjList *unknown78;                            // Inferred role: unit blade objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown80;                         // Inferred role: unit blade cursor; original member name unknown.
  ui::UISelectObjList *unknown88;                            // Inferred role: leader objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown90;                         // Inferred role: leader cursor; original member name unknown.
  ui::UISelectObjList *unknown98;                            // Inferred role: list blade objects; original member name unknown.
  ui::UICtrlCursorSelect *unknowna0;                         // Inferred role: list blade cursor; original member name unknown.
  ui::UISelectObjList *unknowna8;                            // Inferred role: preset objects; original member name unknown.
  ui::UICtrlCursorSelect *unknownb0;                         // Inferred role: preset cursor; original member name unknown.
  GfMenuCallContext *unknownb8;                              // Inferred role: call context; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknownc0[8]; // Inferred role: mission condition and field skill numbers; original member name unknown.
  u32 unknown100;                                            // Inferred role: unused; original member name unknown.
  int unknown104;                                            // Inferred role: frames left; original member name unknown.
  GfMenuSequence<GfMenuObjMercenaryForm, 10> unknown108;     // Inferred role: form steps; original member name unknown.
  bool unknown430;                                           // Inferred role: step started flag; original member name unknown.
  GfMenuSequence<GfMenuObjMercenaryForm, 4> unknown438;      // Inferred role: sub steps; original member name unknown.
  mm::mtl::FixedVector<u16, 422> unknown598;                 // Inferred role: blades unlinked from the unit until it is applied; original member name unknown.
  bool unknown8f0;                                           // Inferred role: unused; original member name unknown.
  GAME_VOICE_HANDLE *unknown8f8;                             // Inferred role: leader voice; original member name unknown.
};

static_assert(offsetof(GfMenuObjMercenaryForm::FormListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjMercenaryForm::FormListener, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjMercenaryForm::FormListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjMercenaryForm::ApplyListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjMercenaryForm::BlImgListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjMercenaryForm::StartListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown78) == 0x78, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknownb8) == 0xb8, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknownc0) == 0xc0, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown104) == 0x104, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown108) == 0x108, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown430) == 0x430, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown438) == 0x438, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown598) == 0x598, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown8f0) == 0x8f0, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown8f8) == 0x8f8, "");
static_assert(sizeof(GfMenuObjMercenaryForm) == 0x900, "");

} // namespace gf
