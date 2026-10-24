#include "ml/critical_section.h"

#include "nn/time_span.h"

namespace ml {

CriticalSection::CriticalSection() {
  unknown20 = true;
  nn::os::InitializeMutex(&unknown00, true, 0);
}

CriticalSection::~CriticalSection() { nn::os::FinalizeMutex(&unknown00); }

void CriticalSection::setCostIgnore(bool costIgnore) {}

bool CriticalSection::isLocked() const { return nn::os::IsMutexLockedByCurrentThread(&unknown00); }

bool CriticalSection::enterTry(const CriticalSection &sect) {
  if (sect.unknown20) {
    return nn::os::TryLockMutex(const_cast<nn::os::MutexType *>(&sect.unknown00));
  }

  return false;
}

CriticalSectionTC::CriticalSectionTC() {
  unknown20 = true;
  nn::os::InitializeMutex(&unknown00, true, 0);
}

CriticalSectionTC::~CriticalSectionTC() { nn::os::FinalizeMutex(&unknown00); }

void CriticalSectionTC::enter(const CriticalSectionTC &sect) {
  if (sect.unknown20) {
    nn::os::LockMutex(const_cast<nn::os::MutexType *>(&sect.unknown00));
  }
}

bool CriticalSectionTC::enterTry(const CriticalSectionTC &sect) {
  if (sect.unknown20) {
    return nn::os::TryLockMutex(const_cast<nn::os::MutexType *>(&sect.unknown00));
  }

  return false;
}

void CriticalSectionTC::leave(const CriticalSectionTC &sect) {
  if (sect.unknown20) {
    nn::os::UnlockMutex(const_cast<nn::os::MutexType *>(&sect.unknown00));
  }
}

CriticalSectionNC::CriticalSectionNC() {
  unknown20 = true;
  nn::os::InitializeMutex(&unknown00, true, 0);
}

CriticalSectionNC::~CriticalSectionNC() { nn::os::FinalizeMutex(&unknown00); }

void CriticalSectionNC::setCostIgnore(bool costIgnore) {}

namespace detail {

f32 getNowSec() { return nn::os::ConvertToTimeSpan(nn::os::GetSystemTick()).GetNanoSeconds() / 1000000000.0f; }

} // namespace detail

void CriticalSectionNC::enter(const CriticalSectionNC &sect) {
  if (sect.unknown20) {
    nn::os::LockMutex(const_cast<nn::os::MutexType *>(&sect.unknown00));
  }
}

void CriticalSectionNC::leave(const CriticalSectionNC &sect) {
  if (sect.unknown20) {
    nn::os::UnlockMutex(const_cast<nn::os::MutexType *>(&sect.unknown00));
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
