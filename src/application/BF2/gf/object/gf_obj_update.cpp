#include "gf/object/gf_obj_update.h"

#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/animation/gf_com_evt_anim.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/gf_obj.h"

namespace gf {

void GfObjUpdate::updateComponent(GfObj *obj, const fw::UpdateInfo &info) {
  if (obj->unknown118) {
    GfComAsm *comAsm = obj->getComponent<GfComAsm>();
    if (comAsm != nullptr) {
      comAsm->executeCallback();
    } else {
      GfComEvtAnim *evtAnim = obj->getComponent<GfComEvtAnim>();
      if (evtAnim != nullptr) {
        evtAnim->unknown10.executeCallback(evtAnim);
      }
    }
    GfComBehavior *behavior = obj->getComponent<GfComBehavior>();
    if (behavior != nullptr) {
      behavior->update(info);
    }
    comAsm = obj->getComponent<GfComAsm>();
    if (comAsm != nullptr) {
      comAsm->executeCallback();
    } else {
      GfComEvtAnim *evtAnim = obj->getComponent<GfComEvtAnim>();
      if (evtAnim != nullptr) {
        evtAnim->unknown10.executeCallback(evtAnim);
      }
    }
  }
}

} // namespace gf
