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
  m_lapS = static_cast<s64 *>(m_buffer);
  m_lapE = m_lapS + lapMax;
  unknown28 = lapMax;
  m_lapCol = reinterpret_cast<u32 *>(m_lapE + lapMax);
  m_lapS[0] = 0;
  m_lapE[0] = 0;
}

void ClockLap::begin() {
  DevClock::getClockNow(unknown08);
  unknown2c = 0;
  m_lapS[0] = 0;
  m_lapE[unknown2c] = 0;
}

bool ClockLap::lapS(u32 color) {
  if (unknown2c >= unknown28) {
    return false;
  }
  DevClock::getClockNow(m_lapS[unknown2c]);
  m_lapE[unknown2c] = m_lapS[unknown2c];
  m_lapCol[unknown2c] = color;
  return true;
}

void ClockLap::lapE() {
  if (m_lapS[unknown2c] == 0) {
    return;
  }
  DevClock::getClockNow(m_lapE[unknown2c]);
  unknown2c++;
  m_lapS[unknown2c] = 0;
  m_lapE[unknown2c] = 0;
}

const s64 &ClockLap::getLapS(u32 index) const { return m_lapS[index]; }

const s64 &ClockLap::getLapE(u32 index) const { return m_lapE[index]; }

u32 ClockLap::getLapCol(u32 index) const { return m_lapCol[index]; }

} // namespace ml
