#include "mm_thread/mm_thread_csection.h"

#include "mm/mm_std_base.h"
#include "mm_thread/mm_thread_util.h"
#include "nn/time_span.h"

namespace mm {
namespace threading {

ReadWriteLock::ReadWriteLock() { nn::os::InitializeReaderWriterLock(&lock); }

ReadWriteLock::~ReadWriteLock() { nn::os::FinalizeReaderWriterLock(&lock); }

void ReadWriteLock::enterReader() { nn::os::AcquireReadLock(&lock); }

void ReadWriteLock::leaveReader() { nn::os::ReleaseReadLock(&lock); }

void ReadWriteLock::enterWriter() { nn::os::AcquireWriteLock(&lock); }

void ReadWriteLock::leaveWriter() { nn::os::ReleaseWriteLock(&lock); }

bool ReadWriteLock::isLockedReader() const { return nn::os::IsReadLockHeld(&lock); }

bool ReadWriteLock::isLockedWriter() const { return nn::os::IsWriteLockHeldByCurrentThread(&lock); }

CriticalSection::CriticalSection() {
  enabled = true;
  nn::os::InitializeMutex(&mutex, true, 31);
}

CriticalSection::~CriticalSection() { nn::os::FinalizeMutex(&mutex); }

void CriticalSection::setCostIgnore(bool costIgnore) {}

bool CriticalSection::isLocked() const { return nn::os::IsMutexLockedByCurrentThread(&mutex); }

void CriticalSection::enter(const CriticalSection &sect) {
  if (sect.enabled) {
    nn::os::LockMutex(const_cast<nn::os::MutexType *>(&sect.mutex));
  }
}

bool CriticalSection::enterTry(const CriticalSection &sect) {
  if (sect.enabled) {
    return nn::os::TryLockMutex(const_cast<nn::os::MutexType *>(&sect.mutex));
  }

  return false;
}

void CriticalSection::leave(const CriticalSection &sect) {
  if (sect.enabled) {
    nn::os::UnlockMutex(const_cast<nn::os::MutexType *>(&sect.mutex));
  }
}

CriticalSectionTC::CriticalSectionTC() {
  enabled = true;
  nn::os::InitializeMutex(&mutex, true, 31);
}

CriticalSectionTC::~CriticalSectionTC() { nn::os::FinalizeMutex(&mutex); }

void CriticalSectionTC::enter(const CriticalSectionTC &sect) {
  if (sect.enabled) {
    nn::os::LockMutex(const_cast<nn::os::MutexType *>(&sect.mutex));
  }
}

bool CriticalSectionTC::enterTry(const CriticalSectionTC &sect) {
  if (sect.enabled) {
    return nn::os::TryLockMutex(const_cast<nn::os::MutexType *>(&sect.mutex));
  }

  return false;
}

void CriticalSectionTC::leave(const CriticalSectionTC &sect) {
  if (sect.enabled) {
    nn::os::UnlockMutex(const_cast<nn::os::MutexType *>(&sect.mutex));
  }
}

CriticalSectionNC::CriticalSectionNC() : m_count(0), m_thid(0), enabled(true) {}

CriticalSectionNC::~CriticalSectionNC() {}

void CriticalSectionNC::setCostIgnore(bool costIgnore) {}

namespace detail {

f32 getNowSec() { return nn::os::ConvertToTimeSpan(nn::os::GetSystemTick()).GetNanoSeconds() / 1000000000.0f; }

} // namespace detail

void CriticalSectionNC::enter(const CriticalSectionNC &sect) {
  if (!sect.enabled) {
    return;
  }

  u64 thid = ThreadUtil::getCurrentID();
  if (thid == 0) {
    return;
  }

  CriticalSectionNC *self = const_cast<CriticalSectionNC *>(&sect);
  if (self->m_thid == thid) {
    __atomic_fetch_add(&self->m_count, 1, __ATOMIC_SEQ_CST);
    MM_ASSERT(const_cast<CriticalSectionNC *>(&sect)->m_thid == thid);
    return;
  }

  f32 startTime = detail::getNowSec();
  f32 yieldTime = startTime;
  for (;;) {
    s32 expected = 0;
    if (__atomic_compare_exchange_n(&self->m_count, &expected, 1, true, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
      break;
    }

    f32 now = detail::getNowSec();
    if (now - startTime > 15.0f) {
      nn::os::YieldThread();
      break;
    }

    if (now - yieldTime > 0.00001f) {
      nn::os::YieldThread();
      yieldTime = now;
    }
  }

  self->m_thid = thid;
}

bool CriticalSectionNC::enterTry(const CriticalSectionNC &sect) {
  if (!sect.enabled) {
    return false;
  }

  u64 thid = ThreadUtil::getCurrentID();
  if (thid == 0) {
    return false;
  }

  CriticalSectionNC *self = const_cast<CriticalSectionNC *>(&sect);
  if (self->m_thid == thid) {
    __atomic_fetch_add(&self->m_count, 1, __ATOMIC_SEQ_CST);
    MM_ASSERT(const_cast<CriticalSectionNC *>(&sect)->m_thid == thid);
    return true;
  }

  s32 expected = 0;
  if (!__atomic_compare_exchange_n(&self->m_count, &expected, 1, true, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
    return false;
  }

  self->m_thid = thid;
  return true;
}

void CriticalSectionNC::leave(const CriticalSectionNC &sect) {
  if (!sect.enabled) {
    return;
  }

  CriticalSectionNC *self = const_cast<CriticalSectionNC *>(&sect);
  s32 count = __atomic_load_n(&self->m_count, __ATOMIC_SEQ_CST);
  if (count == 1) {
    self->m_thid = 0;
  } else if (count < 1) {
    return;
  }

  __atomic_fetch_sub(&self->m_count, 1, __ATOMIC_SEQ_CST);
}

CS::CS(const CriticalSection &sect) {
  CriticalSection::enter(sect);
  this->sect = &sect;
}

CS::~CS() { CriticalSection::leave(*sect); }

CSTRY::CSTRY(const CriticalSection &sect) {
  locked = CriticalSection::enterTry(sect);
  this->sect = &sect;
}

CSTRY::~CSTRY() {
  if (locked) {
    CriticalSection::leave(*sect);
  }
}

CSTC::CSTC(const CriticalSectionTC &sect) {
  CriticalSectionTC::enter(sect);
  this->sect = &sect;
}

CSTC::~CSTC() { CriticalSectionTC::leave(*sect); }

CSTCTRY::CSTCTRY(const CriticalSectionTC &sect) {
  locked = CriticalSectionTC::enterTry(sect);
  this->sect = &sect;
}

CSTCTRY::~CSTCTRY() {
  if (locked) {
    CriticalSectionTC::leave(*sect);
  }
}

CSNC::CSNC(const CriticalSectionNC &sect) {
  CriticalSectionNC::enter(sect);
  this->sect = &sect;
}

CSNC::~CSNC() { CriticalSectionNC::leave(*sect); }

CSNCTRY::CSNCTRY(const CriticalSectionNC &sect) {
  locked = CriticalSectionNC::enterTry(sect);
  this->sect = &sect;
}

CSNCTRY::~CSNCTRY() {
  if (locked) {
    CriticalSectionNC::leave(*sect);
  }
}

ReadLockGuard::ReadLockGuard(const ReadWriteLock &lock) : lock(&lock) { const_cast<ReadWriteLock &>(lock).enterReader(); }

ReadLockGuard::~ReadLockGuard() { const_cast<ReadWriteLock *>(lock)->leaveReader(); }

WriteLockGuard::WriteLockGuard(const ReadWriteLock &lock) : lock(&lock) { const_cast<ReadWriteLock &>(lock).enterWriter(); }

WriteLockGuard::~WriteLockGuard() { const_cast<ReadWriteLock *>(lock)->leaveWriter(); }

} // namespace threading
} // namespace mm
