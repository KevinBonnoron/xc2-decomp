#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuCallContext;

class GfMenuObjPartyStatus : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjPartyStatus *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];             // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjPartyStatus *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ComboReqListener : public ui::UIObjectListener {
  public:
    ComboReqListener(GfMenuObjPartyStatus *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];             // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjPartyStatus *unknown20; // Inferred role: owner; original member name unknown.
  };

  struct RequestParam {
    u16 unknown00; // Inferred role: event parameter; original member name unknown.
    u16 unknown02; // Inferred role: event parameter; original member name unknown.
    u32 unknown04; // Inferred role: event parameter; original member name unknown.
    u8 unknown08;  // Inferred role: event parameter; original member name unknown.
  };

  GfMenuObjPartyStatus(u32 handle);
  ~GfMenuObjPartyStatus() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void lock(bool lock);
  static void open(bool isLock);
  static void close(bool isImmediate);
  static void attachComboRequest(GfMenuCallContext *context);
  static void memberChange(u16 member, u32 value);
  static void openComboRequest(u16 index, const RequestParam &param);
  static void closeComboRequest(u16 index, bool isImmediate);
  static void resetComboRequest(u16 index, const RequestParam &param);
  void closePartyStatus(u32 handle, int member);
  int openPartyStatus(u32 handle, int member);
  void setupComboReq(const ui::UIObjectAcc &acc, u16 index, u16 combo, bool isEnable, u16 effect, u32 button);

  u8 _24[0x30 - 0x24];
  int unknown30[2]; // Inferred role: unused, -1 at start; original member name unknown.
  int unknown38;    // Inferred role: unused, -1 at start; original member name unknown.
  bool unknown3c;   // Role and original member name unknown, cleared by the constructor.
  u8 _3d[0x50 - 0x3d];
};

static_assert(offsetof(GfMenuObjPartyStatus, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjPartyStatus, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjPartyStatus, unknown3c) == 0x3c, "");
static_assert(sizeof(GfMenuObjPartyStatus) == 0x50, "");
static_assert(offsetof(GfMenuObjPartyStatus::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjPartyStatus::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjPartyStatus::ComboReqListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjPartyStatus::ComboReqListener) == 0x28, "");

static_assert(offsetof(GfMenuObjPartyStatus::RequestParam, unknown02) == 0x2, "");
static_assert(offsetof(GfMenuObjPartyStatus::RequestParam, unknown04) == 0x4, "");
static_assert(offsetof(GfMenuObjPartyStatus::RequestParam, unknown08) == 0x8, "");
static_assert(sizeof(GfMenuObjPartyStatus::RequestParam) == 0xc, "");

} // namespace gf
