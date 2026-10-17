#pragma once
#include "types.h"

namespace grlib {

class CGLibDisplayList {
public:
  CGLibDisplayList();
  ~CGLibDisplayList();
  void release();
  void beginDisplay(void *buffer, int size);
  u32 endDisplay(void *buffer);
  void callDisplayList();
};

class CGLibOneDisplayList {
public:
  CGLibOneDisplayList();
  ~CGLibOneDisplayList();
  void release();
  void beginDisplay(void *buffer, int size);
  void endDisplay();
  void callDisplayList();
};

} // namespace grlib
