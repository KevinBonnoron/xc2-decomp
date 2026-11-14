#include "gf/menu/gf_menu_field_skill.h"

#include <new>

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/object/gf_menu_obj_field_skill.h"
#include "mm_mtl/reference_object.h"

namespace gf {

GfMenuFieldSkill::~GfMenuFieldSkill() { mm::mtl::safeRelease(unknown1f8); }

bool GfMenuFieldSkill::isDisp() { return true; }

bool GfMenuFieldSkill::isInitialized() { return true; }

void GfMenuFieldSkill::postUpdate(const fw::UpdateInfo &info) {
  GfMenuFieldSkill *skill = get();
  if (skill != nullptr) {
    GfMenuCallContext::GfMenuResult result;
    if (skill->unknown1f8 != nullptr && skill->unknown1f8->isActive() && !skill->unknown1f8->unknown18.empty() && (skill->unknown1f8->popResult(result), result.unknown04 == 2)) {
      skill->unknown218 = true;
    }
    skill->unknown08.update(&info);
  }
}

bool GfMenuFieldSkill::start(const StartParam &param) {
  GfMenuFieldSkill *skill = get();
  bool started = false;
  if (skill != nullptr) {
    if (!isRunning()) {
      if (param.unknown00 != 0 || !param.unknown08.empty()) {
        skill->unknown80 = param;
        skill->unknown218 = false;
        started = true;
        skill->unknown08.setState(1);
        GfMenuReference::setReferenceBladeID(5, 0);
      }
    }
  }
  return started;
}

bool GfMenuFieldSkill::isRunning() {
  GfMenuFieldSkill *skill = get();
  return skill != nullptr && skill->unknown08.getState()->unknown08 != 0;
}

int GfMenuFieldSkill::getTotalSkillIndex(GfMenuFieldSkill *skill, u16 id) {
  int index = 0;
  for (const StartParam::unknown001 *it = skill->unknown80.unknown120.begin(); it != skill->unknown80.unknown120.end(); it++) {
    if (it->unknown00 == id) {
      return index;
    }
    index++;
  }
  return -1;
}

ai::State *GfMenuFieldSkill::StateIdle::create(void *buffer) { return new (buffer) StateIdle; }

const char *GfMenuFieldSkill::StateIdle::getName() const { return "StateIdle"; }

void GfMenuFieldSkill::StateIdle::onEnter(void *owner, ai::State *previous) {}

void GfMenuFieldSkill::StateIdle::onLeave(void *owner, ai::State *next) {}

void GfMenuFieldSkill::StateIdle::onStep(void *owner, const void *param) {}

ai::State *GfMenuFieldSkill::StateStart::create(void *buffer) { return new (buffer) StateStart; }

const char *GfMenuFieldSkill::StateStart::getName() const { return "StateStart"; }

void GfMenuFieldSkill::StateStart::onEnter(void *owner, ai::State *previous) {
  GfMenuFieldSkill *skill = static_cast<GfMenuFieldSkill *>(owner);
  skill->unknown1f8->reset();
  GfMenuObjFieldSkill::attachSkip(skill->unknown1f8);
  skill->unknown1b8 = 0;
}

void GfMenuFieldSkill::StateStart::onLeave(void *owner, ai::State *next) {}

void GfMenuFieldSkill::StateStart::onStep(void *owner, const void *param) {
  switch (static_cast<GfMenuFieldSkill *>(owner)->unknown80.unknown00) {
  case 0:
    reqState(2);
    break;
  case 1:
    reqState(3);
    break;
  }
}

ai::State *GfMenuFieldSkill::StateWait::create(void *buffer) { return new (buffer) StateWait; }

const char *GfMenuFieldSkill::StateWait::getName() const { return "StateWait"; }

void GfMenuFieldSkill::StateWait::onEnter(void *owner, ai::State *previous) {}

void GfMenuFieldSkill::StateWait::onLeave(void *owner, ai::State *next) { static_cast<GfMenuFieldSkill *>(owner)->unknown210 = 0; }

void GfMenuFieldSkill::StateWait::onStep(void *owner, const void *param) {
  GfMenuFieldSkill *skill = static_cast<GfMenuFieldSkill *>(owner);
  if (skill->unknown210 == 0 || --skill->unknown210 == 0 || skill->unknown218) {
    int state = skill->unknown214;
    if (!skill->unknown218 || state == 5) {
      reqState(state);
    } else {
      reqState(7);
    }
  }
}

ai::State *GfMenuFieldSkill::StateSkip::create(void *buffer) { return new (buffer) StateSkip; }

const char *GfMenuFieldSkill::StateSkip::getName() const { return "StateSkip"; }

void GfMenuFieldSkill::StateSkip::onEnter(void *owner, ai::State *previous) { unknown18 = 0; }

void GfMenuFieldSkill::StateSkip::onLeave(void *owner, ai::State *next) {}

void GfMenuFieldSkill::StateSkip::onStep(void *owner, const void *param) { update(static_cast<GfMenuFieldSkill *>(owner), *static_cast<const fw::UpdateInfo *>(param)); }

ai::State *GfMenuFieldSkill::StateTotalNext::create(void *buffer) { return new (buffer) StateTotalNext; }

const char *GfMenuFieldSkill::StateTotalNext::getName() const { return "StateTotalNext"; }

void GfMenuFieldSkill::StateTotalNext::onEnter(void *owner, ai::State *previous) {}

void GfMenuFieldSkill::StateTotalNext::onLeave(void *owner, ai::State *next) {}

ai::State *GfMenuFieldSkill::StateQuit::create(void *buffer) { return new (buffer) StateQuit; }

const char *GfMenuFieldSkill::StateQuit::getName() const { return "StateQuit"; }

void GfMenuFieldSkill::StateQuit::onLeave(void *owner, ai::State *next) { mm::mtl::safeRelease(static_cast<GfMenuFieldSkill *>(owner)->unknown200); }

void GfMenuFieldSkill::StateQuit::onStep(void *owner, const void *param) {
  GfMenuFieldSkill *skill = static_cast<GfMenuFieldSkill *>(owner);
  if (skill->unknown200 == nullptr || skill->unknown200->isTerm()) {
    reqState(0);
  }
}

ai::State *GfMenuFieldSkill::StateDispTotal::create(void *buffer) { return new (buffer) StateDispTotal; }

const char *GfMenuFieldSkill::StateDispTotal::getName() const { return "StateDispTotal"; }

void GfMenuFieldSkill::StateDispTotal::onEnter(void *owner, ai::State *previous) { enter(static_cast<GfMenuFieldSkill *>(owner), previous); }

void GfMenuFieldSkill::StateDispTotal::onLeave(void *owner, ai::State *next) {}

void GfMenuFieldSkill::StateDispTotal::onStep(void *owner, const void *param) { update(static_cast<GfMenuFieldSkill *>(owner), *static_cast<const fw::UpdateInfo *>(param)); }

ai::State *GfMenuFieldSkill::StateDispResult::create(void *buffer) { return new (buffer) StateDispResult; }

const char *GfMenuFieldSkill::StateDispResult::getName() const { return "StateDispResult"; }

void GfMenuFieldSkill::StateDispResult::onLeave(void *owner, ai::State *next) {
  GfMenuFieldSkill *skill = static_cast<GfMenuFieldSkill *>(owner);
  mm::mtl::safeRelease(skill->unknown208);
  mm::mtl::safeRelease(skill->unknown200);
}

void GfMenuFieldSkill::StateDispResult::onStep(void *owner, const void *param) { update(static_cast<GfMenuFieldSkill *>(owner), *static_cast<const fw::UpdateInfo *>(param)); }

ai::State *GfMenuFieldSkill::StateDispInfo::create(void *buffer) { return new (buffer) StateDispInfo; }

const char *GfMenuFieldSkill::StateDispInfo::getName() const { return "StateDispInfo"; }

void GfMenuFieldSkill::StateDispInfo::onEnter(void *owner, ai::State *previous) { enter(static_cast<GfMenuFieldSkill *>(owner), previous); }

void GfMenuFieldSkill::StateDispInfo::onLeave(void *owner, ai::State *next) {}

void GfMenuFieldSkill::StateDispInfo::onStep(void *owner, const void *param) { update(static_cast<GfMenuFieldSkill *>(owner), *static_cast<const fw::UpdateInfo *>(param)); }

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfMenuFieldSkill>::~PtrSingleton();
