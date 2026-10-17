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
  m_lapStarts = static_cast<s64 *>(m_buffer);
  m_lapEnds = m_lapStarts + lapMax;
  m_lapMax = lapMax;
  m_lapColors = reinterpret_cast<u32 *>(m_lapEnds + lapMax);
  m_lapStarts[0] = 0;
  m_lapEnds[0] = 0;
}

void ClockLap::begin() {
  DevClock::getClockNow(m_beginClock);
  m_lapIndex = 0;
  m_lapStarts[0] = 0;
  m_lapEnds[m_lapIndex] = 0;
}

bool ClockLap::lapS(u32 color) {
  if (m_lapIndex >= m_lapMax) {
    return false;
  }
  DevClock::getClockNow(m_lapStarts[m_lapIndex]);
  m_lapEnds[m_lapIndex] = m_lapStarts[m_lapIndex];
  m_lapColors[m_lapIndex] = color;
  return true;
}

void ClockLap::lapE() {
  if (m_lapStarts[m_lapIndex] == 0) {
    return;
  }
  DevClock::getClockNow(m_lapEnds[m_lapIndex]);
  m_lapIndex++;
  m_lapStarts[m_lapIndex] = 0;
  m_lapEnds[m_lapIndex] = 0;
}

const s64 &ClockLap::getLapS(u32 index) const { return m_lapStarts[index]; }

const s64 &ClockLap::getLapE(u32 index) const { return m_lapEnds[index]; }

u32 ClockLap::getLapCol(u32 index) const { return m_lapColors[index]; }

} // namespace ml
