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

GfComPackAnim::Mot::Mot() : m_comModel(nullptr), unknown08(nullptr), unknown68(0.0f) {}

void GfComPackAnim::Mot::cleanup(u32 layer) { stop(layer); }

void GfComPackAnim::Mot::stop(u32 layer) {
  if (unknown08 == nullptr) {
    return;
  }

  unknown68 = 0.0f;
  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager != nullptr) {
    if (m_animSinglePoseSamper.unknown18 != nullptr && m_animSinglePoseSamper.unknown20 != nullptr) {
      manager->removePoseSampler(layer, m_animSinglePoseSamper);
    }
    if (m_animControlUpdater.unknown18 != nullptr) {
      manager->removeControlUpdater(layer, m_animControlUpdater);
    }
  }

  m_animSinglePoseSamper.unbind();
  m_animControlUpdater.unbind();
  if (unknown08 != nullptr) {
    unknown08->release();
    unknown08 = nullptr;
  }
}

void GfComPackAnim::Mot::setup(GfComModel *model, u32 layer) { this->m_comModel = model; }

void GfComPackAnim::Mot::play(u32 layer, void *motion, bool isLocalSpace) {
  if (m_comModel == nullptr) {
    return;
  }

  anm::Pose *pose = m_comModel->unknown30;
  if (pose == nullptr) {
    return;
  }

  anm::ExtraTruckBuffer *extraTruckBuffer = m_comModel->unknown38;
  anm::Binding *binding = anm::AnimationImporter::import(motion);
  unknown68 = anm::Util::getPlayBackTime(*binding);
  unknown08 = anm::Factory::createControl(binding, getAllocator(ALLOCATOR_UNKNOWN_7));
  if (binding != nullptr) {
    binding->release();
  }

  m_animControlUpdater.bind(unknown08);
  m_animSinglePoseSamper.unknown32 = isLocalSpace;
  m_animSinglePoseSamper.bind(unknown08, pose, extraTruckBuffer);
  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager != nullptr) {
    if (m_animControlUpdater.unknown18 != nullptr) {
      manager->addControlUpdater(layer, m_animControlUpdater);
    }
    if (m_animSinglePoseSamper.unknown18 != nullptr && m_animSinglePoseSamper.unknown20 != nullptr) {
      manager->addPoseSampler(layer, m_animSinglePoseSamper);
    }
  }
}

bool GfComPackAnim::Mot::isPlayEnd() const {
  if (unknown08 != nullptr) {
    return unknown68 <= unknown08->unknown48;
  }

  return true;
}

void GfComPackAnim::Mot::setSpeed(f32 speed) {
  if (unknown08 != nullptr) {
    unknown08->unknown50 = speed;
  }
}

void GfComPackAnim::Mot::changeLayer(u32 oldLayer, u32 newLayer) {
  if (unknown08 == nullptr) {
    return;
  }

  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager == nullptr) {
    return;
  }

  if (m_animSinglePoseSamper.unknown18 != nullptr && m_animSinglePoseSamper.unknown20 != nullptr) {
    manager->removePoseSampler(oldLayer, m_animSinglePoseSamper);
    manager->addPoseSampler(newLayer, m_animSinglePoseSamper);
  }
  if (m_animControlUpdater.unknown18 != nullptr) {
    manager->removeControlUpdater(oldLayer, m_animControlUpdater);
    manager->addControlUpdater(newLayer, m_animControlUpdater);
  }
}

GfComPackAnim::GfComPackAnim() : unknownc8(true) {}

GfComPackAnim::~GfComPackAnim() {}

void GfComPackAnim::cleanup() {
  m_mot.cleanup(getLayer());
  for (arc::CArcData **arc = unknown80.begin(); arc != unknown80.end(); arc++) {
    if (*arc != nullptr) {
      delete *arc;
      *arc = nullptr;
    }
  }

  unknown80.clear();
}

void GfComPackAnim::setup(const SetupInfo &info) {
  cleanup();
  for (void *const *data = info.unknown00.begin(); data != info.unknown00.end(); data++) {
    if (*data != nullptr) {
      // __LINE__ must be 208 as in the original source: it is the line argument of operator new.
#line 208
      unknown80.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) arc::CArcData(*data));
    }
  }

  unknownc8 = info.unknown50;
  play(info.unknown48);
}

void GfComPackAnim::play(const char *name) {
  if (name == nullptr) {
    asm volatile(".inst 0xe7ffdefe");
    __builtin_unreachable();
  }

  GfComModel *model = unknown08->getComponent<GfComModel>();
  if (model != nullptr) {
    m_mot.setup(model, getLayer());
  }

  m_mot.stop(getLayer());
  mm::mtl::FixStr<64> fileName;
  fileName.format("%s.anm", name);
  for (arc::CArcData **arc = unknown80.begin(); arc != unknown80.end(); arc++) {
    void *motion = (*arc)->getFileAdr(fileName.c_str());
    if (motion != nullptr) {
      m_mot.play(getLayer(), motion, unknownc8);
      return;
    }
  }
}

void GfComPackAnim::play(void *motion) {
  if (motion == nullptr) {
    return;
  }

  GfComModel *model = unknown08->getComponent<GfComModel>();
  if (model != nullptr) {
    m_mot.setup(model, getLayer());
  }

  m_mot.stop(getLayer());
  m_mot.play(getLayer(), motion, unknownc8);
}

void GfComPackAnim::stop() {
  m_mot.stop(getLayer());
  m_mot.cleanup(getLayer());
}

bool GfComPackAnim::isPlayEnd() const { return m_mot.isPlayEnd(); }

void GfComPackAnim::setSpeed(f32 speed) { m_mot.setSpeed(speed); }

void GfComPackAnim::changeLayer(u32 oldLayer, u32 newLayer) {}

const mm::mtl::RTTI *GfComPackAnim::getRTTI() const { return &m_rtti; }

} // namespace gf
