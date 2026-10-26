#include "dr/dr_pixl_post_obj_histgram.h"

namespace ml {

f32 DrPixlPostObjHistgram::getMaxLuminance() const { return unknown20[9]; }

int DrPixlPostObjHistgram::getSectionNum() const { return 0xb; }

f32 DrPixlPostObjHistgram::getPercentage(u32 index) const { return m_percentage[index]; }

} // namespace ml
