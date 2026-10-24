#include "dr/dr_res_mdo_inst_anm_obj.h"

#include <string.h>

#include "dr/dr_man.h"
#include "mm_math/mm_vec3.h"

namespace ml {

void DrResMdoPosInstAnm::setMatrix(const mm::Mat44 &matrix) {
  memcpy(&unknown90[DrMan::s_nDblStockIdx], &matrix, sizeof(mm::Mat44));
  unknown150 |= 1 << DrMan::s_nDblStockIdx;
}

void DrResMdoPosInstAnm::getMatrix(mm::Mat44 &matrix) const {
  if (unknown150 & (1 << DrMan::s_nDblStockIdx)) {
    memcpy(&matrix, &unknown90[DrMan::s_nDblStockIdx], sizeof(mm::Mat44));
  } else if (unknown150 & (1 << DrMan::s_nDblMemIdx)) {
    memcpy(&matrix, &unknown90[DrMan::s_nDblMemIdx], sizeof(mm::Mat44));
  } else {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        matrix.rows[i][j] = unknown20.rows[i][j];
      }
    }
  }
}

void DrResMdoPosInstAnm::setAnmFrame(u16 startFrame, u16 maxFrame) {
  unknown154 = startFrame;
  unknown152 = maxFrame;
}

void DrResMdoPosInstAnm::anmInsPosParm_TranX(mm::Vec3 *transform, f32 value) { transform[0].x = value; }

void DrResMdoPosInstAnm::anmInsPosParm_TranY(mm::Vec3 *transform, f32 value) { transform[0].y = value; }

void DrResMdoPosInstAnm::anmInsPosParm_TranZ(mm::Vec3 *transform, f32 value) { transform[0].z = value; }

void DrResMdoPosInstAnm::anmInsPosParm_RotX(mm::Vec3 *transform, f32 value) { transform[1].x = value; }

void DrResMdoPosInstAnm::anmInsPosParm_RotY(mm::Vec3 *transform, f32 value) { transform[1].y = value; }

void DrResMdoPosInstAnm::anmInsPosParm_RotZ(mm::Vec3 *transform, f32 value) { transform[1].z = value; }

void DrResMdoPosInstAnm::anmInsPosParm_SclX(mm::Vec3 *transform, f32 value) { transform[2].x = value; }

void DrResMdoPosInstAnm::anmInsPosParm_SclY(mm::Vec3 *transform, f32 value) { transform[2].y = value; }

void DrResMdoPosInstAnm::anmInsPosParm_SclZ(mm::Vec3 *transform, f32 value) { transform[2].z = value; }

DrResMdoInstPartsObj::DrResMdoInstPartsObj(const u8 *data, const MdsInstObjPosData *info) : unknown10(reinterpret_cast<const char *>(data)), unknown18(info), unknown20(nullptr), unknown28(1.0f) {
  unknown08.unknown00 = 0;
  unknown08.isLoop = info->flags & MdsInstObjPosData::FLAG_LOOP;
  if (info->flags & MdsInstObjPosData::FLAG_DISP_OFF && info->unknown08 != 0) {
    DrMan::getIns()->setGblIdx(unknown18->unknown08);
  }
}

void DrResMdoInstPartsObj::setDisp(bool disp) {
  if (unknown18->unknown08 != 0) {
    if (disp) {
      DrMan::getIns()->offGblIdx(unknown18->unknown08);
    } else {
      DrMan::getIns()->setGblIdx(unknown18->unknown08);
    }
  }
}

void DrResMdoInstPartsObj::getMatrix(mm::Mat44 &matrix) const {
  if (unknown18->flags & MdsInstObjPosData::FLAG_POS_MATRIX) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        matrix.rows[i][j] = unknown20->rows[i][j];
      }
    }
  }
}

bool DrResMdoInstPartsObj::isDisp() const {
  if (unknown18->unknown08 == 0) {
    return false;
  }
  DrMan *drMan = DrMan::getIns();
  s32 id = unknown18->unknown08;
  return drMan->unknown1d20[id >> 5] & (1 << (id & 31));
}

DrResMdoInstPartsAnm::DrResMdoInstPartsAnm(const u8 *data, const MdsInstObjPosData *info)
    : DrResMdoInstPartsObj(data, info), unknown30(nullptr), m_posFrame(0.0f), unknown44(0.0f), unknown48(0.0f), unknown4c(), unknown54(1.0f), unknown58(1.0f), unknown5c(0), unknown5e(0),
      unknown60(nullptr), unknown68(nullptr), m_switchMax(0) {
  m_switchID = 1;
  if (info->unknown0d != 0) {
    unknown54 = info->unknown0d * (1.0f / 255.0f) * 2.0f;
    unknown58 = 1.0f / unknown54;
  }
}

DrResMdoInstPartsAnm::~DrResMdoInstPartsAnm() {}

void DrResMdoInstPartsAnm::setNodeFrame(f32 frame) {
  unknown4c[DrMan::s_nDblStockIdx] = frame;
  unknown08.unknown00 |= 1 << DrMan::s_nDblStockIdx;
}

f32 DrResMdoInstPartsAnm::getNodeFrame() const {
  if (unknown08.unknown00 & (1 << DrMan::s_nDblStockIdx)) {
    return unknown4c[DrMan::s_nDblStockIdx];
  }
  if (unknown08.unknown00 & (1 << DrMan::s_nDblMemIdx)) {
    return unknown4c[DrMan::s_nDblMemIdx];
  }
  return unknown44;
}

void DrResMdoInstPartsAnm::setSwitchID(u8 id) {
  if (unknown18->flags & MdsInstObjPosData::FLAG_SWITCH && m_switchID != id) {
    m_switchID = id;
    updateSwitch();
  }
}

void DrResMdoInstPartsAnm::updateSwitch() {
  int index = -1;
  u8 switchMax = m_switchMax;
  for (int i = 0; i < switchMax; i++) {
    if (unknown68[i].unknown02 == m_switchID) {
      index = i;
      break;
    }
  }
  const MdsInstAnmSwitch &entry = unknown68[index == -1 ? 0 : index];
  unknown08.unknown00 = (entry.unknown00 & MdsInstAnmSwitch::FLAG_LOOP) == 0 ? unknown08.unknown00 & ~FLAG_LOOP : unknown08.unknown00 | FLAG_LOOP;
  if (entry.unknown00 & MdsInstAnmSwitch::FLAG_FRAME) {
    u16 startFrame = entry.unknown04_0;
    u16 maxFrame = entry.unknown06_0 - entry.unknown04_0;
    if (unknown18->flags & MdsInstObjPosData::FLAG_NODE_ANM) {
      unknown5c = startFrame;
      unknown5e = maxFrame;
      if (unknown08.unknown00 & (1 << DrMan::s_nDblStockIdx)) {
        if (getNodeMaxFrame() < unknown4c[DrMan::s_nDblStockIdx]) {
          unknown4c[DrMan::s_nDblStockIdx] = getNodeMaxFrame();
        }
        if (unknown4c[DrMan::s_nDblStockIdx] < 0.0f) {
          unknown4c[DrMan::s_nDblStockIdx] = 0.0f;
        }
        unknown48 = unknown4c[DrMan::s_nDblStockIdx];
      } else {
        if (getNodeMaxFrame() < unknown44) {
          unknown44 = getNodeMaxFrame();
        }
        if (unknown44 < 0.0f) {
          unknown44 = 0.0f;
        }
        unknown48 = unknown44;
      }
    }
    if (unknown18->flags & MdsInstObjPosData::FLAG_POS_ANM) {
      unknown30->setAnmFrame(startFrame, maxFrame);
    }
  }
}

u32 DrResMdoInstPartsAnm::getSwitchIndex(u32 index) const {
  if (index < m_switchMax) {
    return unknown68[index].unknown02;
  }
  return 0;
}

void DrResMdoInstPartsAnm::getMatrix(mm::Mat44 &matrix) const {
  if (unknown18->flags & MdsInstObjPosData::FLAG_POS_ANM) {
    unknown30->getMatrix(matrix);
  } else {
    DrResMdoInstPartsObj::getMatrix(matrix);
  }
}

void DrResMdoInstPartsAnm::getAnmMatrix(mm::Mat44 &matrix) const {
  if (unknown18->flags & MdsInstObjPosData::FLAG_POS_ANM) {
    unknown30->getAnmMatrix(&matrix, m_posFrame * unknown58);
  } else {
    DrResMdoInstPartsObj::getMatrix(matrix);
  }
}

void DrResMdoInstPartsAnm::setMatrix(const mm::Mat44 &matrix) {
  if (unknown18->flags & MdsInstObjPosData::FLAG_POS_ANM) {
    unknown30->setMatrix(matrix);
  }
}

void DrResMdoInstPartsAnm::setNodeAnmData(const MdsInstAnmNodeData *data) {
  unknown5e = data->unknown02;
  if (unknown18->unknown0c != 0) {
    unknown44 = unknown48 = unknown18->unknown0c * (1.0f / 255.0f) * data->unknown02;
  }
  if (data->unknown04 != 0) {
    unknown60 = reinterpret_cast<const MdsInstAnmParamInfo *>(unknown10 + data->unknown04);
    unknown08.isColiSkipData = true;
  }
}

void DrResMdoInstPartsAnm::setPosAnmData(DrResMdoPosInstAnm *posAnm, DrResMdoPos *pos) {
  unknown30 = posAnm;
  unknown38 = pos;
  if (unknown18->unknown0c != 0) {
    m_posFrame = unknown18->unknown0c * (1.0f / 255.0f) * posAnm->unknown152;
  }
  posAnm->setup(m_posFrame);
}

DrResMdoInstPartsGlbID::DrResMdoInstPartsGlbID(const u8 *data, const MdsInstObjPosData *info) : DrResMdoInstPartsObj(data, info) {}

DrResMdoInstPartsGlbID::~DrResMdoInstPartsGlbID() {}

} // namespace ml
