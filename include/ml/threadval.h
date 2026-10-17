#pragma once
#include <string.h>

#include "ml/work_cpu.h"
#include "types.h"

namespace ml {

class IThreadValue {
public:
  virtual ~IThreadValue() {}
  virtual void tvSwap() = 0;
  virtual u8 getCpuBank() const = 0;
  virtual void setCpuBank(u8 bank) = 0;
};

template <typename T> class threadval : public IThreadValue {
public:
  enum Flag {
    FLAG_SYNC = 1 << 0,
  };

  struct Flags {
    bool test(u16 flag) const { return m_bits & flag; }
    void set(u16 flag) { m_bits |= flag; }

    u16 m_bits;
  };

  threadval() : m_flags(), m_bank(0), m_cpuBank(0) {
    m_front = &m_buffers[0];
    m_back = &m_buffers[1];
    WorkCpu::entrySwap(this);
  }

  ~threadval() override { WorkCpu::removeSwap(this); }

  void tvSwap() override {
    if (m_flags.test(FLAG_SYNC)) {
      memcpy(m_front, m_back, sizeof(T));
    }
    m_bank = 1 - m_bank;
    m_front = &m_buffers[m_bank];
    m_back = &m_buffers[1 - m_bank];
  }

  u8 getCpuBank() const override { return m_cpuBank; }
  void setCpuBank(u8 bank) override { m_cpuBank = bank; }

  T *m_front;
  T *m_back;
  T m_buffers[2];
  Flags m_flags;
  u8 m_bank;
  u8 m_cpuBank;
};

} // namespace ml
