#include "gf/object/component/pc/field/gf_pc_state_field.h"

#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_mtl/bitflag.h"

namespace gf {
namespace pc {

void StateField::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->getProperty();
  if (property->input.flags.test(INPUT_ID_LOCK)) {
    StateUtilField::flipAutoRun(*property);
  }
  if (StateUtilField::isInputInverseDirAutoRun(*property)) {
    StateUtilField::setAutoRun(*property, false);
  }
  if (StateUtilField::testAutoRun(*property)) {
    StateUtilField::setAutoRunInput(*property);
  }
}

} // namespace pc
} // namespace gf
