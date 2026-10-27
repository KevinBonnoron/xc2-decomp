#pragma once
#include "types.h"

namespace anm {

class Binding;
class MirrorMapper;
class Skeleton;
class SimpleMapper;

class ResResolver {
public:
  virtual const Binding *unknown00(const char *name, u32 id) const = 0;
  virtual void unknown08(const char *name, u32 id) const = 0;
  virtual const Skeleton *unknown10() const = 0;
  virtual const MirrorMapper *unknown18() const = 0;
  virtual const SimpleMapper *unknown20() const = 0;
};

} // namespace anm
