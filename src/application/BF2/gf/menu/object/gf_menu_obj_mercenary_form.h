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
    MainListener(GfMenuObjMercenaryForm *owner) : _0c(), m_menuObjMercenaryForm(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjMercenaryForm *m_menuObjMercenaryForm; // Inferred role: owner; original member name unknown.
  };

  class FormListener : public ui::UIObjectListener {
  public:
    FormListener(GfMenuObjMercenaryForm *owner) : unknown0c(0), unknown10(0), _14(), m_menuObjMercenaryForm(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Role and original member name unknown, cleared by the opening event.
    int unknown10; // Role and original member name unknown, cleared by the opening event.
    u8 _14[0x1c - 0x14];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjMercenaryForm *m_menuObjMercenaryForm; // Inferred role: owner; original member name unknown.
  };

  class UnitListener : public ui::UIObjectListener {
  public:
    UnitListener(GfMenuObjMercenaryForm *owner) : _0c(), m_menuObjMercenaryForm(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjMercenaryForm *m_menuObjMercenaryForm; // Inferred role: owner; original member name unknown.
  };

  class ApplyListener : public ui::UIObjectListener {
  public:
    ApplyListener(GfMenuObjMercenaryForm *owner) : unknown0c(0), _10(), m_menuObjMercenaryForm(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: caption shown flag; original member name unknown.
    u8 _10[0x1c - 0x10];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjMercenaryForm *m_menuObjMercenaryForm; // Inferred role: owner; original member name unknown.
  };

  class ListListener : public ui::UIObjectListener {
  public:
    ListListener(GfMenuObjMercenaryForm *owner) : _0c(), m_menuObjMercenaryForm(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjMercenaryForm *m_menuObjMercenaryForm; // Inferred role: owner; original member name unknown.
  };

  class PresetListener : public ui::UIObjectListener {
  public:
    PresetListener(GfMenuObjMercenaryForm *owner) : unknown0c(0), _10(), m_menuObjMercenaryForm(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: preset mode, 0 queues seqPresetSave and any other value seqPresetLoad (event 0x21 stores its first parameter, event 8 tests it); original member name unknown.
    u8 _10[0x1c - 0x10];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjMercenaryForm *m_menuObjMercenaryForm; // Inferred role: owner; original member name unknown.
  };

  class LeaderListener : public ui::UIObjectListener {
  public:
    LeaderListener(GfMenuObjMercenaryForm *owner) : _0c(), m_menuObjMercenaryForm(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjMercenaryForm *m_menuObjMercenaryForm; // Inferred role: owner; original member name unknown.
  };

  class StartListener : public ui::UIObjectListener {
  public:
    StartListener(GfMenuObjMercenaryForm *owner) : _0c(), m_menuObjMercenaryForm(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjMercenaryForm *m_menuObjMercenaryForm; // Inferred role: owner; original member name unknown.
  };

  class BlImgListener : public ui::UIObjectListener {
  public:
    BlImgListener(GfMenuObjMercenaryForm *owner) : _0c(), m_menuObjMercenaryForm(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjMercenaryForm *m_menuObjMercenaryForm; // Inferred role: owner; original member name unknown.
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
  GfMenuIDList *m_menuIDList;    // Inferred role: preset ids; original member name unknown.
  u8 _70[0x78 - 0x70];
  ui::UISelectObjList *unknown78;                            // Inferred role: unit blade objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown80;                         // Inferred role: unit blade cursor; original member name unknown.
  ui::UISelectObjList *unknown88;                            // Inferred role: leader objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown90;                         // Inferred role: leader cursor; original member name unknown.
  ui::UISelectObjList *unknown98;                            // Inferred role: list blade objects; original member name unknown.
  ui::UICtrlCursorSelect *unknowna0;                         // Inferred role: list blade cursor; original member name unknown.
  ui::UISelectObjList *unknowna8;                            // Inferred role: preset objects; original member name unknown.
  ui::UICtrlCursorSelect *unknownb0;                         // Inferred role: preset cursor; original member name unknown.
  GfMenuCallContext *m_menuCallContext;                      // Inferred role: call context; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknownc0[8]; // Inferred role: mission condition and field skill numbers; original member name unknown.
  u32 unknown100;                                            // Inferred role: unused; original member name unknown.
  int unknown104;                                            // Inferred role: frames left; original member name unknown.
  GfMenuSequence<GfMenuObjMercenaryForm, 10> unknown108;     // Inferred role: form steps; original member name unknown.
  bool unknown430;                                           // Inferred role: step started flag; original member name unknown.
  GfMenuSequence<GfMenuObjMercenaryForm, 4> unknown438;      // Inferred role: sub steps; original member name unknown.
  mm::mtl::FixedVector<u16, 422> unknown598;                 // Inferred role: blades unlinked from the unit until it is applied; original member name unknown.
  bool unknown8f0;                                           // Inferred role: unused; original member name unknown.
  GAME_VOICE_HANDLE *m_GAME_VOICE_HANDLE;                    // Inferred role: leader voice; original member name unknown.
};

static_assert(offsetof(GfMenuObjMercenaryForm::FormListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjMercenaryForm::FormListener, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjMercenaryForm::FormListener, m_menuObjMercenaryForm) == 0x20, "");
static_assert(offsetof(GfMenuObjMercenaryForm::ApplyListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjMercenaryForm::PresetListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjMercenaryForm::BlImgListener, m_menuObjMercenaryForm) == 0x20, "");
static_assert(offsetof(GfMenuObjMercenaryForm::StartListener, m_menuObjMercenaryForm) == 0x20, "");
static_assert(sizeof(GfMenuObjMercenaryForm::MainListener) == 0x28, "");
static_assert(sizeof(GfMenuObjMercenaryForm::FormListener) == 0x28, "");
static_assert(sizeof(GfMenuObjMercenaryForm::UnitListener) == 0x28, "");
static_assert(sizeof(GfMenuObjMercenaryForm::ApplyListener) == 0x28, "");
static_assert(sizeof(GfMenuObjMercenaryForm::ListListener) == 0x28, "");
static_assert(sizeof(GfMenuObjMercenaryForm::PresetListener) == 0x28, "");
static_assert(sizeof(GfMenuObjMercenaryForm::LeaderListener) == 0x28, "");
static_assert(sizeof(GfMenuObjMercenaryForm::StartListener) == 0x28, "");
static_assert(sizeof(GfMenuObjMercenaryForm::BlImgListener) == 0x28, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjMercenaryForm, m_menuIDList) == 0x68, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown78) == 0x78, "");
static_assert(offsetof(GfMenuObjMercenaryForm, m_menuCallContext) == 0xb8, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknownc0) == 0xc0, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown104) == 0x104, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown108) == 0x108, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown430) == 0x430, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown438) == 0x438, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown598) == 0x598, "");
static_assert(offsetof(GfMenuObjMercenaryForm, unknown8f0) == 0x8f0, "");
static_assert(offsetof(GfMenuObjMercenaryForm, m_GAME_VOICE_HANDLE) == 0x8f8, "");
static_assert(sizeof(GfMenuObjMercenaryForm) == 0x900, "");

} // namespace gf
