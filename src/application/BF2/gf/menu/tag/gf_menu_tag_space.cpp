#include "gf/menu/tag/gf_menu_tag_space.h"

namespace gf {

const char *GfMenuTagSpace::getTagName() { return "ML:Space"; }

const char *GfMenuTagSpace::convBegin(const ParamList &params, u16 id) { return " "; }

} // namespace gf
