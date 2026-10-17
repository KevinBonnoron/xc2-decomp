#include "gf/object/component/animation/gf_com_pack_anim.h"

#include "anm/anm_animation_importer.h"
#include "anm/anm_binding.h"
#include "anm/anm_control.h"
#include "anm/anm_factory.h"
#include "anm/anm_util.h"
#include "arc/arc_data.h"
#include "framework/anim/anim_manager.h"
#include "framework/object/updatable_object.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/model/gf_com_model.h"
#include "mm_mtl/fixstr.h"

namespace anm {
class ExtraTruckBuffer;
class Pose;
} // namespace anm

namespace gf {

GfComPackAnim::Mot::Mot() : model(nullptr), control(nullptr), playBackTime(0.0f) {}

void GfComPackAnim::Mot::cleanup(u32 layer) { stop(layer); }

void GfComPackAnim::Mot::stop(u32 layer) {
  if (control == nullptr) {
    return;
  }

  playBackTime = 0.0f;
  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager != nullptr) {
    if (poseSampler.control != nullptr && poseSampler.pose != nullptr) {
      manager->removePoseSampler(layer, poseSampler);
    }
    if (updater.control != nullptr) {
      manager->removeControlUpdater(layer, updater);
    }
  }

  poseSampler.unbind();
  updater.unbind();
  if (control != nullptr) {
    control->release();
    control = nullptr;
  }
}

void GfComPackAnim::Mot::setup(GfComModel *model, u32 layer) { this->model = model; }

void GfComPackAnim::Mot::play(u32 layer, void *motion, bool isLocalSpace) {
  if (model == nullptr) {
    return;
  }

  anm::Pose *pose = model->pose;
  if (pose == nullptr) {
    return;
  }

  anm::ExtraTruckBuffer *extraTruckBuffer = model->extraTruckBuffer;
  anm::Binding *binding = anm::AnimationImporter::import(motion);
  playBackTime = anm::Util::getPlayBackTime(*binding);
  control = anm::Factory::createControl(binding, getAllocator(ALLOCATOR_ANIMATION));
  if (binding != nullptr) {
    binding->release();
  }

  updater.bind(control);
  poseSampler.isLocalSpace = isLocalSpace;
  poseSampler.bind(control, pose, extraTruckBuffer);
  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager != nullptr) {
    if (updater.control != nullptr) {
      manager->addControlUpdater(layer, updater);
    }
    if (poseSampler.control != nullptr && poseSampler.pose != nullptr) {
      manager->addPoseSampler(layer, poseSampler);
    }
  }
}

bool GfComPackAnim::Mot::isPlayEnd() const {
  if (control != nullptr) {
    return playBackTime <= control->m_localTime;
  }

  return true;
}

void GfComPackAnim::Mot::setSpeed(f32 speed) {
  if (control != nullptr) {
    control->m_speed = speed;
  }
}

void GfComPackAnim::Mot::changeLayer(u32 oldLayer, u32 newLayer) {
  if (control == nullptr) {
    return;
  }

  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager == nullptr) {
    return;
  }

  if (poseSampler.control != nullptr && poseSampler.pose != nullptr) {
    manager->removePoseSampler(oldLayer, poseSampler);
    manager->addPoseSampler(newLayer, poseSampler);
  }
  if (updater.control != nullptr) {
    manager->removeControlUpdater(oldLayer, updater);
    manager->addControlUpdater(newLayer, updater);
  }
}

GfComPackAnim::GfComPackAnim() : isLocalSpace(true) {}

void GfComPackAnim::cleanup() {
  mot.cleanup(getLayer());
  for (arc::CArcData **arc = arcs.begin(); arc != arcs.end(); arc++) {
    if (*arc != nullptr) {
      delete *arc;
      *arc = nullptr;
    }
  }

  arcs.clear();
}

void GfComPackAnim::setup(const SetupInfo &info) {
  cleanup();
  for (void *const *data = info.arcs.begin(); data != info.arcs.end(); data++) {
    if (*data != nullptr) {
      // __LINE__ must be 208 as in the original source: it is the line argument of operator new.
#line 208
      arcs.push_back(new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) arc::CArcData(*data));
    }
  }

  isLocalSpace = info.isLocalSpace;
  play(info.name);
}

void GfComPackAnim::play(const char *name) {
  if (name == nullptr) {
    asm volatile(".inst 0xe7ffdefe");
    __builtin_unreachable();
  }

  GfComModel *model = owner->getComponent<GfComModel>();
  if (model != nullptr) {
    mot.setup(model, getLayer());
  }

  mot.stop(getLayer());
  mm::mtl::FixStr<64> fileName;
  fileName.format("%s.anm", name);
  for (arc::CArcData **arc = arcs.begin(); arc != arcs.end(); arc++) {
    void *motion = (*arc)->getFileAdr(fileName.c_str());
    if (motion != nullptr) {
      mot.play(getLayer(), motion, isLocalSpace);
      return;
    }
  }
}

void GfComPackAnim::play(void *motion) {
  if (motion == nullptr) {
    return;
  }

  GfComModel *model = owner->getComponent<GfComModel>();
  if (model != nullptr) {
    mot.setup(model, getLayer());
  }

  mot.stop(getLayer());
  mot.play(getLayer(), motion, isLocalSpace);
}

void GfComPackAnim::stop() {
  mot.stop(getLayer());
  mot.cleanup(getLayer());
}

bool GfComPackAnim::isPlayEnd() const { return mot.isPlayEnd(); }

void GfComPackAnim::setSpeed(f32 speed) { mot.setSpeed(speed); }

void GfComPackAnim::changeLayer(u32 oldLayer, u32 newLayer) {}

const mm::mtl::RTTI *GfComPackAnim::getRTTI() const { return &m_rtti; }

} // namespace gf
