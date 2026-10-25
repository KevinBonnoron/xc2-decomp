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

GfComPackAnim::Mot::Mot() : unknown00(nullptr), unknown08(nullptr), unknown68(0.0f) {}

void GfComPackAnim::Mot::cleanup(u32 layer) { stop(layer); }

void GfComPackAnim::Mot::stop(u32 layer) {
  if (unknown08 == nullptr) {
    return;
  }

  unknown68 = 0.0f;
  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager != nullptr) {
    if (unknown30.unknown18 != nullptr && unknown30.unknown20 != nullptr) {
      manager->removePoseSampler(layer, unknown30);
    }
    if (unknown10.unknown18 != nullptr) {
      manager->removeControlUpdater(layer, unknown10);
    }
  }

  unknown30.unbind();
  unknown10.unbind();
  if (unknown08 != nullptr) {
    unknown08->release();
    unknown08 = nullptr;
  }
}

void GfComPackAnim::Mot::setup(GfComModel *model, u32 layer) { this->unknown00 = model; }

void GfComPackAnim::Mot::play(u32 layer, void *motion, bool isLocalSpace) {
  if (unknown00 == nullptr) {
    return;
  }

  anm::Pose *pose = unknown00->unknown30;
  if (pose == nullptr) {
    return;
  }

  anm::ExtraTruckBuffer *extraTruckBuffer = unknown00->unknown38;
  anm::Binding *binding = anm::AnimationImporter::import(motion);
  unknown68 = anm::Util::getPlayBackTime(*binding);
  unknown08 = anm::Factory::createControl(binding, getAllocator(ALLOCATOR_ANIMATION));
  if (binding != nullptr) {
    binding->release();
  }

  unknown10.bind(unknown08);
  unknown30.unknown32 = isLocalSpace;
  unknown30.bind(unknown08, pose, extraTruckBuffer);
  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager != nullptr) {
    if (unknown10.unknown18 != nullptr) {
      manager->addControlUpdater(layer, unknown10);
    }
    if (unknown30.unknown18 != nullptr && unknown30.unknown20 != nullptr) {
      manager->addPoseSampler(layer, unknown30);
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

  if (unknown30.unknown18 != nullptr && unknown30.unknown20 != nullptr) {
    manager->removePoseSampler(oldLayer, unknown30);
    manager->addPoseSampler(newLayer, unknown30);
  }
  if (unknown10.unknown18 != nullptr) {
    manager->removeControlUpdater(oldLayer, unknown10);
    manager->addControlUpdater(newLayer, unknown10);
  }
}

GfComPackAnim::GfComPackAnim() : unknownc8(true) {}

GfComPackAnim::~GfComPackAnim() {}

void GfComPackAnim::cleanup() {
  unknown10.cleanup(getLayer());
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
      unknown80.push_back(new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) arc::CArcData(*data));
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
    unknown10.setup(model, getLayer());
  }

  unknown10.stop(getLayer());
  mm::mtl::FixStr<64> fileName;
  fileName.format("%s.anm", name);
  for (arc::CArcData **arc = unknown80.begin(); arc != unknown80.end(); arc++) {
    void *motion = (*arc)->getFileAdr(fileName.c_str());
    if (motion != nullptr) {
      unknown10.play(getLayer(), motion, unknownc8);
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
    unknown10.setup(model, getLayer());
  }

  unknown10.stop(getLayer());
  unknown10.play(getLayer(), motion, unknownc8);
}

void GfComPackAnim::stop() {
  unknown10.stop(getLayer());
  unknown10.cleanup(getLayer());
}

bool GfComPackAnim::isPlayEnd() const { return unknown10.isPlayEnd(); }

void GfComPackAnim::setSpeed(f32 speed) { unknown10.setSpeed(speed); }

void GfComPackAnim::changeLayer(u32 oldLayer, u32 newLayer) {}

const mm::mtl::RTTI *GfComPackAnim::getRTTI() const { return &m_rtti; }

} // namespace gf
