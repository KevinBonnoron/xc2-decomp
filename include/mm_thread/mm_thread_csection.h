#pragma once
#include <stddef.h>

#include "nn/os.h"
#include "types.h"

namespace mm {
namespace threading {

class ReadWriteLock {
public:
  ReadWriteLock();
  ~ReadWriteLock();
  void enterReader();
  void leaveReader();
  void enterWriter();
  void leaveWriter();
  bool isLockedReader() const;
  bool isLockedWriter() const;

  nn::os::ReaderWriterLockType lock;
};

class CriticalSection {
public:
  CriticalSection();
  ~CriticalSection();
  void setCostIgnore(bool costIgnore);
  bool isLocked() const;
  static void enter(const CriticalSection &sect);
  static bool enterTry(const CriticalSection &sect);
  static void leave(const CriticalSection &sect);

  nn::os::MutexType unknown00; // Inferred role: mutex; original member name unknown.
  bool unknown20;              // Inferred role: enabled; original member name unknown.
};

static_assert(offsetof(CriticalSection, unknown20) == 0x20, "");
static_assert(sizeof(CriticalSection) == 0x28, "");

class CriticalSectionTC {
public:
  CriticalSectionTC();
  ~CriticalSectionTC();
  static void enter(const CriticalSectionTC &sect);
  static bool enterTry(const CriticalSectionTC &sect);
  static void leave(const CriticalSectionTC &sect);

  nn::os::MutexType unknown00; // Inferred role: mutex; original member name unknown.
  bool unknown20;              // Inferred role: enabled; original member name unknown.
};

static_assert(offsetof(CriticalSectionTC, unknown20) == 0x20, "");

class CriticalSectionNC {
public:
  CriticalSectionNC();
  ~CriticalSectionNC();
  void setCostIgnore(bool costIgnore);
  static void enter(const CriticalSectionNC &sect);
  static bool enterTry(const CriticalSectionNC &sect);
  static void leave(const CriticalSectionNC &sect);

  s32 unknown00; // Inferred role: count; original member name unknown.
  u64 m_thid;
  bool unknown10; // Inferred role: enabled; original member name unknown.
};

static_assert(offsetof(CriticalSectionNC, m_thid) == 0x08, "");
static_assert(offsetof(CriticalSectionNC, unknown10) == 0x10, "");

namespace detail {

f32 getNowSec();

} // namespace detail

class CS {
public:
  CS(const CriticalSection &sect);
  ~CS();

  const CriticalSection *sect;
};

class CSTRY {
public:
  CSTRY(const CriticalSection &sect);
  ~CSTRY();

  const CriticalSection *sect;
  bool locked;
};

class CSTC {
public:
  CSTC(const CriticalSectionTC &sect);
  ~CSTC();

  const CriticalSectionTC *sect;
};

class CSTCTRY {
public:
  CSTCTRY(const CriticalSectionTC &sect);
  ~CSTCTRY();

  const CriticalSectionTC *sect;
  bool locked;
};

class CSNC {
public:
  CSNC(const CriticalSectionNC &sect);
  ~CSNC();

  const CriticalSectionNC *sect;
};

class CSNCTRY {
public:
  CSNCTRY(const CriticalSectionNC &sect);
  ~CSNCTRY();

  const CriticalSectionNC *sect;
  bool locked;
};

class ReadLockGuard {
public:
  ReadLockGuard(const ReadWriteLock &lock);
  ~ReadLockGuard();

  const ReadWriteLock *lock;
};

class WriteLockGuard {
public:
  WriteLockGuard(const ReadWriteLock &lock);
  ~WriteLockGuard();

  const ReadWriteLock *lock;
};

} // namespace threading
} // namespace mm
