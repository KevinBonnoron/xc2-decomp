#include "dr/dr_pixl_occ_query.h"

#include "dr/dr_ap_gx_type.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "grlib/cglib_shader.h"

namespace ml {

void DrPixlOccQuery::begin() {
  DrAPGxType::beginOccQuery();
  unknown10->bindShdBoxVertex();
  unknown28 = 0;
  unknown18->setupShader(0u);
  unknown24 = (unknown18->unknown38 + unknown18->unknown58)->getUniformBlockOfs("U_POST");
}

DrResQueryObj *DrPixlOccQuery::createObj() {
  DrResQueryObj *obj = unknown48;
  if (obj != nullptr) {
    DrResQueryObj *next = obj->unknown00;
    if (next == nullptr) {
      unknown48 = nullptr;
      unknown50 = nullptr;
    } else {
      unknown48 = next;
      next->unknown08 = nullptr;
    }
    if (unknown60 != nullptr) {
      unknown60->unknown00 = obj;
    }
    if (unknown58 == nullptr) {
      unknown58 = obj;
    }
    DrResQueryObj *last = unknown60;
    obj->unknown00 = nullptr;
    obj->unknown08 = last;
    unknown60 = obj;
    unknown74--;
    unknown70++;
    obj->unknown38 = 0;
    obj->unknown28 = nullptr;
    obj->unknown30 = nullptr;
  }
  return obj;
}

void DrPixlOccQuery::releaseObj(DrResQueryObj *obj) {
  DrResQueryObj *next = obj->unknown00;
  DrResQueryObj *prev = obj->unknown08;
  if (next == nullptr) {
    if (prev != nullptr) {
      prev->unknown00 = nullptr;
    }
  } else {
    if (prev != nullptr) {
      prev->unknown00 = next;
    }
    next->unknown08 = prev;
  }
  if (unknown60 == obj) {
    unknown60 = prev;
  }
  if (unknown58 == obj) {
    unknown58 = next;
    if (next != nullptr) {
      next->unknown08 = nullptr;
    }
  }
  if (unknown50 == nullptr) {
    unknown48 = obj;
    unknown50 = obj;
    obj->unknown08 = nullptr;
  } else {
    unknown50->unknown00 = obj;
    obj->unknown08 = unknown50;
    unknown50 = obj;
  }
  obj->unknown00 = nullptr;
  unknown74++;
  unknown70--;
}

void DrPixlOccQuery::update() {
  DrResQueryObj *obj = unknown58;
  while (obj != nullptr) {
    bool isDone = obj->update();
    DrResQueryObj *next = obj->unknown00;
    if (isDone) {
      releaseObj(obj);
    }
    obj = next;
  }
}

void DrPixlOccQuery::end() { DrAPGxType::endOccQuery(); }

} // namespace ml
