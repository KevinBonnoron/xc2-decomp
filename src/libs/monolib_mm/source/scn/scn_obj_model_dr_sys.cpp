#include "scn/scn_obj_model_dr_sys.h"

#include "dr/dr_mdl_obj.h"
#include "ml/attr_transform.h"
#include "ml/scn.h"
#include "scn/scn_render_dr_sys.h"

namespace ml {

ScnObjModelDrSys::ScnObjModelDrSys(Scn *scn, const void *data, const char *name) : ScnObjModel(scn, name), m_drMdl(nullptr), m_data(data) { m_drMan = m_scn->renderDrSys->drMan; }

void ScnObjModelDrSys::update() {}

void ScnObjModelDrSys::apply() {
  getTrans(false)->update();
  if (!isDisp()) {
    if (m_drMdl != nullptr) {
      m_drMdl->setDisp(false);
    }
  } else if (m_drMdl != nullptr) {
    m_drMdl->setDisp(true);
    m_drMdl->setClip(isClip());
    m_drMdl->setFrameSpd((m_flags & FLAG_FRAME_SPD) ? m_frameSpd : 0.0f);
  }
}

void ScnObjModelDrSys::setGroups(int groups) { m_drMdl->m_groups = groups; }

int ScnObjModelDrSys::getGroups() { return m_drMdl->m_groups; }

void ScnObjModelDrSys::setAlpha(f32 alpha) { m_drMdl->setAlpha(alpha); }

f32 ScnObjModelDrSys::getAlpha() const { return m_drMdl->getAlpha(); }

void ScnObjModelDrSys::setWriteStencil(bool isWriteStencil) { m_drMdl->setWriteStencil(isWriteStencil); }

void ScnObjModelDrSys::setAlwaysTexStm(bool isAlwaysTexStm) { m_drMdl->setAlwaysTexStm(isAlwaysTexStm); }

bool ScnObjModelDrSys::isMdlTexStm() const { return m_drMdl->isMdlTexStm(); }

bool ScnObjModelDrSys::isMemTexStm() const { return m_drMdl->isMemTexStm(); }

const mm::Vec3 &ScnObjModelDrSys::getAABBMax() const { return m_drMdl->getAABBMax(); }

const mm::Vec3 &ScnObjModelDrSys::getAABBMin() const { return m_drMdl->getAABBMin(); }

const mm::Vec3 &ScnObjModelDrSys::getCenter() const { return m_drMdl->m_center; }

f32 ScnObjModelDrSys::getLength() const { return m_drMdl->m_length; }

} // namespace ml
