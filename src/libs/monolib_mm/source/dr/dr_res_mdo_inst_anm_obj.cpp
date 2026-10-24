#include "dr/dr_res_mdo_inst_anm_obj.h"

#include <string.h>

#include "dr/dr_man.h"
#include "mm_math/mm_vec3.h"

namespace ml {

void DrResMdoPosInstAnm::setMatrix(const mm::Mat44 &matrix) {
  memcpy(&m_dblMatrices[DrMan::s_nDblStockIdx], &matrix, sizeof(mm::Mat44));
  m_dblFlags |= 1 << DrMan::s_nDblStockIdx;
}

void DrResMdoPosInstAnm::getMatrix(mm::Mat44 &matrix) const {
  if (m_dblFlags & (1 << DrMan::s_nDblStockIdx)) {
    memcpy(&matrix, &m_dblMatrices[DrMan::s_nDblStockIdx], sizeof(mm::Mat44));
  } else if (m_dblFlags & (1 << DrMan::s_nDblMemIdx)) {
    memcpy(&matrix, &m_dblMatrices[DrMan::s_nDblMemIdx], sizeof(mm::Mat44));
  } else {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        matrix.rows[i][j] = m_matrix.rows[i][j];
      }
    }
  }
}

void DrResMdoPosInstAnm::setAnmFrame(u16 startFrame, u16 maxFrame) {
  m_startFrame = startFrame;
  m_maxFrame = maxFrame;
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

DrResMdoInstPartsObj::DrResMdoInstPartsObj(const u8 *data, const MdsInstObjPosData *info) : m_names(reinterpret_cast<const char *>(data)), m_info(info), m_matrix(nullptr), m_alpha(1.0f) {
  m_flags.all = 0;
  m_flags.isLoop = info->flags & MdsInstObjPosData::FLAG_LOOP;
  if (info->flags & MdsInstObjPosData::FLAG_DISP_OFF && info->id != 0) {
    DrMan::getIns()->setGblIdx(m_info->id);
  }
}

void DrResMdoInstPartsObj::setDisp(bool disp) {
  if (m_info->id != 0) {
    if (disp) {
      DrMan::getIns()->offGblIdx(m_info->id);
    } else {
      DrMan::getIns()->setGblIdx(m_info->id);
    }
  }
}

void DrResMdoInstPartsObj::getMatrix(mm::Mat44 &matrix) const {
  if (m_info->flags & MdsInstObjPosData::FLAG_POS_MATRIX) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        matrix.rows[i][j] = m_matrix->rows[i][j];
      }
    }
  }
}

bool DrResMdoInstPartsObj::isDisp() const {
  if (m_info->id == 0) {
    return false;
  }
  DrMan *drMan = DrMan::getIns();
  s32 id = m_info->id;
  return drMan->gblTbl[id >> 5] & (1 << (id & 31));
}

DrResMdoInstPartsAnm::DrResMdoInstPartsAnm(const u8 *data, const MdsInstObjPosData *info)
    : DrResMdoInstPartsObj(data, info), m_posAnm(nullptr), m_posFrame(0.0f), m_nodeFrame(0.0f), m_oldNodeFrame(0.0f), m_dblNodeFrames(), m_frameScale(1.0f), m_invFrameScale(1.0f), m_nodeStart(0),
      m_nodeMax(0), m_coliParam(nullptr), m_switches(nullptr), m_switchMax(0) {
  m_switchID = 1;
  if (info->frameScale != 0) {
    m_frameScale = info->frameScale * (1.0f / 255.0f) * 2.0f;
    m_invFrameScale = 1.0f / m_frameScale;
  }
}

DrResMdoInstPartsAnm::~DrResMdoInstPartsAnm() {}

void DrResMdoInstPartsAnm::setNodeFrame(f32 frame) {
  m_dblNodeFrames[DrMan::s_nDblStockIdx] = frame;
  m_flags.all |= 1 << DrMan::s_nDblStockIdx;
}

f32 DrResMdoInstPartsAnm::getNodeFrame() const {
  if (m_flags.all & (1 << DrMan::s_nDblStockIdx)) {
    return m_dblNodeFrames[DrMan::s_nDblStockIdx];
  }
  if (m_flags.all & (1 << DrMan::s_nDblMemIdx)) {
    return m_dblNodeFrames[DrMan::s_nDblMemIdx];
  }
  return m_nodeFrame;
}

void DrResMdoInstPartsAnm::setSwitchID(u8 id) {
  if (m_info->flags & MdsInstObjPosData::FLAG_SWITCH && m_switchID != id) {
    m_switchID = id;
    updateSwitch();
  }
}

void DrResMdoInstPartsAnm::updateSwitch() {
  int index = -1;
  u8 switchMax = m_switchMax;
  for (int i = 0; i < switchMax; i++) {
    if (m_switches[i].id == m_switchID) {
      index = i;
      break;
    }
  }
  const MdsInstAnmSwitch &entry = m_switches[index == -1 ? 0 : index];
  m_flags.all = (entry.flags & MdsInstAnmSwitch::FLAG_LOOP) == 0 ? m_flags.all & ~FLAG_LOOP : m_flags.all | FLAG_LOOP;
  if (entry.flags & MdsInstAnmSwitch::FLAG_FRAME) {
    u16 startFrame = entry.startFrame;
    u16 maxFrame = entry.endFrame - entry.startFrame;
    if (m_info->flags & MdsInstObjPosData::FLAG_NODE_ANM) {
      m_nodeStart = startFrame;
      m_nodeMax = maxFrame;
      if (m_flags.all & (1 << DrMan::s_nDblStockIdx)) {
        if (getNodeMaxFrame() < m_dblNodeFrames[DrMan::s_nDblStockIdx]) {
          m_dblNodeFrames[DrMan::s_nDblStockIdx] = getNodeMaxFrame();
        }
        if (m_dblNodeFrames[DrMan::s_nDblStockIdx] < 0.0f) {
          m_dblNodeFrames[DrMan::s_nDblStockIdx] = 0.0f;
        }
        m_oldNodeFrame = m_dblNodeFrames[DrMan::s_nDblStockIdx];
      } else {
        if (getNodeMaxFrame() < m_nodeFrame) {
          m_nodeFrame = getNodeMaxFrame();
        }
        if (m_nodeFrame < 0.0f) {
          m_nodeFrame = 0.0f;
        }
        m_oldNodeFrame = m_nodeFrame;
      }
    }
    if (m_info->flags & MdsInstObjPosData::FLAG_POS_ANM) {
      m_posAnm->setAnmFrame(startFrame, maxFrame);
    }
  }
}

u32 DrResMdoInstPartsAnm::getSwitchIndex(u32 index) const {
  if (index < m_switchMax) {
    return m_switches[index].id;
  }
  return 0;
}

void DrResMdoInstPartsAnm::getMatrix(mm::Mat44 &matrix) const {
  if (m_info->flags & MdsInstObjPosData::FLAG_POS_ANM) {
    m_posAnm->getMatrix(matrix);
  } else {
    DrResMdoInstPartsObj::getMatrix(matrix);
  }
}

void DrResMdoInstPartsAnm::getAnmMatrix(mm::Mat44 &matrix) const {
  if (m_info->flags & MdsInstObjPosData::FLAG_POS_ANM) {
    m_posAnm->getAnmMatrix(&matrix, m_posFrame * m_invFrameScale);
  } else {
    DrResMdoInstPartsObj::getMatrix(matrix);
  }
}

void DrResMdoInstPartsAnm::setMatrix(const mm::Mat44 &matrix) {
  if (m_info->flags & MdsInstObjPosData::FLAG_POS_ANM) {
    m_posAnm->setMatrix(matrix);
  }
}

void DrResMdoInstPartsAnm::setNodeAnmData(const MdsInstAnmNodeData *data) {
  m_nodeMax = data->frameMax;
  if (m_info->startRate != 0) {
    m_nodeFrame = m_oldNodeFrame = m_info->startRate * (1.0f / 255.0f) * data->frameMax;
  }
  if (data->coliParamOffset != 0) {
    m_coliParam = reinterpret_cast<const MdsInstAnmParamInfo *>(m_names + data->coliParamOffset);
    m_flags.isColiSkipData = true;
  }
}

void DrResMdoInstPartsAnm::setPosAnmData(DrResMdoPosInstAnm *posAnm, DrResMdoPos *pos) {
  m_posAnm = posAnm;
  m_pos = pos;
  if (m_info->startRate != 0) {
    m_posFrame = m_info->startRate * (1.0f / 255.0f) * posAnm->m_maxFrame;
  }
  posAnm->setup(m_posFrame);
}

DrResMdoInstPartsGlbID::DrResMdoInstPartsGlbID(const u8 *data, const MdsInstObjPosData *info) : DrResMdoInstPartsObj(data, info) {}

DrResMdoInstPartsGlbID::~DrResMdoInstPartsGlbID() {}

} // namespace ml
