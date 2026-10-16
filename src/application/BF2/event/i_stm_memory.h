#pragma once
#include "types.h"
#include <stddef.h>

namespace mm {
template <typename T> struct Rect;
} // namespace mm

namespace event {

class IStmMemory {
public:
  virtual ~IStmMemory() {}
  virtual void update() = 0;
  virtual void render(const mm::Rect<int> &rect, f32 frame) = 0;
  virtual void tail() {}
  virtual void *adr(const char *path, size_t *size) = 0;
  virtual void free(void *adr, int frame) = 0;
  virtual bool isLoadingPrio(f32 prio) const = 0;
  virtual bool isFailure() const = 0;
};

} // namespace event
