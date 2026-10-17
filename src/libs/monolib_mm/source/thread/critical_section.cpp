#include "ml/critical_section.h"

#include "nn/time_span.h"

namespace ml {

CriticalSection::CriticalSection() {
  enabled = true;
  nn::os::InitializeMutex(&mutex, true, 0);
}

CriticalSection::~CriticalSection() { nn::os::FinalizeMutex(&mutex); }

void CriticalSection::setCostIgnore(bool costIgnore) {}

bool CriticalSection::isLocked() const { return nn::os::IsMutexLockedByCurrentThread(&mutex); }

bool CriticalSection::enterTry(const CriticalSection &sect) {
  if (sect.enabled) {
    return nn::os::TryLockMutex(const_cast<nn::os::MutexType *>(&sect.mutex));
  }

  return false;
}

CriticalSectionTC::CriticalSectionTC() {
  enabled = true;
  nn::os::InitializeMutex(&mutex, true, 0);
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

CriticalSectionNC::CriticalSectionNC() {
  enabled = true;
  nn::os::InitializeMutex(&mutex, true, 0);
}

CriticalSectionNC::~CriticalSectionNC() { nn::os::FinalizeMutex(&mutex); }

void CriticalSectionNC::setCostIgnore(bool costIgnore) {}

namespace detail {

f32 getNowSec() { return nn::os::ConvertToTimeSpan(nn::os::GetSystemTick()).GetNanoSeconds() / 1000000000.0f; }

} // namespace detail

void CriticalSectionNC::enter(const CriticalSectionNC &sect) {
  if (sect.enabled) {
    nn::os::LockMutex(const_cast<nn::os::MutexType *>(&sect.mutex));
  }
}

void CriticalSectionNC::leave(const CriticalSectionNC &sect) {
  if (sect.enabled) {
    nn::os::UnlockMutex(const_cast<nn::os::MutexType *>(&sect.mutex));
  }
}

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

} // namespace ml
