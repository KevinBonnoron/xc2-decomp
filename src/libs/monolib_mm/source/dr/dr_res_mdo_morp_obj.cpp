#include "dr/dr_res_mdo_morp_obj.h"

namespace ml {

DrResMdoMorpObj::DrResMdoMorpObj() : unknown00(0), unknown01(0), unknown02(0), unknown08(nullptr), unknown10(0) {}

DrResMdoMorpObj::~DrResMdoMorpObj() {}

u32 DrResMdoMorpObj::calcWorkSize(const u8 *resource) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(resource);
  const unknown002 *table = reinterpret_cast<const unknown002 *>(resource + header->unknown80);
  return table->unknown04 * 0x20 + sizeof(DrResMdoMorpObj);
}

void DrResMdoMorpObj::release(DrResMdoMorpObj *&morpObj) {
  if (morpObj != nullptr) {
    morpObj = nullptr;
  }
}

} // namespace ml
