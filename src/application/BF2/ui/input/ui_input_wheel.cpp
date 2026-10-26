#include "ui/input/ui_input_wheel.h"

#include "framework/memory/framework_memory.h"

namespace ui {

UIInputWheel::UIInputWheel(u32 handle, u32 priority, const WheelSetup &setup) : UIInputLayer(handle, priority, setup), unknown1e0(setup.unknown188), unknown1e2(setup.unknown18a), unknown1e4(false) {}

UIInputWheel *UIInputWheel::create(u32 handle, u32 priority, const WheelSetup &setup, mm::mtl::IAllocator *allocator) {
// __LINE__ is the line argument of the operator new call.
#line 40
  return new (allocator, 16, __FILE__, __LINE__) UIInputWheel(handle, priority, setup);
}

UIInputWheel::~UIInputWheel() { ; }

const EventData *UIInputWheel::getInputEventExt() { return &unknown10; }

UIInputWheel *UIInputWheel::castUIInputWheel() { return this; }

} // namespace ui
