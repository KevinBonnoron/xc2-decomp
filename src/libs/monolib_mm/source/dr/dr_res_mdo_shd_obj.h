#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrShdMdoExtTblObj;

struct MdsDecShdInfo {
  u32 nameOfs;
  u32 id;
  u32 parmMax;
  u32 shaderIdxOfs;
  s32 shaderNum;
};

static_assert(sizeof(MdsDecShdInfo) == 0x14, "");

struct MdsDecShdHeader {
  s32 num;
  u32 infoOfs;
};

struct DrResMdoDecShd {
  const MdsDecShdInfo *info;
  u8 *declOfs;
  u32 parm;
  u32 prevParm;
};

static_assert(sizeof(DrResMdoDecShd) == 0x18, "");

class DrResMdoShdObj {
public:
  DrResMdoShdObj();
  ~DrResMdoShdObj();
  int setup(const u8 *resource, u8 *work);
  void bindShader(DrShdMdoExtTblObj *extTblObj);
  bool update(DrShdMdoExtTblObj *extTblObj);
  u32 getDecShdID(u32 index) const;
  int getDecShdIdx(const char *name) const;
  int getDecShdIdx(u32 id) const;
  void setDecShdParm(u32 index, u32 parm);
  u32 getDecShdParm(u32 index) const;
  u32 getDecShdParmMax(u32 index) const;
  static int calcWorkSize(const u8 *resource);
  static int create(u8 *work, const u8 *resource);
  static void release(DrResMdoShdObj *&shdObj);

  const MdsDecShdHeader *m_header;
  DrResMdoDecShd *m_decShds;
  u32 m_decShdMax;
};

static_assert(offsetof(DrResMdoShdObj, m_decShds) == 0x08, "");
static_assert(offsetof(DrResMdoShdObj, m_decShdMax) == 0x10, "");
static_assert(sizeof(DrResMdoShdObj) == 0x18, "");

} // namespace ml
