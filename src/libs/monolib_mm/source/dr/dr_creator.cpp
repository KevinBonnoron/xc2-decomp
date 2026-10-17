#include "dr/dr_creator.h"

#include "dr/dr_env_coli_man.h"
#include "dr/dr_environment_man.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"

namespace ml {

DrCreator::DrCreator() : m_drMan(DrMan::s_pTop) {}

DrMdlObj *DrCreator::createMdl(const void *data, const char *name, int index) { return m_drMan->mdlMan->createMdl(data, name, index); }

DrMdlObj *DrCreator::createInstantMdl(const void *data, const char *name, int index) { return m_drMan->mdlMan->createInstantMdl(data, name, index); }

DrMdoGrpObj *DrCreator::createGrp(int num, u32 flags) { return m_drMan->mdlMan->createGrp(num, flags); }

DrMdoGrpObj *DrCreator::createInstantGrp(int num, u32 flags) { return m_drMan->mdlMan->createInstantGrp(num, flags); }

DrEnvironmentObj *DrCreator::createLgt(const void *data, int screen) { return m_drMan->environmentMans[screen]->createObj(data); }

DrEnvColiObj *DrCreator::createEnvColi(const void *data, int screen) { return m_drMan->environmentMans[screen]->m_envColiMan->createObj(data); }

DrGpuCheckBase *DrCreator::createGpuCheckObj(int type) { return m_drMan->mdlMan->createGpuCheckObj(type); }

DrGpuCheckBase *DrCreator::createEffGpuCheckObj(int type) { return m_drMan->mdlMan->createEffGpuCheckObj(type); }

DrStmReadObj *DrCreator::createStmLoadObj(const char *path) { return m_drMan->mdlMan->createStmLoadObj(path); }

DrStmReadObj *DrCreator::createStmSizeObj(u32 size) { return m_drMan->mdlMan->createStmSizeObj(size); }

} // namespace ml
