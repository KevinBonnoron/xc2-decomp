#include "event/chara_stop_action.h"

#include "event/chara_util.h"
#include "gf/object/gf_obj_util.h"

namespace gf {
class GfObj;
} // namespace gf

namespace event {

ICmd::RESULT CharaStopAction::update(const Param &param) {
  gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
  if (obj != nullptr) {
    CharaUtil::execCmd(obj, "C_idle", "S_idle", "S_idle");
  }
  return RESULT_END;
}

} // namespace event
