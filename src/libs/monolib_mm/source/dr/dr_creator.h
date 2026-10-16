#pragma once
#include "types.h"

namespace ml {
class DrGpuCheckBase;
class DrStmReadObj;

class DrCreator {
public:
  DrCreator();
  DrGpuCheckBase *createGpuCheckObj(int type);
  DrStmReadObj *createStmLoadObj(const char *path);
  DrStmReadObj *createStmSizeObj(u32 size);

private:
  u8 _00[0x08 - 0x00];
};

} // namespace ml
