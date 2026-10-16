#pragma once
#include <stddef.h>

namespace event {

class IResPackEvent {
public:
  struct PARAM {
    const char *path;
    void *adr;
    size_t size;
  };

  virtual void OnPackEvent(const PARAM &param) = 0;
};

} // namespace event
