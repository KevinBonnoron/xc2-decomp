#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

struct DrResMdoDecShd {
  const u32 *nameOffset;
  u8 _08[0x18 - 0x08];
};

static_assert(sizeof(DrResMdoDecShd) == 0x18, "");

class DrResMdoShdObj {
public:
  u32 getDecShdID(u32 index) const;
  int getDecShdIdx(const char *name) const;
  int getDecShdIdx(u32 id) const;
  void setDecShdParm(u32 index, u32 parm);
  u32 getDecShdParm(u32 index) const;
  u32 getDecShdParmMax(u32 index) const;

  const char *m_names;
  const DrResMdoDecShd *m_decShds;
  u32 m_decShdMax;
};

static_assert(offsetof(DrResMdoShdObj, m_decShds) == 0x08, "");
static_assert(offsetof(DrResMdoShdObj, m_decShdMax) == 0x10, "");

} // namespace ml
