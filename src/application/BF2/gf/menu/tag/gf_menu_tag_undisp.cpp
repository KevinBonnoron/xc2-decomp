#include "gf/menu/tag/gf_menu_tag_undisp.h"

namespace gf {

const char *GfMenuTagUndisp::getTagName() { return "ML:undisp"; }

const char *GfMenuTagUndisp::convBegin(const ParamList &params, u16 id) { return " "; }

} // namespace gf
