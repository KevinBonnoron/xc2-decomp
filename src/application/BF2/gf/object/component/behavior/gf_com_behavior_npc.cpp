#include "gf/object/component/behavior/gf_com_behavior_npc.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/gf_obj.h"
#include "gmk/gmk_manager.h"

namespace gf {

gmk::AGmkBase *GfComBehaviorNpc::getBindedGmkInst() const { return gmk::getBindedGmkInst(static_cast<GfObj *>(unknown08)->unknownf8); }

void GfComBehaviorNpc::setGoalPos(const mm::Vec3 &position) { unknownc0 = position; }

GfComAsm *GfComBehaviorNpc::getComAsm() const { return unknown08->getComponent<GfComAsm>(); }

} // namespace gf
