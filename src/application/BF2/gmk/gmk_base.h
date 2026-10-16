#pragma once
#include "gmk/gmk_manager.h"
#include "types.h"
#include <stddef.h>

namespace gmk {

struct GmkInfo {
  u16 id;
};

class AGmkBase {
public:
  virtual ~AGmkBase();
  virtual GmkType getGmkType() const = 0;
  virtual bool isValid() const;

  u8 _08[0x30 - 0x08];
  const GmkInfo *info;
};

static_assert(offsetof(AGmkBase, info) == 0x30, "");

} // namespace gmk
