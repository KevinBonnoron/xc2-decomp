#pragma once
#include <stddef.h>

#include "nn/os.h"
#include "types.h"

namespace ml {

class CriticalSection {
public:
  CriticalSection();
  ~CriticalSection();
  void setCostIgnore(bool costIgnore);
  bool isLocked() const;
  static bool enterTry(const CriticalSection &sect);

  static void enter(const CriticalSection &sect) {
    if (sect.unknown20) {
      nn::os::LockMutex(const_cast<nn::os::MutexType *>(&sect.unknown00));
    }
  }

  static void leave(const CriticalSection &sect) {
    if (sect.unknown20) {
      nn::os::UnlockMutex(const_cast<nn::os::MutexType *>(&sect.unknown00));
    }
  }

  nn::os::MutexType unknown00; // Inferred role: mutex; original member name unknown.
  bool unknown20;              // Inferred role: enabled; original member name unknown.
};

static_assert(offsetof(CriticalSection, unknown20) == 0x20, "");

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
  static void leave(const CriticalSectionNC &sect);

  nn::os::MutexType unknown00; // Inferred role: mutex; original member name unknown.
  bool unknown20;              // Inferred role: enabled; original member name unknown.
};

static_assert(offsetof(CriticalSectionNC, unknown20) == 0x20, "");

namespace detail {

f32 getNowSec();

} // namespace detail

class CS {
public:
  CS(const CriticalSection &sect) {
    CriticalSection::enter(sect);
    this->sect = &sect;
  }

  ~CS() { CriticalSection::leave(*sect); }

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

} // namespace ml
