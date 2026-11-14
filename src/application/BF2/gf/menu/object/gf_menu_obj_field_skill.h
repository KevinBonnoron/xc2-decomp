#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {
class GfMenuCallContext;
class GfMenuFieldSkillList;
class GfMenuReferenceFs;
class GfMenuReferenceNumber;
struct GAME_VOICE_HANDLE;

class GfMenuObjFieldSkill : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjFieldSkill *unknown20; // Inferred role: owner; original member name unknown.
  };

  class InputListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;
  };

  // Only the member that reciveEvent (1.0.0: 0x71004684c8) reads or writes is declared: the constructor is inlined in GfMenuObjFieldSkill::initialize, which is not matched (it allocates each of its
  // seven listeners with 0x28 bytes, 0x7100467290..0x7100467b84), so the rest of the layout is not proven.
  class BladeListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: shown flag; original member name unknown.
  };

  struct OpenSkillInfoParam {
    u32 unknown00_0 : 16; // Inferred role: skill; original member name unknown.
    u32 unknown00_16 : 8; // Inferred role: level; original member name unknown.
    u32 unknown00_24 : 8; // Role and original member name unknown, completes the 32-bit word that openSkillInfo loads at once.
    u8 _04[0x0c - 0x04];
    u16 unknown0c; // Inferred role: blade; original member name unknown.
  };

  struct OpenResultParam {
    u8 unknown00;  // Inferred role: result type; original member name unknown.
    u8 *unknown08; // Inferred role: message bdat; original member name unknown.
    u32 unknown10; // Inferred role: message id; original member name unknown.
    u32 unknown14; // Inferred role: result parameter; original member name unknown.
  };

  ~GfMenuObjFieldSkill() override;
  static void attachSkip(GfMenuCallContext *context);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void applyImageParam(u32 handle);
  static void close(GfMenuCallContext *context);
  static void setSkipInput(GfMenuCallContext *context, bool skip);
  static void openSkillInfo(GfMenuCallContext *context, u8 unknown, const OpenSkillInfoParam &param);
  static void closeSkillInfo(GfMenuCallContext *context, u8 unknown);
  static void openResult(GfMenuCallContext *context, const OpenResultParam &param);
  static void closeResult(GfMenuCallContext *context);
  static void closeTotalInfo(GfMenuCallContext *context);
  static void addTotalSkillLevel(u8 skill, u8 level);
  static void setCurrentTotalSkill(u8 skill);
  static void undoTotalSkillLevel(u8 skill);
  bool seqWaitVoice();

  u8 _24[0x28 - 0x24];
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown28; // Inferred role: reference number; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown30; // Inferred role: reference number; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown38; // Inferred role: reference number; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown40; // Inferred role: reference number; original member name unknown.
  GfMenuFieldSkillList *unknown48;                        // Inferred role: field skills; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceFs> unknown50;     // Inferred role: field skill reference; original member name unknown.
  u16 unknown58;                                          // Role and original member name unknown, cleared by the constructor.
  bool unknown5a;                                         // Role and original member name unknown, cleared by the constructor.
  u8 _5b[0x5c - 0x5b];
  u16 unknown5c; // Role and original member name unknown, cleared by the constructor.
  u8 _5e[0x60 - 0x5e];
  u32 unknown60; // Inferred role: main object handle, set by the closing event of the main listener; original member name unknown.
  u8 _64[0x68 - 0x64];
  GAME_VOICE_HANDLE *unknown68;                     // Inferred role: playing voice; original member name unknown.
  GfMenuSequence<GfMenuObjFieldSkill, 4> unknown70; // Inferred role: queued steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjFieldSkill, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjFieldSkill, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjFieldSkill, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjFieldSkill, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjFieldSkill, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjFieldSkill, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjFieldSkill::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjFieldSkill::BladeListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjFieldSkill, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjFieldSkill, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjFieldSkill, unknown5a) == 0x5a, "");
static_assert(offsetof(GfMenuObjFieldSkill, unknown5c) == 0x5c, "");
static_assert(offsetof(GfMenuObjFieldSkill, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjFieldSkill, unknown70) == 0x70, "");
static_assert(sizeof(GfMenuObjFieldSkill) == 0x1d0, "");

} // namespace gf
