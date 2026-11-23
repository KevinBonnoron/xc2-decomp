#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuObjChainCount : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjChainCount *owner) : unknown0c(0), unknown10(0), unknown14(0), unknown18(0), m_menuObjChainCount(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: id of the running fade control; original member name unknown.
    union {
      u64 unknown10_u64; // Both flags as one 64-bit slot: the game clears them with a single store.
      struct {
        int unknown10; // Inferred role: opened flag; original member name unknown.
        int unknown14; // Inferred role: faded in flag; original member name unknown.
      };
    };
    int unknown18; // Inferred role: hidden flag; original member name unknown.
    u8 _1c[0x20 - 0x1c];
    GfMenuObjChainCount *m_menuObjChainCount; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjChainCount(u32 handle);
  ~GfMenuObjChainCount() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void open();
  static void close();
};

static_assert(offsetof(GfMenuObjChainCount::MainListener, m_menuObjChainCount) == 0x20, "");
static_assert(offsetof(GfMenuObjChainCount::MainListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjChainCount::MainListener, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjChainCount::MainListener, unknown14) == 0x14, "");
static_assert(offsetof(GfMenuObjChainCount::MainListener, unknown18) == 0x18, "");
static_assert(sizeof(GfMenuObjChainCount::MainListener) == 0x28, "");

} // namespace gf
