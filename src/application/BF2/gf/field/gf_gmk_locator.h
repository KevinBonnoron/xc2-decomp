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
    CreateInfo() : unknown00(nullptr), unknown08(false) {}

    gmk::AGmkBase *unknown00; // Inferred role: gimmick; original member name unknown.
    bool unknown08;           // Inferred role: follow the gimmick through an accessor; original member name unknown.
  };

  explicit GfGmkLocator(const CreateInfo *info);
  ~GfGmkLocator() { dispose(); }
  void create(const CreateInfo &info);
  void dispose();
  const gmk::AGmkBase *getBindedGmk() const;
  u32 getFsId() const;

  // Layout evidence: the element copies of Vector<GfGmkLocator>::push_back (0x71002e0b18) and expand copy the
  // 8 bytes at 0x08 as a whole, the padding of a CreateInfo.
  CreateInfo m_createInfo; // Inferred role: creation parameters; original member name unknown.
  gmk::GmkAcc m_gmkAcc;    // Inferred role: gimmick accessor; original member name unknown.
};

static_assert(offsetof(GfGmkLocator, m_gmkAcc) == 0x10, "");
static_assert(sizeof(GfGmkLocator) == 0x50, "");

} // namespace gf
