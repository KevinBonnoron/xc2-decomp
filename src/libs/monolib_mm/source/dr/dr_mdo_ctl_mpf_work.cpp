#include "dr/dr_mdo_ctl_mpf_work.h"

#include <math.h>

#include "dr/dr_mdo_mpf_man.h"
#include "dr/dr_res_mdo_pnt_alpha.h"
#include "ml/rand.h"

namespace ml {

void DrMdoCtlMpfWindCalc::init() {
  for (int i = 0; i < 3; i++) {
    unknown00[i] = mm::Vec3(0.0f, i, 0.0f);
    unknown30[i] = mm::Vec3::zero;
  }
  unknown70 = mm::Mat44::identity;
  unknownb0 = mm::Mat44::identity;
  f32 x = (mtRand() % 100) * 0.01f - 0.5f;
  f32 z = (mtRand() % 100) * 0.01f - 0.5f;
  unknown60 = mm::Vec3(x, 0.0f, z);
  if (!(fabsf(unknown60.x) <= 0.000001f && fabsf(unknown60.y) <= 0.000001f && fabsf(unknown60.z) <= 0.000001f)) {
    unknown60.unknown001();
  } else {
    unknown60 = mm::Vec3(0.0f, 0.0f, 1.0f);
  }
}

DrMdoCtlMpfWork::DrMdoCtlMpfWork() {}

int DrMdoCtlMpfWork::calcRenderListWork(int count, const MdsMpfObjData *data) {
  int size = count * 0x1d0;
  return size + DrResMdoPntAlphaMan::getWrkSize(0x80);
}

void DrMdoCtlMpfWork::changeMemWork(const MdsMpfObjData *data) { m_mdsMpfObjData = data; }

u32 DrMdoCtlMpfWork::getObjChk(int index) { return m_wkMpfObjSelect[index].m_objChk; }

void DrMdoCtlMpfWork::mpf_countSet(_wkMpfObjBuff *buff, const MdsMpfPosData *pos, int index) {
  buff->unknown08[buff->unknown00] = pos;
  if (buff->unknown00++ > 62) {
    buff->unknown18.unknown00 = &DrMdoCtlMpfWork::mpf_changeSet;
  }
}

void DrMdoCtlMpfWork::auto_countSet(_wkMpfObjBuff *buff, const _MPFWorkAutoInf *work, int index) {
  buff->unknown08[buff->unknown00] = work;
  if (buff->unknown00++ > 62) {
    buff->unknown18.unknown00_1 = &DrMdoCtlMpfWork::auto_changeSet;
  }
}

void DrMdoCtlMpfWork::mpf_alpha_countSet(_wkMpfAlphaObjBuff *buff, const MdsMpfPosData *pos, int index, f32 alpha) {
  buff->unknown08[buff->unknown00] = pos;
  buff->unknown10[buff->unknown00] = static_cast<u8>(alpha * 255.0f);
  if (buff->unknown00++ > 14) {
    buff->unknown20.unknown00 = &DrMdoCtlMpfWork::mpf_alpha_changeSet;
  }
}

void DrMdoCtlMpfWork::auto_alpha_countSet(_wkMpfAlphaObjBuff *buff, const _MPFWorkAutoInf *work, int index) {
  buff->unknown08[buff->unknown00] = work;
  if (buff->unknown00++ > 14) {
    buff->unknown20.unknown00_1 = &DrMdoCtlMpfWork::auto_alpha_changeSet;
  }
}

void DrMdoCtlMpfWork::mpf_alpha_changeSet(_wkMpfAlphaObjBuff *buff, const MdsMpfPosData *pos, int index, f32 alpha) {
  unknown734 *chunk = static_cast<unknown734 *>(m_drMdoMpfMan->unknown001(sizeof(unknown734)));
  if (chunk != nullptr) {
    chunk->unknown00.m_wkMpfAlphaObjBuff.unknown08 = chunk->unknown00.unknown30;
    chunk->unknown00.m_wkMpfAlphaObjBuff.unknown10 = chunk->unknownb0;
    chunk->unknown00.m_wkMpfAlphaObjBuff.m_wkMpfAlphaObjBuff = nullptr;
    chunk->unknown00.unknown30[0] = pos;
    chunk->unknownb0[0] = static_cast<u8>(alpha * 255.0f);
    chunk->unknown00.m_wkMpfAlphaObjBuff.unknown00 = 1;
    chunk->unknown00.m_wkMpfAlphaObjBuff.unknown20.unknown00 = &DrMdoCtlMpfWork::mpf_alpha_countSet;
    m_wkMpfObjSelect[index].m_wkMpfAlphaObjBuff = &chunk->unknown00.m_wkMpfAlphaObjBuff;
    buff->m_wkMpfAlphaObjBuff = &chunk->unknown00.m_wkMpfAlphaObjBuff;
  } else {
    m_wkMpfObjSelect[index].m_objChk--;
    buff->unknown00 = 0;
  }
}

void DrMdoCtlMpfWork::auto_alpha_changeSet(_wkMpfAlphaObjBuff *buff, const _MPFWorkAutoInf *work, int index) {
  unknown733 *chunk = static_cast<unknown733 *>(m_drMdoMpfMan->unknown001(sizeof(unknown733)));
  if (chunk != nullptr) {
    chunk->m_wkMpfAlphaObjBuff.unknown08 = chunk->unknown30;
    chunk->m_wkMpfAlphaObjBuff.m_wkMpfAlphaObjBuff = nullptr;
    chunk->unknown30[0] = work;
    chunk->m_wkMpfAlphaObjBuff.unknown00 = 1;
    chunk->m_wkMpfAlphaObjBuff.unknown20.unknown00_1 = &DrMdoCtlMpfWork::auto_alpha_countSet;
    m_wkMpfObjSelect[index].m_wkMpfAlphaObjBuff = &chunk->m_wkMpfAlphaObjBuff;
    buff->m_wkMpfAlphaObjBuff = &chunk->m_wkMpfAlphaObjBuff;
  } else {
    m_wkMpfObjSelect[index].m_objChk--;
    buff->unknown00 = 0;
  }
}

void DrMdoCtlMpfWork::mpf_fastSet(_wkMpfObjBuff *buff, const MdsMpfPosData *pos, int index) {
  const void **list = static_cast<const void **>(m_drMdoMpfMan->unknown001(0x200));
  buff->unknown08 = list;
  if (list != nullptr) {
    list[0] = pos;
    buff->unknown18.unknown00 = &DrMdoCtlMpfWork::mpf_countSet;
    buff->unknown00 = 1;
  } else {
    m_wkMpfObjSelect[index].m_objChk--;
    buff->unknown00 = 0;
  }
}

void DrMdoCtlMpfWork::auto_fastSet(_wkMpfObjBuff *buff, const _MPFWorkAutoInf *work, int index) {
  const void **list = static_cast<const void **>(m_drMdoMpfMan->unknown001(0x200));
  buff->unknown08 = list;
  if (list != nullptr) {
    list[0] = work;
    buff->unknown18.unknown00_1 = &DrMdoCtlMpfWork::auto_countSet;
    buff->unknown00 = 1;
  } else {
    m_wkMpfObjSelect[index].m_objChk--;
    buff->unknown00 = 0;
  }
}

void DrMdoCtlMpfWork::mpf_alpha_fastSet(_wkMpfAlphaObjBuff *buff, const MdsMpfPosData *pos, int index, f32 alpha) {
  unknown735 *chunk = static_cast<unknown735 *>(m_drMdoMpfMan->unknown001(sizeof(unknown735)));
  buff->unknown08 = chunk->unknown00;
  buff->unknown10 = chunk->unknown80;
  if (chunk != nullptr) {
    chunk->unknown00[0] = pos;
    buff->unknown10[0] = static_cast<u8>(alpha * 255.0f);
    buff->unknown00 = 1;
    buff->unknown20.unknown00 = &DrMdoCtlMpfWork::mpf_alpha_countSet;
  } else {
    m_wkMpfObjSelect[index].m_objChk--;
    buff->unknown00 = 0;
  }
}

void DrMdoCtlMpfWork::auto_alpha_fastSet(_wkMpfAlphaObjBuff *buff, const _MPFWorkAutoInf *work, int index) {
  const void **list = static_cast<const void **>(m_drMdoMpfMan->unknown001(0x80));
  buff->unknown08 = list;
  if (list != nullptr) {
    list[0] = work;
    buff->unknown20.unknown00_1 = &DrMdoCtlMpfWork::auto_alpha_countSet;
    buff->unknown00 = 1;
  } else {
    m_wkMpfObjSelect[index].m_objChk--;
    buff->unknown00 = 0;
  }
}

void DrMdoCtlMpfWork::stockObj(int index, const MdsMpfPosData *pos) {
  m_wkMpfObjSelect[index].m_objChk++;
  m_wkMpfObjSelect[index].unknown00[pos->unknown0f & 0xf]++;
  (this->*m_wkMpfObjSelect[index].m_wkMpfObjBuff->unknown18.unknown00)(m_wkMpfObjSelect[index].m_wkMpfObjBuff, pos, index);
}

void DrMdoCtlMpfWork::stockObj(int index, const MdsMpfPosData *pos, f32 alpha) {
  m_wkMpfObjSelect[index].m_objChk++;
  m_wkMpfObjSelect[index].unknown10[pos->unknown0f & 0xf]++;
  (this->*m_wkMpfObjSelect[index].m_wkMpfAlphaObjBuff->unknown20.unknown00)(m_wkMpfObjSelect[index].m_wkMpfAlphaObjBuff, pos, index, alpha);
}

} // namespace ml
