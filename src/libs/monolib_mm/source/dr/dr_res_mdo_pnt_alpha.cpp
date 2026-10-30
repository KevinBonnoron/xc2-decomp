#include "dr/dr_res_mdo_pnt_alpha.h"

namespace ml {

void DrResMdoPntAlpha::init() {
  unknown00 = 0;
  unknown04 = 1.0f;
  unknown08 = nullptr;
}

f32 DrResMdoPntAlpha::getObjAlpha(bool unknown001) {
  if (unknown001) {
    unknown00 |= unknown004_2 | unknown004_4;
  } else {
    unknown00 &= ~(unknown004_2 | unknown004_4);
    unknown00 |= unknown004_2;
  }
  return unknown04;
}

void DrResMdoPntAlpha::setAlphaReset(bool unknown001) {
  f32 alpha = 1.0f;
  if (!unknown001) {
    alpha = 0.0f;
  }
  if (unknown001) {
    unknown00 |= unknown004_2 | unknown004_4;
  } else {
    unknown00 &= ~(unknown004_2 | unknown004_4);
    unknown00 |= unknown004_2;
  }
  unknown04 = alpha;
}

void DrResMdoPntAlpha::create(const void *unknown001) {
  unknown08 = unknown001;
  unknown00 = unknown004_1;
}

s32 DrResMdoPntAlphaMan::getWrkSize(s32 unknown001) { return unknown001 * (sizeof(DrResMdoPntAlpha) + sizeof(DrResMdoPntAlpha *)) + sizeof(DrResMdoPntAlphaMan); }

void DrResMdoPntAlphaMan::setup(DrResMdoPntAlpha *unknown001, DrResMdoPntAlpha **unknown002, s32 unknown003) {
  unknown00 = unknown001;
  unknown08 = unknown002;
  unknown10 = unknown003;
  unknown14 = 0;
  for (s32 i = 0; i < unknown10; i++) {
    unknown00[i].init();
  }
}

f32 DrResMdoPntAlphaMan::getAlphaObj(const void *unknown001, bool unknown002) {
  for (s32 i = 0; i < unknown14; i++) {
    DrResMdoPntAlpha *item = unknown08[i];
    if (item->unknown08 == unknown001) {
      return item->getObjAlpha(unknown002);
    }
  }
  for (s32 i = 0; i < unknown10; i++) {
    DrResMdoPntAlpha *item = &unknown00[i];
    if (!(item->unknown00 & DrResMdoPntAlpha::unknown004_1)) {
      unknown08[unknown14] = item;
      unknown08[unknown14]->create(unknown001);
      return unknown08[unknown14++]->getObjAlpha(unknown002);
    }
  }
  return 1.0f;
}

void DrResMdoPntAlphaMan::setAlphaReset(const void *unknown001, bool unknown002) {
  for (s32 i = 0; i < unknown14; i++) {
    DrResMdoPntAlpha *item = unknown08[i];
    if (item->unknown08 == unknown001) {
      item->setAlphaReset(unknown002);
      return;
    }
  }
  for (s32 i = 0; i < unknown10; i++) {
    DrResMdoPntAlpha *item = &unknown00[i];
    if (!(item->unknown00 & DrResMdoPntAlpha::unknown004_1)) {
      unknown08[unknown14] = item;
      unknown08[unknown14]->create(unknown001);
      unknown08[unknown14++]->setAlphaReset(unknown002);
    }
  }
}

} // namespace ml
