#include "dr/dr_res_mdo_seam_coli.h"

namespace ml {

DrResMdoSeamColi::DrResMdoSeamColi(int index) : unknown08(nullptr), m_cache(nullptr), unknown28(nullptr), unknown38(0), unknown3c(index), unknown3e(0), unknown40(0), unknown42(0) {
  unknown10 = nullptr;
}

DrResMdoSeamColi::~DrResMdoSeamColi() {}

void DrResMdoSeamColi::createColi(const void *data, const MdsSeamColiData *coliData) {
  unknown20 = coliData;
  unknown28 = data;
  unknown3e = 0;
  unknown42 = 3;
  unknown38 = coliData->unknown38;
  if ((coliData->unknown54 & 0x40000000) != 0) {
    unknown42 = 0x403;
  } else if ((coliData->unknown54 & 0x80000000) != 0) {
    unknown42 = 0x803;
  }
}

void DrResMdoSeamColi::release() {
  unknown28 = nullptr;
  unknown3e = 0;
  unknown42 = 0;
  m_cache = nullptr;
}

void DrResMdoSeamColi::setCache(DrResMdoSeamMemObj *cache) { m_cache = cache; }

} // namespace ml
