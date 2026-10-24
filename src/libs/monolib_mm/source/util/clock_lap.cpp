#include "ml/clock_lap.h"

#include "ml/dev_clock.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

ClockLap::~ClockLap() {
  if (m_buffer != nullptr) {
    mtl::MemManager::deallocate(m_buffer, 0, false);
    m_buffer = nullptr;
  }
}

void ClockLap::setup(mtl::ALLOC_HANDLE handle, u32 lapMax) {
  m_buffer = mtl::MemManager::allocate(handle, lapMax * (sizeof(s64) * 2 + sizeof(u32)), 8, false, "no name", 0);
  unknown10 = static_cast<s64 *>(m_buffer);
  unknown18 = unknown10 + lapMax;
  unknown28 = lapMax;
  unknown20 = reinterpret_cast<u32 *>(unknown18 + lapMax);
  unknown10[0] = 0;
  unknown18[0] = 0;
}

void ClockLap::begin() {
  DevClock::getClockNow(unknown08);
  unknown2c = 0;
  unknown10[0] = 0;
  unknown18[unknown2c] = 0;
}

bool ClockLap::lapS(u32 color) {
  if (unknown2c >= unknown28) {
    return false;
  }
  DevClock::getClockNow(unknown10[unknown2c]);
  unknown18[unknown2c] = unknown10[unknown2c];
  unknown20[unknown2c] = color;
  return true;
}

void ClockLap::lapE() {
  if (unknown10[unknown2c] == 0) {
    return;
  }
  DevClock::getClockNow(unknown18[unknown2c]);
  unknown2c++;
  unknown10[unknown2c] = 0;
  unknown18[unknown2c] = 0;
}

const s64 &ClockLap::getLapS(u32 index) const { return unknown10[index]; }

const s64 &ClockLap::getLapE(u32 index) const { return unknown18[index]; }

u32 ClockLap::getLapCol(u32 index) const { return unknown20[index]; }

} // namespace ml
