#include "scn/scn_render_dr_env_coli.h"

#include "dr/dr_env_coli_man.h"
#include "dr/dr_environment_man.h"
#include "dr/dr_man.h"

namespace ml {

ScnRenderDrEnvColi::ScnRenderDrEnvColi(s32 index) { m_envColiMan = DrMan::getIns()->unknown100[index]->unknown18; }

ScnRenderDrEnvColi::~ScnRenderDrEnvColi() {}

bool ScnRenderDrEnvColi::testEnvColi(const mm::Vec3 &position, f32 radius) { return m_envColiMan->testEnvColi(nullptr, position, radius); }

s32 ScnRenderDrEnvColi::getBgmId() const { return m_envColiMan->unknown48.unknown00; }

s32 ScnRenderDrEnvColi::getLayerId() const { return m_envColiMan->unknown48.unknown04; }

s32 ScnRenderDrEnvColi::getReverbId() const { return m_envColiMan->unknown48.unknown08; }

s32 ScnRenderDrEnvColi::getCaveId() const { return m_envColiMan->unknown48.unknown0c; }

s32 ScnRenderDrEnvColi::getAreaId() const { return m_envColiMan->unknown48.unknown10; }

s32 ScnRenderDrEnvColi::getWindId() const { return m_envColiMan->unknown48.unknown18; }

bool ScnRenderDrEnvColi::isRoom() const { return m_envColiMan->unknown48.unknown1c_2; }

} // namespace ml
