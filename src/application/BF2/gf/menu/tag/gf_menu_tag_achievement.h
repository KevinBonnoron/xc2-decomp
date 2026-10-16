#pragma once
#include "types.h"
#include "ui/text/ui_tag_conv.h"

namespace gf {

class GfMenuTagAchievement : public ui::UITagConv {
public:
  const char *getTagName() override;
  const char *convBegin(const ParamList &params, u16 id) override;
};

} // namespace gf
