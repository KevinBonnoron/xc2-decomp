#pragma once
#include <stddef.h>

#include "gmk/gmk_acc.h"
#include "types.h"

namespace gmk {
class AGmkBase;
} // namespace gmk

namespace gf {

class GfGmkLocator {
public:
  struct CreateInfo {
    gmk::AGmkBase *unknown00; // Inferred role: gimmick; original member name unknown.
    bool unknown08;           // Inferred role: follow the gimmick through an accessor; original member name unknown.
  };

  explicit GfGmkLocator(const CreateInfo *info);
  ~GfGmkLocator() { dispose(); }
  void create(const CreateInfo &info);
  void dispose();
  const gmk::AGmkBase *getBindedGmk() const;
  u32 getFsId() const;

  gmk::AGmkBase *unknown00; // Inferred role: gimmick; original member name unknown.
  bool unknown08;           // Inferred role: follow the gimmick through an accessor; original member name unknown.
  gmk::GmkAcc unknown10;    // Inferred role: gimmick accessor; original member name unknown.
};

static_assert(offsetof(GfGmkLocator, unknown08) == 0x08, "");
static_assert(offsetof(GfGmkLocator, unknown10) == 0x10, "");
static_assert(sizeof(GfGmkLocator) == 0x50, "");

} // namespace gf
