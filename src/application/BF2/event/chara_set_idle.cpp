#include "event/chara_set_idle.h"

#include "bdat.h"
#include "event/chara_dys_updater.h"
#include "event/chara_util.h"
#include "event/cmd_variable.h"
#include "gf/object/gf_obj_util.h"

namespace gf {
class GfObj;
} // namespace gf

namespace event {

const char *CharaSetIdle::type2stat(int type) {
  return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_idletype"), "stat", type, 7));
}

const char *CharaSetIdle::type2name(int type) {
  return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_idletype"), "name", type, 7));
}

void CharaSetIdle::init() { mStep = 0; }

ICmd::RESULT CharaSetIdle::update(const Param &param) {
  gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
  if (obj != nullptr && param.getFrame() <= 0) {
    int type = param.val(1).getS32();
    CharaUtil::setStat(obj, type2stat(type));
    mDys->resetDynamics(0);
    mType = type;
  }
  return RESULT_END;
}

} // namespace event
