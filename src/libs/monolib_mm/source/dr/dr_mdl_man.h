#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrGpuCheckBase;
class DrMdlObj;
class DrMdoGrpObj;
class DrStmReadObj;

class DrMdlMan {
public:
  void renderBegin();
  void setGroupsDisp(s32 group, bool disp);
  static void getTextureStreamInfo(u32 &size, u32 &count, const void *data, bool isMiddle);
  DrMdlObj *createMdl(const void *data, const char *name, int index);
  DrMdlObj *createInstantMdl(const void *data, const char *name, int index);
  DrMdoGrpObj *createGrp(int num, u32 flags);
  DrMdoGrpObj *createInstantGrp(int num, u32 flags);
  DrGpuCheckBase *createGpuCheckObj(int type);
  DrGpuCheckBase *createEffGpuCheckObj(int type);
  DrStmReadObj *createStmLoadObj(const char *path);
  DrStmReadObj *createStmSizeObj(u32 size);

  u8 _000[0x23c - 0x000];
  u32 m_groupsDisp;
};

static_assert(offsetof(DrMdlMan, m_groupsDisp) == 0x23c, "");

} // namespace ml
