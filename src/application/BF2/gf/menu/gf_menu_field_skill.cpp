#include "gf/menu/gf_menu_field_skill.h"

#include <new>

namespace gf {

ai::State *GfMenuFieldSkill::StateIdle::create(void *buffer) { return new (buffer) StateIdle; }

const char *GfMenuFieldSkill::StateIdle::getName() const { return "StateIdle"; }

void GfMenuFieldSkill::StateIdle::onEnter(void *owner, ai::State *previous) {}

void GfMenuFieldSkill::StateIdle::onLeave(void *owner, ai::State *next) {}

void GfMenuFieldSkill::StateIdle::onStep(void *owner, const void *param) {}

} // namespace gf
