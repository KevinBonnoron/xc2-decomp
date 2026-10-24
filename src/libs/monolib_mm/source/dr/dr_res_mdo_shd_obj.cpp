#include "dr/dr_res_mdo_shd_obj.h"

#include <string.h>

namespace ml {

static const MdsDecShdHeader *getDecShdHeader(const u8 *resource) { return reinterpret_cast<const MdsDecShdHeader *>(resource + *reinterpret_cast<const u32 *>(resource + 0x88)); }

static const MdsDecShdInfo *getDecShdInfos(const MdsDecShdHeader *header) { return reinterpret_cast<const MdsDecShdInfo *>(reinterpret_cast<const u8 *>(header) + header->infoOfs); }

DrResMdoShdObj::DrResMdoShdObj() : unknown00(nullptr), unknown08(nullptr), unknown10(0) {}

DrResMdoShdObj::~DrResMdoShdObj() {}

u32 DrResMdoShdObj::getDecShdID(u32 index) const {
  if (index < unknown10) {
    return unknown08[index].unknown00->unknown04;
  }
  return 0;
}

int DrResMdoShdObj::getDecShdIdx(const char *name) const {
  for (u32 i = 0; i < unknown10; i++) {
    if (strcmp(reinterpret_cast<const char *>(unknown00) + unknown08[i].unknown00->unknown00, name) == 0) {
      return i;
    }
  }
  return -1;
}

int DrResMdoShdObj::getDecShdIdx(u32 id) const {
  for (u32 i = 0; i < unknown10; i++) {
    if (unknown08[i].unknown00->unknown04 == id) {
      return i;
    }
  }
  return -1;
}

void DrResMdoShdObj::setDecShdParm(u32 index, u32 parm) {
  if (index < unknown10) {
    unknown08[index].unknown10 = parm;
  }
}

u32 DrResMdoShdObj::getDecShdParm(u32 index) const {
  if (index < unknown10) {
    return unknown08[index].unknown10;
  }
  return 0;
}

u32 DrResMdoShdObj::getDecShdParmMax(u32 index) const {
  if (index < unknown10) {
    return unknown08[index].unknown00->unknown08;
  }
  return 0;
}

int DrResMdoShdObj::calcWorkSize(const u8 *resource) {
  const MdsDecShdHeader *header = getDecShdHeader(resource);
  int size = 0;
  const MdsDecShdInfo *info = getDecShdInfos(header);
  for (int i = 0; i < header->num; i++, info++) {
    size += info->unknown10;
  }
  return size + (-size & 3) + header->num * sizeof(DrResMdoDecShd) + sizeof(DrResMdoShdObj);
}

void DrResMdoShdObj::release(DrResMdoShdObj *&shdObj) {
  if (shdObj != nullptr) {
    shdObj = nullptr;
  }
}

} // namespace ml
