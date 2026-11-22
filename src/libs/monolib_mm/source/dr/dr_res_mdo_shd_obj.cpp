#include "dr/dr_res_mdo_shd_obj.h"

#include <new>
#include <string.h>

#include "dr/dr_shd_mdo_dec_ext_tbl.h"
#include "dr/dr_shd_mdo_ext_tbl_obj.h"
#include "grlib/cglib_dec_shader.h"

namespace ml {

static const unknown042 *getDecShdHeader(const u8 *resource) { return reinterpret_cast<const unknown042 *>(resource + *reinterpret_cast<const u32 *>(resource + 0x88)); }

static const unknown041 *getDecShdInfos(const unknown042 *header) { return reinterpret_cast<const unknown041 *>(reinterpret_cast<const u8 *>(header) + header->infoOfs); }

DrResMdoShdObj::DrResMdoShdObj() : unknown00(nullptr), unknown08(nullptr), unknown10(0) {}

DrResMdoShdObj::~DrResMdoShdObj() {}

int DrResMdoShdObj::setup(const u8 *resource, u8 *work) {
  const unknown042 *header = getDecShdHeader(resource);
  unknown00 = header;
  const unknown041 *info = getDecShdInfos(header);
  unknown08 = reinterpret_cast<unknown043 *>(work);
  unknown10 = header->num;
  u8 *decl = work + header->num * sizeof(unknown043);
  u32 size = 0;
  for (int i = 0; i < header->num; i++, info++) {
    unknown043 shd = {info, decl + size, 1, 1};
    unknown08[i] = shd;
    size += info->unknown10;
  }
  return size + (-size & 3) + header->num * sizeof(unknown043) + sizeof(DrResMdoShdObj);
}

void DrResMdoShdObj::bindShader(DrShdMdoExtTblObj *extTblObj) {
  const unknown042 *header = unknown00;
  const unknown041 *info = getDecShdInfos(header);
  for (int i = 0; i < header->num; i++, info++) {
    const char *name = reinterpret_cast<const char *>(unknown00) + info->unknown00;
    u8 *decl = unknown08[i].unknown08;
    const u16 *shaderIdx = reinterpret_cast<const u16 *>(reinterpret_cast<const u8 *>(unknown00) + info->unknown0c);
    for (int j = 0; j < info->unknown10; j++, shaderIdx++) {
      decl[j] = (extTblObj->m_drShdMdoDecExtTbl + *shaderIdx)->unknown00->getDeclarationOfs(name);
    }
  }
}

bool DrResMdoShdObj::update(DrShdMdoExtTblObj *extTblObj) {
  bool isUpdate = false;
  const unknown041 *info = getDecShdInfos(unknown00);
  for (u32 i = 0; i < unknown10; i++, info++) {
    u32 parm = unknown08[i].unknown10;
    if (parm != unknown08[i].unknown14) {
      unknown08[i].unknown14 = parm;
      const u8 *decl = unknown08[i].unknown08;
      const u16 *shaderIdx = reinterpret_cast<const u16 *>(reinterpret_cast<const u8 *>(unknown00) + info->unknown0c);
      for (int j = 0; j < info->unknown10; j++, shaderIdx++) {
        (extTblObj->m_drShdMdoDecExtTbl + *shaderIdx)->setDeclarationIdx(decl[j], parm);
      }
      isUpdate = true;
    }
  }
  return isUpdate;
}

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
  const unknown042 *header = getDecShdHeader(resource);
  int size = 0;
  const unknown041 *info = getDecShdInfos(header);
  for (int i = 0; i < header->num; i++, info++) {
    size += info->unknown10;
  }
  return size + (-size & 3) + header->num * sizeof(unknown043) + sizeof(DrResMdoShdObj);
}

int DrResMdoShdObj::create(u8 *work, const u8 *resource) {
  DrResMdoShdObj *shdObj = new (work) DrResMdoShdObj();
  return shdObj->setup(resource, work + sizeof(DrResMdoShdObj));
}

void DrResMdoShdObj::release(DrResMdoShdObj *&shdObj) {
  if (shdObj != nullptr) {
    shdObj = nullptr;
  }
}

} // namespace ml
