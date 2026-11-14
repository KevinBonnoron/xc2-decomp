#include "dr/dr_res_mdo_alp_tbl.h"

#include <new>
#include <string.h>

#include "dr/dr_res_mdo_lod_obj.h"
#include "dr/dr_res_mdo_lod_parts.h"
#include "dr/dr_res_mdo_mesh_obj.h"

namespace ml {

DrResMdoAlpTbl::~DrResMdoAlpTbl() { CGLibVtxInstans::release(); }

int DrResMdoAlpTbl::setup(const u8 *resource, u8 *work) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(resource);
  if (!(header->unknown02 & 4)) {
    return 0;
  }
  unknown30 = reinterpret_cast<f32 *>(work);
  const unknown002 *data = reinterpret_cast<const unknown002 *>(resource + header->unknown90);
  unknown40 = reinterpret_cast<const unknown003 *>(reinterpret_cast<const u8 *>(data) + data->unknown00);
  unknown48 = data->unknown04;
  s32 count = data->unknown04;
  u32 alignedCount = count + (4 - count % 4) % 4;
  createInstansBuffer(alignedCount * 8);
  for (u32 i = 0; i < unknown48; i++) {
    unknown30[i] = 1.0f;
  }
  u32 words = unknown48 >> 5;
  if ((unknown48 & 0x1f) != 0) {
    words++;
  }
  unknown38 = reinterpret_cast<u32 *>(work + alignedCount * sizeof(f32));
  memset(unknown38, 0, words * sizeof(u32));
  return alignedCount * sizeof(f32) + words * sizeof(u32) + sizeof(DrResMdoAlpTbl);
}

int DrResMdoAlpTbl::setupCnt(u32 count, u8 *work) {
  unknown48 = count;
  unknown40 = nullptr;
  u32 alignedCount = count + (-count & 3);
  unknown30 = reinterpret_cast<f32 *>(work);
  createInstansBuffer(alignedCount * 8);
  for (u32 i = 0; i < unknown48; i++) {
    unknown30[i] = 1.0f;
  }
  u32 words = unknown48 >> 5;
  if ((unknown48 & 0x1f) != 0) {
    words++;
  }
  unknown38 = reinterpret_cast<u32 *>(work + alignedCount * sizeof(f32));
  memset(unknown38, 0, words * sizeof(u32));
  return alignedCount * sizeof(f32) + words * sizeof(u32) + sizeof(DrResMdoAlpTbl);
}

void DrResMdoAlpTbl::updateInstace() {
  beginInstansBuff();
  f32 *buffer = static_cast<f32 *>(getNextInstansBuff());
  for (u32 i = 0; i < unknown48; i++) {
    if (unknown38[i >> 5] & (1 << (i & 0x1f))) {
      buffer[i] = 1.0f - unknown30[i];
    } else {
      buffer[i] = unknown30[i];
    }
  }
  unknown08 += unknown48 * sizeof(f32);
  updateInstansBuff();
}

void DrResMdoAlpTbl::update(f32 alpha, const DrResMdoLodObj *lodObj, const DrResMdoMeshObj *meshObj) {
  const unknown003 *entry = unknown40;
  if (meshObj != nullptr) {
    for (u32 i = 0; i < unknown48; i++, entry++) {
      const DrResMdoLodParts *lodParts = &lodObj->unknown00[entry->unknown02];
      f32 lodAlpha = lodParts->unknown10;
      if (lodParts->unknown14 & 0x10) {
        unknown38[i >> 5] |= 1 << (i & 0x1f);
      } else {
        unknown38[i >> 5] &= ~(1 << (i & 0x1f));
      }
      if (entry->unknown00 != 0) {
        const DrResMdoMeshParts *meshParts = meshObj->getParts(entry->unknown00 - 1);
        f32 meshAlpha = (meshParts->unknown28 & 8) ? 0.0f : meshParts->unknown34;
        unknown30[i] = lodAlpha * (meshAlpha * alpha);
      } else {
        unknown30[i] = lodAlpha * alpha;
      }
    }
  } else {
    for (u32 i = 0; i < unknown48; i++, entry++) {
      const DrResMdoLodParts *lodParts = &lodObj->unknown00[entry->unknown02];
      f32 lodAlpha = lodParts->unknown10;
      if (lodParts->unknown14 & 0x10) {
        unknown38[i >> 5] |= 1 << (i & 0x1f);
      } else {
        unknown38[i >> 5] &= ~(1 << (i & 0x1f));
      }
      unknown30[i] = lodAlpha * alpha;
    }
  }
  updateInstace();
}

void DrResMdoAlpTbl::update() { updateInstace(); }

void DrResMdoAlpTbl::release(DrResMdoAlpTbl *&table) {
  if (table != nullptr) {
    table->~DrResMdoAlpTbl();
    table = nullptr;
  }
}

DrResMdoAlpTbl::DrResMdoAlpTbl() {}

int DrResMdoAlpTbl::calcCntWorkSize(u32 count) {
  u32 aligned = count + (-count & 3);
  u32 words = count >> 5;
  if ((count & 0x1f) != 0) {
    words++;
  }
  return (aligned + words) * 4 + 0x50;
}

int DrResMdoAlpTbl::calcWorkSize(const u8 *resource) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(resource);
  if (!(header->unknown02 & 4)) {
    return 0;
  }
  const unknown002 *data = reinterpret_cast<const unknown002 *>(resource + header->unknown90);
  s32 count = data->unknown04;
  s32 padding = (4 - count % 4) % 4;
  s32 words = count / 32;
  if ((count & 0x1f) != 0) {
    words++;
  }
  return (count + words + padding) * sizeof(u32) + sizeof(DrResMdoAlpTbl);
}

int DrResMdoAlpTbl::create(u8 *work, const u8 *resource) {
  DrResMdoAlpTbl *table = new (work) DrResMdoAlpTbl;
  return table->setup(resource, work + sizeof(DrResMdoAlpTbl));
}

int DrResMdoAlpTbl::createCnt(u8 *work, u32 count) {
  DrResMdoAlpTbl *table = new (work) DrResMdoAlpTbl;
  return table->setupCnt(count, work + sizeof(DrResMdoAlpTbl));
}

} // namespace ml
