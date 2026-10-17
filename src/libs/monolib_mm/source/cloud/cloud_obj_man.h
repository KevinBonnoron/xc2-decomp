#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class IDrDrawWorkInfo;
} // namespace ml

namespace cloud {

class CloudCalcParams;

class CloudObjMan {
public:
  CloudObjMan();
  ~CloudObjMan();
  void creataFastSetup();
  bool update(const ml::IDrDrawWorkInfo *workInfo);
  bool isRender() const;
  void alphaRender(const ml::IDrDrawWorkInfo *workInfo);

  u8 _00[0x38 - 0x00];
  CloudCalcParams *m_calcParams;
  u8 _40[0x58 - 0x40];
  bool m_isDisp;
  bool m_isPlane;
  bool m_isPlaneSide;
  u8 _5b;
  bool m_isSky;
  u8 _5d[0x61 - 0x5d];
  bool m_isMdl;
  u8 _62[0x66 - 0x62];
  bool m_isHole;
  u8 _67[0x70 - 0x67];
};

static_assert(offsetof(CloudObjMan, m_calcParams) == 0x38, "");
static_assert(offsetof(CloudObjMan, m_isDisp) == 0x58, "");
static_assert(offsetof(CloudObjMan, m_isSky) == 0x5c, "");
static_assert(offsetof(CloudObjMan, m_isMdl) == 0x61, "");
static_assert(offsetof(CloudObjMan, m_isHole) == 0x66, "");
static_assert(sizeof(CloudObjMan) == 0x70, "");

} // namespace cloud
