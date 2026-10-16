#include "scn/scn_render_dr_env_coli.h"

#include "dr/dr_env_coli_man.h"
#include "dr/dr_environment_man.h"
#include "dr/dr_man.h"

namespace ml {

ScnRenderDrEnvColi::ScnRenderDrEnvColi(s32 index) { m_envColiMan = DrMan::getIns()->environmentMans[index]->m_envColiMan; }

ScnRenderDrEnvColi::~ScnRenderDrEnvColi() {}

bool ScnRenderDrEnvColi::testEnvColi(const mm::Vec3 &position, f32 radius) { return m_envColiMan->testEnvColi(nullptr, position, radius); }

s32 ScnRenderDrEnvColi::getBgmId() const { return m_envColiMan->m_result.bgmId; }

s32 ScnRenderDrEnvColi::getLayerId() const { return m_envColiMan->m_result.layerId; }

s32 ScnRenderDrEnvColi::getReverbId() const { return m_envColiMan->m_result.reverbId; }

s32 ScnRenderDrEnvColi::getCaveId() const { return m_envColiMan->m_result.caveId; }

s32 ScnRenderDrEnvColi::getAreaId() const { return m_envColiMan->m_result.areaId; }

s32 ScnRenderDrEnvColi::getWindId() const { return m_envColiMan->m_result.windId; }

bool ScnRenderDrEnvColi::isRoom() const { return m_envColiMan->m_result.isRoom; }

} // namespace ml
