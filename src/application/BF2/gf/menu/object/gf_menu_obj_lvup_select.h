#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {
class GfMenuCallContext;
class GfMenuReferenceNumber;

class GfMenuObjLvupSelect : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjLvupSelect *owner) : _0c(), m_menuObjLvupSelect(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjLvupSelect *m_menuObjLvupSelect; // Inferred role: owner; original member name unknown.
  };

  class SelectListener : public ui::UIObjectListener {
  public:
    SelectListener(GfMenuObjLvupSelect *owner) : _0c(), m_menuObjLvupSelect(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjLvupSelect *m_menuObjLvupSelect; // Inferred role: owner; original member name unknown.
  };

  class DrImgListener : public ui::UIObjectListener {
  public:
    DrImgListener(GfMenuObjLvupSelect *owner) : _0c(), m_menuObjLvupSelect(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjLvupSelect *m_menuObjLvupSelect; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjLvupSelect(u32 handle);
  ~GfMenuObjLvupSelect() override;
  static void openLevelSelect(GfMenuCallContext *context, u32 level);
  static void openLevelup(GfMenuCallContext *context, u32 level, u32 levelMax);
  bool seqConfirmLevelUp();
  bool seqExecLevelUp();
  void updateBonusExp();
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0x28 - 0x24];
  GfMenuSequence<GfMenuObjLvupSelect, 8> unknown28; // Inferred role: queued steps; original member name unknown.
  bool unknown2b8;                                  // Role and original member name unknown, cleared by the constructor.
  u8 _2b9[0x2c0 - 0x2b9];
  u32 unknown2c0; // Inferred role: level to reach with the level up; original member name unknown.
  u8 _2c4[0x2c8 - 0x2c4];
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown2c8; // Inferred role: reference number; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown2d0; // Inferred role: reference number; original member name unknown.
  GfMenuCallContext *m_menuCallContext;                    // Inferred role: call context; original member name unknown.
};

static_assert(offsetof(GfMenuObjLvupSelect, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjLvupSelect, unknown2b8) == 0x2b8, "");
static_assert(offsetof(GfMenuObjLvupSelect, unknown2c0) == 0x2c0, "");
static_assert(offsetof(GfMenuObjLvupSelect, unknown2c8) == 0x2c8, "");
static_assert(offsetof(GfMenuObjLvupSelect, unknown2d0) == 0x2d0, "");
static_assert(offsetof(GfMenuObjLvupSelect, m_menuCallContext) == 0x2d8, "");
static_assert(sizeof(GfMenuObjLvupSelect) == 0x2e0, "");
static_assert(offsetof(GfMenuObjLvupSelect::MainListener, m_menuObjLvupSelect) == 0x20, "");
static_assert(sizeof(GfMenuObjLvupSelect::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjLvupSelect::SelectListener, m_menuObjLvupSelect) == 0x20, "");
static_assert(sizeof(GfMenuObjLvupSelect::SelectListener) == 0x28, "");
static_assert(offsetof(GfMenuObjLvupSelect::DrImgListener, m_menuObjLvupSelect) == 0x20, "");
static_assert(sizeof(GfMenuObjLvupSelect::DrImgListener) == 0x28, "");
} // namespace gf
