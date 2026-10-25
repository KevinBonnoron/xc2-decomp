#pragma once
#include "types.h"

namespace ui {

class UIBuildInfo {
public:
  struct ObjectData {
    u8 unknown00[0xc0]; // Inferred role: object build data; original member names unknown.
  };

  virtual ~UIBuildInfo() {}
  virtual void update();
  virtual bool isReady() const;
  virtual bool isValid() const;
};

static_assert(sizeof(UIBuildInfo::ObjectData) == 0xc0, "");

} // namespace ui
