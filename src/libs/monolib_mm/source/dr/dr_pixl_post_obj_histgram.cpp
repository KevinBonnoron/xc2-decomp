#include "dr/dr_pixl_post_obj_histgram.h"

#include "dr/dr_res_use_query_obj.h"

namespace ml {

DrPixlPostObjHistgram::~DrPixlPostObjHistgram() {
  DrResUseQueryObj *query = unknown18;
  if (query != nullptr) {
    delete query;
    unknown18 = nullptr;
  }
}

f32 DrPixlPostObjHistgram::getMaxLuminance() const { return unknown20[9]; }

int DrPixlPostObjHistgram::getSectionNum() const { return 0xb; }

f32 DrPixlPostObjHistgram::getPercentage(u32 index) const { return m_percentage[index]; }

} // namespace ml
