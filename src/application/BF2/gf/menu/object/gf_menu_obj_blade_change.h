#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {
class GfMenuCallContext;

class GfMenuObjBladeChange : public GfMenuObject {
public:
  // Inferred role: state of a blade face; original name unknown.
  struct unknown004 {
    unknown004() : unknown00(-1), unknown04(0) {}

    int unknown00; // Inferred role: unused, -1 at start; original member name unknown.
    u32 unknown04; // Inferred role: face flags; original member name unknown.
  };

  GfMenuObjBladeChange(u32 handle);
  ~GfMenuObjBladeChange() override;
  static void close();
  static void startChainAttack(GfMenuCallContext *context);
  static void exitChainAttack();
  static void open();
  static void pushGroupUp();
  void initialize() override;
  void finalize() override;
  void update() override;
  static void enableAwakening(bool);
  static void pushBladeChange(unsigned int blade);
  static void dispInfo(bool isDisp);

  int unknown24;           // Inferred role: awakening control, -1 when idle; original member name unknown.
  int unknown28;           // Inferred role: unused, -1 at start; original member name unknown.
  bool unknown2c;          // Inferred role: awakening; original member name unknown.
  bool unknown2d;          // Inferred role: unused; original member name unknown.
  bool unknown2e;          // Inferred role: chain attack; original member name unknown.
  unknown004 unknown30[3]; // Inferred role: face states; original member name unknown.
  int unknown48;           // Inferred role: unused, -1 at start; original member name unknown.
  int unknown4c;           // Inferred role: unused, -1 at start; original member name unknown.
  int unknown50;           // Inferred role: unused, -1 at start; original member name unknown.
  int unknown54;           // Inferred role: unused, -1 at start; original member name unknown.
};

static_assert(offsetof(GfMenuObjBladeChange, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjBladeChange, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBladeChange, unknown2c) == 0x2c, "");
static_assert(offsetof(GfMenuObjBladeChange, unknown2d) == 0x2d, "");
static_assert(offsetof(GfMenuObjBladeChange, unknown2e) == 0x2e, "");
static_assert(offsetof(GfMenuObjBladeChange, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjBladeChange, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjBladeChange, unknown4c) == 0x4c, "");
static_assert(offsetof(GfMenuObjBladeChange, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjBladeChange, unknown54) == 0x54, "");
static_assert(sizeof(GfMenuObjBladeChange) == 0x58, "");

} // namespace gf
