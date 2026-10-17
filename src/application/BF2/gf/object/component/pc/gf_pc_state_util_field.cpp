#include "gf/object/component/pc/gf_pc_state_util_field.h"

#include "gf/object/component/animation/gf_com_asm.h"

namespace gf {
namespace pc {

bool StateUtilField::execAsmCmd(GfComAsm &comAsm, ASM_CMD_ID_FIELD id) { return comAsm.execCmd(getASMCmdNameField(id), ANIM_LAYER_BASE); }

} // namespace pc
} // namespace gf
