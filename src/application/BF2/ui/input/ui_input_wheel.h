#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/input/ui_input_layer.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace ui {

class UIInputWheel : public UIInputLayer {
public:
  struct WheelSetup : InputSetup {
    u16 unknown188; // Role and original member name unknown.
    u16 unknown18a; // Role and original member name unknown.
  };

  UIInputWheel(u32 handle, u32 priority, const WheelSetup &setup);
  static UIInputWheel *create(u32 handle, u32 priority, const WheelSetup &setup, mm::mtl::IAllocator *allocator);
  virtual ~UIInputWheel();
  virtual const EventData *getInputEventExt();
  virtual UIInputWheel *castUIInputWheel();
  virtual bool updateImpl();

  u16 unknown1e0;  // Role and original member name unknown.
  u16 unknown1e2;  // Role and original member name unknown.
  bool unknown1e4; // Role and original member name unknown.
  u8 unknown1e5[0x1e8 - 0x1e5];
};

static_assert(offsetof(UIInputWheel, unknown1e0) == 0x1e0, "");
static_assert(offsetof(UIInputWheel, unknown1e2) == 0x1e2, "");
static_assert(offsetof(UIInputWheel, unknown1e4) == 0x1e4, "");
static_assert(sizeof(UIInputWheel) == 0x1e8, "");

} // namespace ui
