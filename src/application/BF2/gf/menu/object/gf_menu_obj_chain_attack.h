#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"
#include "ui/input/ui_input_layer.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjChainAttack : public GfMenuObject, public ui::IUIInputSelectionChecker {
public:
  class ExtendListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: shown flag; original member name unknown.
  };

  class StartListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;
  };

  class ResultListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: result display state, 0 closed and 1 shown; the event 0x21 stores the time of the event in hundredths of a second here before the state 1, and the event 0xc reads
                   // it as such; original member name unknown.
  };

  struct ResultParam {
    u8 unknown00;  // Inferred role: event parameter; original member name unknown.
    u32 unknown04; // Inferred role: event parameter; original member name unknown.
  };

  // Layout evidence: openTurnSelect (0x7100426090) reads up to three words at 0x00, 0x04 and 0x08 after testing the size word at 0x10 against 0, 1 and 2; original type name unknown.
  struct TurnSelectParam {
    mm::mtl::FixedVector<u32, 3> unknown00; // Inferred role: turn select characters; original member name unknown.
  };

  GfMenuObjChainAttack(u32 handle);
  ~GfMenuObjChainAttack() override;
  static void openStatus(GfMenuCallContext *context);
  static void openStart(GfMenuCallContext *context);
  static void openFullBurst(GfMenuCallContext *context);
  static void openTurnSelect(GfMenuCallContext *context, const TurnSelectParam &param);
  static void closeTurnSelect(GfMenuCallContext *context);
  static void openResult(const ResultParam &param);
  static void closeResult();
  static void closeRoundExtend();
  static void openRoundExtend();
  static void closeStatus();
  static void changeCharacter(u32 character);
  void initialize() override;
  void finalize() override;
  void update() override;
  bool isEnableSelect(u32 handle, int index) override;

  u64 unknown30; // Role and original member name unknown, cleared by the constructor.
  u64 unknown38; // Role and original member name unknown, cleared by the constructor.
  u64 unknown40; // Role and original member name unknown, cleared by the constructor.
  u64 unknown48; // Role and original member name unknown, cleared by the constructor.
  u32 unknown50; // Role and original member name unknown, cleared by the constructor.
};

static_assert(offsetof(GfMenuObjChainAttack, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjChainAttack, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjChainAttack, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjChainAttack, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjChainAttack, unknown50) == 0x50, "");
static_assert(sizeof(GfMenuObjChainAttack) == 0x58, "");

static_assert(offsetof(GfMenuObjChainAttack::ResultParam, unknown04) == 0x4, "");
static_assert(sizeof(GfMenuObjChainAttack::ResultParam) == 0x8, "");
static_assert(sizeof(GfMenuObjChainAttack::TurnSelectParam) == 0x18, "");
static_assert(sizeof(GfMenuObjChainAttack::StartListener) == 0x10, "");
static_assert(offsetof(GfMenuObjChainAttack::ResultListener, unknown0c) == 0xc, "");
static_assert(sizeof(GfMenuObjChainAttack::ResultListener) == 0x10, "");

} // namespace gf
