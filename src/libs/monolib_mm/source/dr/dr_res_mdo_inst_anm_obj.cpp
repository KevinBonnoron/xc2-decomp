#include "dr/dr_res_mdo_inst_anm_obj.h"

#include <string.h>

#include "dr/dr_man.h"
#include "dr/dr_mdo_ctl_pos.h"
#include "dr/dr_res_mdo_pos.h"
#include "grlib/shd_util.h"
#include "mm_math/mm_vec3.h"

namespace ml {

DrResMdoPosInstAnm::DrResMdoPosInstAnm(const MdsInstAnmObj *anm, const u8 *data, const MdsPosKeepData *keep) : unknown00(anm), unknown08(data), unknown10(keep) {
  unknown150 = 0;
  unknown154 = 0;
  unknown152 = anm->unknown3e;
}

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

f32 DrResMdoPosInstAnm::getHermiteAttr(const MdsInstAnmInf *inf, f32 frame) const {
  const unknown095 *keys = reinterpret_cast<const unknown095 *>(unknown08 + inf->unknown00);
  if (frame <= inf->unknown08) {
    return keys[0].unknown08;
  }
  if (frame >= inf->unknown0a) {
    return keys[inf->unknown06 - 1].unknown08;
  }
  for (u32 i = 1; i < inf->unknown06; i++) {
    const unknown095 *key = &keys[i];
    f32 keyFrame = key->unknown0c;
    if (frame < keyFrame) {
      const unknown095 *prev = &keys[i - 1];
      if (prev->unknown0f & 1) {
        return prev->unknown08;
      }
      f32 prevFrame = prev->unknown0c;
      f32 length = keyFrame - prevFrame;
      f32 t = (frame - prevFrame) / length;
      f32 t2 = t * t;
      f32 t3 = t * t2;
      f32 h00 = 2.0f * t3 - 3.0f * t2 + 1.0f;
      f32 h10 = t3 - 2.0f * t2 + t;
      f32 h01 = 3.0f * t2 - 2.0f * t3;
      f32 h11 = t3 - t2;
      return prev->unknown08 * h00 + prev->unknown00 * h10 + key->unknown08 * h01 + key->unknown04 * h11;
    }
  }
  return 0.0f;
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
  unknown08.isLoop = info->flags & MdsInstObjPosData::FLAG_UNKNOWN_0;
  if (info->flags & MdsInstObjPosData::FLAG_UNKNOWN_9 && info->unknown08 != 0) {
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
  if (unknown18->flags & MdsInstObjPosData::FLAG_UNKNOWN_5) {
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
  return DrMan::getIns()->isGblIdx(unknown18->unknown08);
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
  if (unknown18->flags & MdsInstObjPosData::FLAG_UNKNOWN_7 && m_switchID != id) {
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
  const unknown044 &entry = unknown68[index == -1 ? 0 : index];
  unknown08.unknown00 = (entry.unknown00 & unknown044::FLAG_UNKNOWN_1) == 0 ? unknown08.unknown00 & ~FLAG_UNKNOWN_2 : unknown08.unknown00 | FLAG_UNKNOWN_2;
  if (entry.unknown00 & unknown044::FLAG_UNKNOWN_0) {
    u16 startFrame = entry.unknown04_0;
    u16 maxFrame = entry.unknown06_0 - entry.unknown04_0;
    if (unknown18->flags & MdsInstObjPosData::FLAG_UNKNOWN_3) {
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
    if (unknown18->flags & MdsInstObjPosData::FLAG_UNKNOWN_4) {
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
  if (unknown18->flags & MdsInstObjPosData::FLAG_UNKNOWN_4) {
    unknown30->getMatrix(matrix);
  } else {
    DrResMdoInstPartsObj::getMatrix(matrix);
  }
}

void DrResMdoInstPartsAnm::getAnmMatrix(mm::Mat44 &matrix) const {
  if (unknown18->flags & MdsInstObjPosData::FLAG_UNKNOWN_4) {
    unknown30->getAnmMatrix(&matrix, m_posFrame * unknown58);
  } else {
    DrResMdoInstPartsObj::getMatrix(matrix);
  }
}

void DrResMdoInstPartsAnm::setMatrix(const mm::Mat44 &matrix) {
  if (unknown18->flags & MdsInstObjPosData::FLAG_UNKNOWN_4) {
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

namespace ml {

DrResMdoInstAnmObj::DrResMdoInstAnmObj() { release(); }

int DrResMdoInstAnmObj::getWorkSize(const u8 *data) {
  const unknown045 *header = reinterpret_cast<const unknown045 *>(data);
  u32 size = header->unknown08 * 0x78 + header->unknown04 * 8 + (header->unknown28 + header->unknown34) * 0x30 + header->unknown18 * 0x28;
  u32 align = (0x10 - (size & 0xf)) & 0xf;
  return size + header->unknown18 * 0x160 + align;
}
int DrResMdoInstAnmObj::getObjIdx(const char *name) {
  if (unknown00 != nullptr) {
    int count = static_cast<int>(unknown00->unknown04);
    for (int i = 0; i < count; i++) {
      DrResMdoInstPartsObj *object = unknown08[i];
      if (strcmp(object->unknown10 + object->unknown18->unknown00, name) == 0) {
        return i;
      }
    }
  }
  return -1;
}
void DrResMdoInstAnmObj::release() {
  unknown20 = nullptr;
  unknown28 = nullptr;
  unknown10 = nullptr;
  unknown18 = nullptr;
  unknown00 = nullptr;
  unknown08 = nullptr;
}

void DrResMdoInstAnmObj::update() {
  if (unknown00 != nullptr) {
    for (int i = 0; i < unknown00->unknown08; i++) {
      unknown10[i].update();
    }
  }
}

void DrResMdoInstAnmObj::setupLink(DrResMdoPos *pos) const {
  if (unknown00 != nullptr) {
    int index = unknown00->unknown18;
    for (int i = 0; i < unknown00->unknown1c; i++, index++) {
      pos[unknown08[index]->unknown18->unknown04].unknown18 = index;
    }
    index = unknown00->unknown08;
    for (int i = 0; i < unknown00->unknown28; i++, index++) {
      pos[unknown08[index]->unknown18->unknown04].unknown18 = index;
    }
  }
}

void DrResMdoInstAnmObj::setupLink(DrResMdoPos *pos, int posStart, int posCount, int switchStart, int switchCount) const {
  if (unknown00 != nullptr) {
    int index = unknown00->unknown18 + posStart;
    for (int i = 0; i < posCount; i++, index++) {
      pos[unknown08[index]->unknown18->unknown04].unknown18 = index;
    }
    index = unknown00->unknown08 + switchStart;
    for (int i = 0; i < switchCount; i++, index++) {
      pos[unknown08[index]->unknown18->unknown04].unknown18 = index;
    }
  }
}

void DrResMdoInstAnmObj::getUniformOldMat(f32 *work, const DrResMdoPos *pos, const mm::Mat44 &matrix) {
  mm::Mat44 result;
  if (pos->unknown1e & DrResMdoPos::FLAG_UNKNOWN_12) {
    result.unknown009(unknown28[pos->unknown18].unknown110, matrix);
  } else {
    result.unknown009(pos->unknown08->unknown00, matrix);
  }
  grlib::ShdMat44TransposeMat44(work, result);
}

} // namespace ml
