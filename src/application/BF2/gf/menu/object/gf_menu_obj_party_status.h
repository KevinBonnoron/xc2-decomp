#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjPartyStatus : public GfMenuObject {
public:
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
  static void closeComboRequest(u16 index, bool isImmediate);
  void closePartyStatus(u32 handle, int member);
  int openPartyStatus(u32 handle, int member);

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

} // namespace gf
