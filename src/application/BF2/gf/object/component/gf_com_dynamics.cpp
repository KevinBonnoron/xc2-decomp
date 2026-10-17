#include "gf/object/component/gf_com_dynamics.h"

#include "anm/anm_array-inl.h"
#include "framework/dynamics/dynamics_manager.h"
#include "framework/dynamics/force_calculator.h"
#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/gf_com_wind.h"
#include "gf/object/component/model/gf_com_model.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"
#include "skd/skd_collision_object.h"
#include "skd/skd_dynamics.h"
#include "skd/skd_factory.h"

namespace anm {
class Pose;
} // namespace anm
namespace fw {
class WindProbe;
} // namespace fw

namespace gf {

bool GfComDynamics::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  if (message.id == MSG_DEBUG_ACTIVATE_COMPONENT_WINDOW) {
    procMsgActivateComponentDebugWindow(sender, static_cast<MsgDebugActivateComponentWindow &>(message));
    return true;
  }

  return false;
}

void GfComDynamics::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

GfComDynamics::GfComDynamics() : iterationCount(ITERATION_COUNT_DEFAULT), isMaxIteration(false), viewer(nullptr) { viewerListener.owner = this; }

GfComDynamics::~GfComDynamics() {}

void GfComDynamics::setup(const SetupInfo &info) {
  if (info.resDynamics == nullptr) {
    return;
  }

  GfComModel *model = owner->getComponent<GfComModel>();
  if (model == nullptr) {
    return;
  }

  anm::Pose *pose = model->pose;
  if (pose == nullptr) {
    return;
  }

  skd::CollisionObject *collisionObject = info.collisionObject;
  bool isCreateCollision = false;
  if (collisionObject == nullptr) {
    collisionObject = skd::Factory::createColObject(info.resDynamics->collisions, *pose, getAllocator(ALLOCATOR_DEFAULT));
    isCreateCollision = true;
  }

  if (info.forceCalculator != nullptr) {
    forceCalculator = info.forceCalculator;
  } else {
    GfComWind *wind = owner->getComponent<GfComWind>();
    if (wind != nullptr) {
      forceCalculator = fw::WindForceCalculator::create().get();
      fw::WindProbe *probe = wind->probe;
      fw::ForceCalculator *calculator = forceCalculator.operator->();
      fw::WindForceCalculator *windForceCalculator = calculator != nullptr ? mm::mtl::dynamicCast<fw::WindForceCalculator>(calculator) : nullptr;
      windForceCalculator->bindProbe(*probe);
    }
  }

  skd::Dynamics *dynamics =
      skd::Factory::createDynamics(collisionObject, *info.resDynamics->solvers, *pose, forceCalculator.get(), getAllocator(ALLOCATOR_DEFAULT));
  dynamics->iterationCount = info.iterationCount;
  fw::DyanmicsManager *manager = fw::DyanmicsManager::get();
  if (manager != nullptr) {
    u32 layer = getLayer();
    updater.bind(dynamics, model->referenceFrame);
    updater.preUpdateCallback.bind(this, &GfComDynamics::applyAttribute);
    manager->addUpdater(layer, updater);
    if (dynamics != nullptr) {
      dynamics->release();
    }

    if (isCreateCollision) {
      colObjUpdater.bind(collisionObject);
      manager->addColUpdater(layer, colObjUpdater);
      if (collisionObject != nullptr) {
        collisionObject->release();
      }
    }
  }

  iterationCount = info.iterationCount;
}

void GfComDynamics::applyAttribute() {
  GfComAsm *comAsm = owner->getComponent<GfComAsm>();
  if (comAsm == nullptr) {
    return;
  }

  skd::Dynamics *dynamics = updater.dynamics;
  u64 attribute = comAsm->getAttribute(static_cast<AsmCategory>(0), ANIM_LAYER_BASE);
  bool isFreeMovement = (attribute & ASM_ATTRIBUTE_LIMIT_MOVEMENT) == 0;
  f32 maxMoveDistance = isFreeMovement ? 0.1f : 0.03f;
  f32 maxRotation = isFreeMovement ? 0.0f : 0.1f;
  dynamics->maxMoveDistance = maxMoveDistance;
  dynamics->maxRotation = maxRotation;
  if ((attribute & ASM_ATTRIBUTE_MAX_ITERATION) != 0 || isMaxIteration) {
    dynamics->iterationCount = ITERATION_COUNT_MAX;
  } else {
    dynamics->iterationCount = iterationCount;
  }
}

void GfComDynamics::cleanup() {
  if (forceCalculator.get() != nullptr) {
    fw::WindForceCalculator *windForceCalculator = mm::mtl::dynamicCast<fw::WindForceCalculator>(forceCalculator.get());
    if (windForceCalculator != nullptr) {
      windForceCalculator->unbindProbe();
    }
  }

  fw::DyanmicsManager *manager = fw::DyanmicsManager::get();
  if (manager == nullptr) {
    return;
  }

  u32 layer = getLayer();
  if (updater.dynamics != nullptr && updater.referenceFrame.get() != nullptr) {
    manager->removeUpdater(layer, updater);
    updater.preUpdateCallback.clear();
    updater.unbind();
  }
  if (colObjUpdater.collisionObject != nullptr) {
    manager->removeColUpdater(layer, colObjUpdater);
    colObjUpdater.unbind();
  }
}

void GfComDynamics::changeLayer(u32 oldLayer, u32 newLayer) {
  fw::DyanmicsManager *manager = fw::DyanmicsManager::get();
  if (manager == nullptr) {
    return;
  }

  if (updater.dynamics != nullptr && updater.referenceFrame.get() != nullptr) {
    manager->removeUpdater(oldLayer, updater);
    manager->addUpdater(newLayer, updater);
  }
  if (colObjUpdater.collisionObject != nullptr) {
    manager->removeColUpdater(oldLayer, colObjUpdater);
    manager->addColUpdater(newLayer, colObjUpdater);
  }
}

void GfComDynamics::resetMovement() {
  updater.setEnableMovement(false);
  updater.setEnableMovement(true);
}

u32 GfComDynamics::getSolverCount() const {
  if (updater.dynamics != nullptr) {
    return updater.dynamics->solvers.size();
  }

  return 0;
}

static const char *findSolverName(const skd::Dynamics *dynamics, u32 index) {
  if (index == static_cast<u32>(-1) || dynamics == nullptr) {
    return nullptr;
  }

  const anm::Array<skd::ResSolver> &solvers = *dynamics->resSolvers;
  if (index < solvers.size()) {
    return solvers[index].name;
  }

  return nullptr;
}

const char *GfComDynamics::getSolverName(u32 index) const { return findSolverName(updater.dynamics, index); }

u32 GfComDynamics::getSolverID(const char *name) const {
  if (updater.dynamics != nullptr) {
    return updater.dynamics->solvers.size();
  }

  return static_cast<u32>(-1);
}

void GfComDynamics::setSolverBlendWeight(u32 index, f32 weight) {
  if (updater.dynamics != nullptr) {
    updater.dynamics->setSolverBlendWeight(index, weight);
  }
}

f32 GfComDynamics::getSolverBlendWeight(u32 index) const {
  if (updater.dynamics != nullptr) {
    return updater.dynamics->getSolverBlendWeight(index);
  }

  return 1.0f;
}

const mm::mtl::RTTI *GfComDynamics::getRTTI() const { return &m_rtti; }

} // namespace gf
