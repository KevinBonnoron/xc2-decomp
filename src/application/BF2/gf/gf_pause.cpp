#include "gf/gf_pause.h"

#include "gf/event/gf_event.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "ml/fixed_size_alloc.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep

namespace gf {

GfPause::GfPause(const GfSetupParam &param) : unknowne58(0), unknowne5c(0), unknowne60(0) { initialize(param); }

void GfPause::initialize(const GfSetupParam &) { unknowne64 = true; }

GfPause::~GfPause() {}

void GfPause::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfPause(param); }

void GfPause::destroy() {
  GfPause *pause = get();
  pause->finalize();
  delete pause;
}

void GfPause::finalize() {
  while (unknown138.size() > 0) {
    GfSleep(1);
  }
  unknowne58 = 0;
  unknowne64 = false;
}

bool GfPause::isInitialized() {
  GfPause *pause = get();
  if (pause != nullptr) {
    return pause->unknowne64;
  }
  return false;
}

GF_PAUSE_HANDLE *GfPause::createPauseHandle(u32 pauseBits) {
  GfPause *pause = get();
  u32 index = 0;
  u32 *bits = pause->unknown08.unknown003(&index);
  *bits = pauseBits;
  return reinterpret_cast<GF_PAUSE_HANDLE *>(pause->createPauseHandleByIndex(index));
}

u64 GfPause::createPauseHandleByIndex(u32 index) {
  u32 serial = unknowne60;
  unknowne60 = serial + 1;
  if (serial >= 0x3ffffff) {
    serial++;
    unknowne60 = serial + 1;
  }
  return (index & 0x3f) | (serial << 6);
}

void GfPause::destroyPauseHandle(GF_PAUSE_HANDLE *handle) {
  unknown08.unknown011(reinterpret_cast<u64>(handle) & 0x3f);
  mm::mtl::FixedList<GF_PAUSE_HANDLE *, 64>::iterator it = mm::mtl::find(unknown138.begin(), unknown138.end(), handle);
  if (it != unknown138.end()) {
    unknown138.erase(it);
  }
}

GF_PAUSE_HANDLE *GfPause::reqPause(u32 pauseBits) {
  GfPause *pause = get();
  GF_PAUSE_HANDLE *handle = createPauseHandle(pauseBits);
  pause->unknown598.push_back(handle);
  pause->unknowne58 = pause->getPauseBit();
  return handle;
}

u32 GfPause::getPauseBit() const {
  u32 pauseBits = 0;
  for (mm::mtl::FixedList<GF_PAUSE_HANDLE *, 64>::const_iterator it = unknown138.begin(); it != unknown138.end(); ++it) {
    pauseBits |= unknown08.unknown007[reinterpret_cast<u64>(*it) & 0x3f];
  }
  for (mm::mtl::FixedList<GF_PAUSE_HANDLE *, 64>::const_iterator it = unknown598.begin(); it != unknown598.end(); ++it) {
    pauseBits |= unknown08.unknown007[reinterpret_cast<u64>(*it) & 0x3f];
  }
  return pauseBits;
}

void GfPause::destroyHandle(GF_PAUSE_HANDLE *handle) {
  if (handle != reinterpret_cast<GF_PAUSE_HANDLE *>(-1)) {
    get()->unknown9f8.push_back(handle);
  }
}

void GfPause::update() {
  GfPause *pause = get();
  u32 oldPauseBits = pause->unknowne5c;
  if (pause->unknown9f8.size() != 0 || pause->unknown598.size() != 0) {
    for (mm::mtl::FixedList<GF_PAUSE_HANDLE *, 64>::iterator it = pause->unknown9f8.begin(); it != pause->unknown9f8.end(); ++it) {
      pause->destroyPauseHandle(*it);
    }
    if (pause->unknown9f8.size() > 0) {
      pause->unknown9f8.clear();
    }
    for (mm::mtl::FixedList<GF_PAUSE_HANDLE *, 64>::iterator it = pause->unknown598.begin(); it != pause->unknown598.end(); ++it) {
      pause->unknown138.push_back(*it);
    }
    if (pause->unknown598.size() > 0) {
      pause->unknown598.clear();
    }
    pause->unknowne58 = pause->getPauseBit();
    u32 changedBits = pause->unknowne58 ^ oldPauseBits;
    u32 pauseBits = changedBits & pause->unknowne58;
    u32 resumeBits = changedBits & oldPauseBits;
    GfEvent::unknown001(resumeBits, pauseBits);
    pause->unknowne5c = pause->unknowne58;
  }
}

bool GfPause::isPause(u32 pauseBits) { return (get()->unknowne58 & pauseBits) == pauseBits; }

} // namespace gf

template mm::mtl::FixedList<gf::GF_PAUSE_HANDLE *, 64>::iterator mm::mtl::FixedList<gf::GF_PAUSE_HANDLE *, 64>::erase(mm::mtl::FixedList<gf::GF_PAUSE_HANDLE *, 64>::iterator);

template mm::mtl::PtrSingleton<gf::GfPause>::~PtrSingleton();
