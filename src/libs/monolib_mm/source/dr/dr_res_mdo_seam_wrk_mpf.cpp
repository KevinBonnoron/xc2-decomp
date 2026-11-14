#include "dr/dr_res_mdo_seam_wrk_mpf.h"

#include "dr/dr_mdo_ctl_mpf_auto.h"
#include "dr/dr_mdo_ctl_mpf_inst.h"
#include "dr/dr_mdo_ctl_mpf_work.h"
#include "dr/dr_mdo_ctl_seam_mpf_map.h"
#include "dr/dr_res_mdo_seam_res.h"
#include "dr/dr_res_mdo_seam_wrk_pos_mpf.h"
#include "mtl/mem_manager.h"

namespace ml {
struct MdsMpfAutoPosData;
struct MdsMpfAutoPosTree;
struct MdsMpfAutoTree;

f32 DrResMdoSeamWrkMpf::SEAM_MPFMAP_READ_CHECK = 60.0f;

DrResMdoSeamWrkMpf::DrResMdoSeamWrkMpf()
    : unknown18(nullptr), unknown4c(0), unknown54(0), unknown56(0), unknown58(0), unknown5c(0), unknown60(0), unknown64(0), unknown68(0), unknown6c(0), unknown70(nullptr), unknown78(nullptr),
      unknownc0(nullptr), unknownc8(nullptr), unknownd0(nullptr), unknownd8(nullptr), unknowne8(0) {}

DrResMdoSeamWrkMpf::~DrResMdoSeamWrkMpf() { release(); }

void DrResMdoSeamWrkMpf::release() {
  if (unknown70 != nullptr) {
    unknownc8->autoMpfRelease();
    unknownc8->~DrMdoCtlMpfAuto();
    unknownc8 = nullptr;
    unknownd0 = nullptr;
    unknownc0 = nullptr;
    if (unknown70 != nullptr) {
      mtl::MemManager::deallocate(unknown70, 0, false);
      unknown70 = nullptr;
    }
    if (unknown78 != nullptr) {
      mtl::MemManager::deallocate(unknown78, 0, false);
      unknown78 = nullptr;
    }
  }
  unknown18 = nullptr;
  unknown54 = 0;
}

void DrResMdoSeamWrkMpf::changeMemCall() {
  const MdsSeamMpfMapHead *head = reinterpret_cast<const MdsSeamMpfMapHead *>(unknown18->m_buffer);
  unknown30 = head;
  const u8 *data = reinterpret_cast<const u8 *>(head) + head->unknown08;
  const unknown001 *mpf = reinterpret_cast<const unknown001 *>(data);
  unknown38 = reinterpret_cast<const MdsMpfObjData *>(data + mpf->unknown04);
  unknown40 = reinterpret_cast<const unknown002 *>(reinterpret_cast<const u8 *>(head) + head->unknown1c);
  unknownd0->setupInstMpf(data);
  unknownc0->changeMemWork(unknown38);
  if (mpf->unknown1c != 0) {
    unknownc8->changeMemAutoMpf(data, data + mpf->unknown1c);
  }
}

void DrResMdoSeamWrkMpf::releaseCache(DrMdoCtlSeamMpfMap *ctl) {
  for (int i = 0; i < unknown50; i++) {
    if ((unknown80[i >> 5] & (1 << (i & 0x1f))) != 0 && unknownd8[i].unknown20 != nullptr) {
      ctl->releaseFreeSeamMemObj(unknownd8[i].unknown20);
      unknownd8[i].unknown20 = nullptr;
    }
  }
  for (int i = 0; i < unknown58; i++) {
    ctl->releaseFreeSeamMemObj(unknownb8[i]);
  }
  unknown58 = 0;
  release();
}

void DrResMdoSeamWrkMpf::beginCalc() {
  unknown48 = 0;
  unknown4e = 0;
  unknown60 = 0;
  unknown64 = 0;
  unknown68 = 0;
  unknown6c = 0;
}

void DrResMdoSeamWrkMpf::calcCacheInfo() {
  for (int i = 0; i < unknown54; i++) {
    DrResMdoSeamWrkPosMpf *pos = unknowne0[i];
    if ((pos->unknown20->unknown24 & 2) != 0) {
      pos->changeMemCall();
    }
  }
  for (int i = 0; i < unknown58; i++) {
    if ((unknownb8[i]->unknown24 & 2) != 0) {
      setupMpfPoliWork(i);
    }
  }
}

void DrResMdoSeamWrkMpf::calcMpfMatSetup(DrCalcViewWork *view, grlib::CGLibVtxInstans *instans) {
  const MdsMpfObjData *obj = unknown38;
  for (int i = 0; i < unknown52; i++, obj++) {
    if (unknownc0->getObjChk(i) != 0) {
      unknown48 |= 1;
      unknown4e++;
      if (obj->unknown06 == 1 || obj->unknown06 == 3) {
        unknownc0->createAutoList(i, view, instans);
      } else {
        unknownc0->createPosList(i, instans);
      }
    }
  }
}

u32 DrResMdoSeamWrkPosMpf::getDataSize() const {
  if (unknown20 != nullptr) {
    return unknown20->m_size;
  }
  return 0;
}

void DrResMdoSeamWrkMpf::setEtcMpfCache(int id, DrResMdoSeamMemObj *memObj) {
  const unknown002 *entry = unknown40;
  for (int i = 0; i < unknown50; i++, entry++) {
    if (entry->unknown00 == id) {
      unknown80[i >> 5] |= 1 << (i & 0x1f);
      unknownd8[i].setupMpfEtcPos(i, memObj);
      unknowne0[unknown54] = &unknownd8[i];
      unknown54++;
      return;
    }
  }
}

void DrResMdoSeamWrkPosMpf::setupMpfEtcPos(int index, DrResMdoSeamMemObj *memObj) {
  unknown20 = memObj;
  unknown28 = index;
  const u8 *data = memObj->m_buffer;
  const unknown001 *header = reinterpret_cast<const unknown001 *>(data);
  unknown10 = data;
  unknown00 = data + header->unknown04;
  unknown08 = data + header->unknown0c;
  unknown18 = header->unknown10;
}

void DrResMdoSeamWrkMpf::setMpfPoliCache(int id, DrResMdoSeamMemObj *memObj) {
  const DrMdoCtlMpfAuto::unknown001 *autoHead = unknownc8->unknown00;
  const unknown003 *poli = reinterpret_cast<const unknown003 *>(reinterpret_cast<const u8 *>(autoHead) + autoHead->unknown5c);
  const unknown004 *entry = reinterpret_cast<const unknown004 *>(reinterpret_cast<const u8 *>(poli) + poli->unknown08);
  for (int i = 0; i < poli->unknown0c; i++, entry++) {
    if (entry->unknown00 == id) {
      unknown88[i >> 5] |= 1 << (i & 0x1f);
      unknownb8[unknown58] = memObj;
      unknown98[unknown58] = i;
      setupMpfPoliWork(unknown58);
      unknown58++;
      return;
    }
  }
}

void DrResMdoSeamWrkMpf::setupMpfPoliWork(int index) {
  _wkMpfAutoBuff *buff = unknownb0[index];
  const unknown005 *data = reinterpret_cast<const unknown005 *>(unknownb8[index]->m_buffer);
  buff->unknown00 = data->unknown24;
  buff->unknown08 = data->unknown2c;
  buff->unknown04 = data->unknown28;
  buff->unknown0c = data->unknown30;
  buff->unknown10 = reinterpret_cast<const u8 *>(data) + data->unknown00;
  buff->unknown18 = reinterpret_cast<const u8 *>(data) + data->unknown04;
  buff->unknown20 = reinterpret_cast<const u8 *>(data) + data->unknown08;
  buff->unknown28 = reinterpret_cast<const u8 *>(data) + data->unknown0c;
  buff->unknown30 = reinterpret_cast<const u8 *>(data) + data->unknown10;
  if (data->unknown14 == 0) {
    buff->unknown38 = nullptr;
  } else {
    buff->unknown38 = reinterpret_cast<const MdsMpfAutoTree *>(reinterpret_cast<const u8 *>(data) + data->unknown14);
  }
  buff->unknown40 = reinterpret_cast<const u32 *>(reinterpret_cast<const u8 *>(data) + data->unknown18);
  buff->unknown48 = reinterpret_cast<const u32 *>(reinterpret_cast<const u8 *>(data) + data->unknown1c);
  buff->unknown50 = reinterpret_cast<const f32 *>(reinterpret_cast<const u8 *>(data) + data->unknown20);
  if (data->unknown34 != 0) {
    buff->unknown58 = reinterpret_cast<const MdsMpfAutoPosData *>(reinterpret_cast<const u8 *>(data) + data->unknown34);
    buff->unknown60 = reinterpret_cast<const MdsMpfAutoPosTree *>(reinterpret_cast<const u8 *>(data) + data->unknown38);
    buff->unknown68 = reinterpret_cast<const u32 *>(reinterpret_cast<const u8 *>(data) + data->unknown3c);
  } else {
    buff->unknown58 = nullptr;
  }
}

void DrResMdoSeamWrkPosMpf::changeMemCall() {
  const u8 *data = unknown20->m_buffer;
  const unknown001 *header = reinterpret_cast<const unknown001 *>(data);
  unknown10 = data;
  unknown00 = data + header->unknown04;
  unknown08 = data + header->unknown0c;
}

} // namespace ml
