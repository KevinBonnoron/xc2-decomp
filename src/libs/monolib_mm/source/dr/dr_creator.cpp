#include "dr/dr_creator.h"

#include "dr/dr_env_coli_man.h"
#include "dr/dr_environment_man.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"

namespace ml {

DrCreator::DrCreator() : unknown00(DrMan::s_pTop) {}

DrMdlObj *DrCreator::createMdl(const void *data, const char *name, int index) { return unknown00->unknown88->createMdl(data, name, index); }

DrMdlObj *DrCreator::createInstantMdl(const void *data, const char *name, int index) { return unknown00->unknown88->createInstantMdl(data, name, index); }

DrMdoGrpObj *DrCreator::createGrp(int num, u32 flags) { return unknown00->unknown88->createGrp(num, flags); }

DrMdoGrpObj *DrCreator::createInstantGrp(int num, u32 flags) { return unknown00->unknown88->createInstantGrp(num, flags); }

DrEnvironmentObj *DrCreator::createLgt(const void *data, int screen) { return unknown00->unknown100[screen]->createObj(data); }

DrEnvColiObj *DrCreator::createEnvColi(const void *data, int screen) { return unknown00->unknown100[screen]->unknown18->createObj(data); }

DrGpuCheckBase *DrCreator::createGpuCheckObj(int type) { return unknown00->unknown88->createGpuCheckObj(type); }

DrGpuCheckBase *DrCreator::createEffGpuCheckObj(int type) { return unknown00->unknown88->createEffGpuCheckObj(type); }

DrStmReadObj *DrCreator::createStmLoadObj(const char *path) { return unknown00->unknown88->createStmLoadObj(path); }

DrStmReadObj *DrCreator::createStmSizeObj(u32 size) { return unknown00->unknown88->createStmSizeObj(size); }

} // namespace ml
