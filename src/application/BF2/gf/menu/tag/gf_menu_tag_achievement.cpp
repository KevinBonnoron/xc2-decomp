#include "gf/menu/tag/gf_menu_tag_achievement.h"

#include "gf/menu/gf_menu_reference.h"
#include "ui/ui_str.h"

namespace gf {

const char *GfMenuTagAchievement::getTagName() { return "ML:AchieveParam"; }

const char *GfMenuTagAchievement::convBegin(const ParamList &params, u16 id) {
  const ui::UIStr &string = GfMenuReference::getReferenceString(id);
  if (string.isValid()) {
    return string.c_str();
  }
  return "<error>";
}

} // namespace gf
