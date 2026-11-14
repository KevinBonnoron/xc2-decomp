#pragma once
#include <stddef.h>
#include <string.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

struct GF_OBJ_HANDLE;
class unknown135;

class GfMenuObjEnemyStatus : public GfMenuObject {
public:
  struct OpenParam {
    GF_OBJ_HANDLE *unknown00; // Inferred role: enemy handle; original member name unknown.
  };

  // Inferred role: enemy adapters cleared as a whole by the constructor; original name unknown.
  struct unknown005 {
    unknown005() { memset(this, 0, sizeof(*this)); }

    mm::mtl::FixedVector<unknown135 *, 25> unknown00; // Inferred role: adapters; original member name unknown.
  };

  class MainListener : public ui::UIObjectListener {
  public:
    // Inferred role: control ids of the reaction icon and of the pulse effect; original type name unknown.
    struct unknown006 {
      int unknown00; // Inferred role: reaction icon control, -1 when none; original member name unknown.
      int unknown04; // Inferred role: pulse effect control, -1 when none; original member name unknown.
    };

    MainListener(GfMenuObjEnemyStatus *owner) : unknown0c(0), unknown10(), _18(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: arts name shown flag; original member name unknown.
    unknown006 unknown10;
    u8 _18[0x1c - 0x18];
    GfMenuObjEnemyStatus *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ElemListener : public ui::UIObjectListener {
  public:
    ElemListener(GfMenuObjEnemyStatus *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjEnemyStatus *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjEnemyStatus(u32 handle);
  ~GfMenuObjEnemyStatus() override;
  static void open(const OpenParam &param);
  static void close();
  static void disp(bool isDisp);
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0x28 - 0x24];
  GF_OBJ_HANDLE *unknown28; // Inferred role: enemy handle read by the main listener, -1 at start; original member name unknown.
  unknown005 unknown30;     // Inferred role: enemy adapters; original member name unknown.
  int unknown100;           // Inferred role: unused, -1 at start; original member name unknown.
  u8 _104[0x108 - 0x104];
};

static_assert(sizeof(GfMenuObjEnemyStatus::unknown005) == 0xd0, "");
static_assert(offsetof(GfMenuObjEnemyStatus, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjEnemyStatus, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjEnemyStatus, unknown100) == 0x100, "");
static_assert(sizeof(GfMenuObjEnemyStatus) == 0x108, "");
static_assert(offsetof(GfMenuObjEnemyStatus::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjEnemyStatus::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjEnemyStatus::ElemListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjEnemyStatus::ElemListener) == 0x28, "");

} // namespace gf
