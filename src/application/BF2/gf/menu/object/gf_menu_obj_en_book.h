#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace ui {
class UICtrlCursorSelect;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuIDList;
class GfMenuModelView;
class GfMenuMsgList;

class GfMenuObjEnBook : public GfMenuObject {
public:
  GfMenuObjEnBook(u32 handle);
  ~GfMenuObjEnBook() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  void setupFamilyMsgList();
  void refreshFamilyList();
  void refreshGenusMsgList();
  void setupMapIDList();
  bool isBattled(u32 id);
  bool isDefeated(u32 id);
  void deleteCurEnemyModel();
  bool seqWaitLoading();
  bool seqStartTop();
  bool seqDeleteEnmey();
  bool seqCreateEnmey();
  bool seqFadeOutEnmey();

  u32 unknown24;                     // Role and original member name unknown, cleared by the constructor.
  u32 unknown28;                     // Role and original member name unknown, cleared by the constructor.
  u32 unknown2c;                     // Role and original member name unknown, cleared by the constructor.
  ui::UISelectObjList *unknown30;    // Inferred role: top menu objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown38; // Inferred role: top menu cursor; original member name unknown.
  GfMenuMsgList *unknown40;          // Inferred role: messages; original member name unknown.
  ui::UISelectObjList *unknown48;    // Inferred role: list objects; original member name unknown.
  GfMenuMsgList *unknown50;          // Inferred role: messages; original member name unknown.
  ui::UISelectObjList *unknown58;    // Inferred role: list objects; original member name unknown.
  GfMenuIDList *unknown60;           // Inferred role: identifiers; original member name unknown.
  GfMenuIDList *unknown68;           // Inferred role: identifiers; original member name unknown.
  ui::UISelectObjList *unknown70;    // Inferred role: list objects; original member name unknown.
  ui::UISelectObjList *unknown78;    // Inferred role: list objects; original member name unknown.
  GfMenuModelView *unknown80;        // Inferred role: model view; original member name unknown.
  u32 unknown88;                     // Role and original member name unknown, cleared by the constructor.
  u8 _8c[0x90 - 0x8c];
  GfMenuSequence<GfMenuObjEnBook, 8> unknown90; // Inferred role: queued steps; original member name unknown.
  bool unknown320;                              // Role and original member name unknown, cleared by the constructor.
  u8 _321[0x328 - 0x321];
};

static_assert(offsetof(GfMenuObjEnBook, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjEnBook, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjEnBook, unknown2c) == 0x2c, "");
static_assert(offsetof(GfMenuObjEnBook, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjEnBook, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjEnBook, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjEnBook, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjEnBook, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjEnBook, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjEnBook, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjEnBook, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjEnBook, unknown70) == 0x70, "");
static_assert(offsetof(GfMenuObjEnBook, unknown78) == 0x78, "");
static_assert(offsetof(GfMenuObjEnBook, unknown80) == 0x80, "");
static_assert(offsetof(GfMenuObjEnBook, unknown88) == 0x88, "");
static_assert(offsetof(GfMenuObjEnBook, unknown90) == 0x90, "");
static_assert(offsetof(GfMenuObjEnBook, unknown320) == 0x320, "");
static_assert(sizeof(GfMenuObjEnBook) == 0x328, "");

} // namespace gf
