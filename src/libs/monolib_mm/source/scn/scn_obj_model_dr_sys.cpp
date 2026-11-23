#include "scn/scn_obj_model_dr_sys.h"

#include "dr/dr_mdl_obj.h"
#include "ml/attr_transform.h"
#include "ml/scn.h"
#include "scn/scn_render_dr_sys.h"

namespace ml {

ScnObjModelDrSys::ScnObjModelDrSys(Scn *scn, const void *data, const char *name) : ScnObjModel(scn, name), unknown3d8(nullptr), m_data(data) { m_drMan = m_scn->unknown38->m_drMan; }

void ScnObjModelDrSys::update() {}

void ScnObjModelDrSys::apply() {
  getTrans(false)->update();
  if (!isDisp()) {
    if (unknown3d8 != nullptr) {
      unknown3d8->setDisp(false);
    }
  } else if (unknown3d8 != nullptr) {
    unknown3d8->setDisp(true);
    unknown3d8->setClip(isClip());
    unknown3d8->setFrameSpd((unknown34c & FLAG_UNKNOWN_6) ? m_frameSpd : 0.0f);
  }
}

void ScnObjModelDrSys::setGroups(int groups) { unknown3d8->m_groups = groups; }

int ScnObjModelDrSys::getGroups() { return unknown3d8->m_groups; }

void ScnObjModelDrSys::setAlpha(f32 alpha) { unknown3d8->setAlpha(alpha); }

f32 ScnObjModelDrSys::getAlpha() const { return unknown3d8->getAlpha(); }

void ScnObjModelDrSys::setWriteStencil(bool isWriteStencil) { unknown3d8->setWriteStencil(isWriteStencil); }

void ScnObjModelDrSys::setAlwaysTexStm(bool isAlwaysTexStm) { unknown3d8->setAlwaysTexStm(isAlwaysTexStm); }

bool ScnObjModelDrSys::isMdlTexStm() const { return unknown3d8->isMdlTexStm(); }

bool ScnObjModelDrSys::isMemTexStm() const { return unknown3d8->isMemTexStm(); }

const mm::Vec3 &ScnObjModelDrSys::getAABBMax() const { return unknown3d8->getAABBMax(); }

const mm::Vec3 &ScnObjModelDrSys::getAABBMin() const { return unknown3d8->getAABBMin(); }

const mm::Vec3 &ScnObjModelDrSys::getCenter() const { return unknown3d8->m_center; }

f32 ScnObjModelDrSys::getLength() const { return unknown3d8->m_length; }

} // namespace ml
