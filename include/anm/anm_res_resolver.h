#pragma once
#include "types.h"

namespace anm {

class Binding;
class MirrorMapper;
class Skeleton;
class SimpleMapper;

class ResResolver {
public:
  virtual const Binding *importBinding(const char *name, u32 id) const = 0;
  virtual void restoreBinding(const char *name, u32 id) const = 0;
  virtual const Skeleton *getSkekelton() const = 0;
  virtual const MirrorMapper *getMirrorMapper() const = 0;
  virtual const SimpleMapper *getSimpleMapper() const = 0;
};

} // namespace anm
