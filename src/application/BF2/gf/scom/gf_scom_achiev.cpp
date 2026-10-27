#include "gf/scom/gf_scom_achiev.h"

#include "gf/data/gf_data_achievement.h"

namespace gf {

void SCOM_ACHIEV_INC::addTotalCount(u32 stats, u32 count) { GfDataAchievement::addTotalCount(stats, count); }

} // namespace gf
