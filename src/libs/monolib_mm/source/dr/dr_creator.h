#pragma once
#include "types.h"

namespace ml {
class DrCalcClipObj;
class DrEnvColiObj;
class DrEnvironmentObj;
class DrGpuCheckBase;
class DrMan;
class DrMdlObj;
class DrMdoGrpObj;
class DrStmReadObj;

class DrCreator {
public:
  DrCreator();
  DrMdlObj *createMdl(const void *data, const char *name, int index);
  DrMdlObj *createInstantMdl(const void *data, const char *name, int index);
  DrMdoGrpObj *createGrp(int num, u32 flags);
  DrMdoGrpObj *createInstantGrp(int num, u32 flags);
  DrEnvironmentObj *createLgt(const void *data, int screen);
  DrEnvColiObj *createEnvColi(const void *data, int screen);
  DrCalcClipObj *createClipObj(const void *data, int screen);
  DrGpuCheckBase *createGpuCheckObj(int type);
  DrGpuCheckBase *createEffGpuCheckObj(int type);
  DrStmReadObj *createStmLoadObj(const char *path);
  DrStmReadObj *createStmSizeObj(u32 size);

private:
  DrMan *m_drMan;
};

static_assert(sizeof(DrCreator) == 0x08, "");

} // namespace ml
