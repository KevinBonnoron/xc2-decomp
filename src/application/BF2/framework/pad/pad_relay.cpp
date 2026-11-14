#include "framework/pad/pad_res_event.h"
#include "framework/pad/pad_res_event_manager.h"
#include "fw/fw_pad.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/map.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

PadRelay::PadRelay() : unknown00(-1), unknown04(-1) {}

PadRelay::~PadRelay() {}

void PadRelay::bind(int padNo, int type, mm::mtl::IAllocator *allocator) {
  unknown00 = padNo;
  unknown04 = type;
  unknown08.setAllocator(allocator);
  unknown20.setAllocator(allocator);
}

void PadRelay::unbind() {
  unknown20.clear();
  unknown08.clear();
  unknown20.setAllocator(nullptr);
  unknown08.setAllocator(nullptr);
  unknown00 = -1;
  unknown04 = -1;
}

void PadRelay::update() {
  PadResEventManager *manager = PadResEventManager::get();
  if (manager != nullptr) {
    const PadResEvent *event = manager->unknown08[unknown04].get();
    if (event != nullptr) {
      updateAction(*event);
      updateAxis(*event);
    }
  }
}

void PadRelay::updateAction(const PadResEvent &event) {
  for (u32 i = 0; i < event.unknown20; i++) {
    const ResActionInfo &info = event.unknown18[i];
    for (u32 j = 0; j < info.unknown10; j++) {
      if (checkAction(info.unknown08[j])) {
        invokeAction(info);
        break;
      }
    }
  }
}

void PadRelay::updateAxis(const PadResEvent &event) {
  for (u32 i = 0; i < event.unknown30; i++) {
    invokeAxis(event.unknown28[i]);
  }
}

void PadRelay::invokeAction(const ResActionInfo &info) {
  mm::mtl::FixStr<32> key(info.unknown00);
  mm::mtl::Map<mm::mtl::FixStr<32>, mm::mtl::Delegate<void()>>::iterator it = unknown08.find(key);
  if (it != unknown08.end() && it->second.isValid()) {
    it->second();
  }
}

void PadRelay::invokeAxis(const ResAxisInfo &info) {
  mm::mtl::FixStr<32> key(info.unknown00);
  mm::mtl::Map<mm::mtl::FixStr<32>, mm::mtl::Delegate<void(float)>>::iterator it = unknown20.find(key);
  if (it != unknown20.end() && it->second.isValid()) {
    const PadData &pad = *PadManager::getControlPadData(unknown00);
    f32 value;
    switch (info.unknown08) {
    case 0:
      value = pad.unknown1c;
      break;
    case 1:
      value = pad.unknown20;
      break;
    case 2:
      value = pad.unknown24;
      break;
    case 3:
      value = pad.unknown28;
      break;
    default:
      value = 0.0f;
      break;
    }
    it->second(value * info.unknown0c);
  }
}

} // namespace fw
