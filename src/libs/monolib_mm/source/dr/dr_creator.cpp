#include "dr/dr_creator.h"

#include "dr/dr_calc_clip_man.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_env_coli_man.h"
#include "dr/dr_environment_man.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"
#include "mm_mtl/fixed_array.h"

namespace ml {

DrCreator::DrCreator() : m_drMan(DrMan::s_pTop) {}

DrMdlObj *DrCreator::createMdl(const void *data, const char *name, int index) { return m_drMan->m_drMdlMan->createMdl(data, name, index); }

DrMdlObj *DrCreator::createInstantMdl(const void *data, const char *name, int index) { return m_drMan->m_drMdlMan->createInstantMdl(data, name, index); }

DrMdoGrpObj *DrCreator::createGrp(int num, u32 flags) { return m_drMan->m_drMdlMan->createGrp(num, flags); }

DrMdoGrpObj *DrCreator::createInstantGrp(int num, u32 flags) { return m_drMan->m_drMdlMan->createInstantGrp(num, flags); }

DrEnvironmentObj *DrCreator::createLgt(const void *data, int screen) { return m_drMan->unknown100[screen]->createObj(data); }

DrEnvColiObj *DrCreator::createEnvColi(const void *data, int screen) { return m_drMan->unknown100[screen]->m_drEnvColiMan->createObj(data); }

DrCalcClipObj *DrCreator::createClipObj(const void *data, int screen) { return m_drMan->unknowna0[screen]->m_drCalcClipMan->createClipObj(data); }

DrGpuCheckBase *DrCreator::createGpuCheckObj(int type) { return m_drMan->m_drMdlMan->createGpuCheckObj(type); }

DrGpuCheckBase *DrCreator::createEffGpuCheckObj(int type) { return m_drMan->m_drMdlMan->createEffGpuCheckObj(type); }

DrStmReadObj *DrCreator::createStmLoadObj(const char *path) { return m_drMan->m_drMdlMan->createStmLoadObj(path); }

DrStmReadObj *DrCreator::createStmSizeObj(u32 size) { return m_drMan->m_drMdlMan->createStmSizeObj(size); }

} // namespace ml
