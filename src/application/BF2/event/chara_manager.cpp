#include "event/chara_manager.h"

#include "event/extend.h"
#include "event/mdlstm_manager.h"
#include "event/model_obj.h"
#include "event/res_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

bool CharaManager::isSeamlessAction() const { return (unknown10 & FLAG_UNKNOWN_3) != 0; }

bool CharaManager::isStreamMode() const { return (unknown10 & FLAG_UNKNOWN_0) != 0; }

int CharaManager::getReuseFlag() const { return m_reuseFlag; }

bool CharaManager::isUseHood() const { return (unknown10 & FLAG_UNKNOWN_5) != 0; }

bool CharaManager::isOffscrMode() const { return (unknown10 & FLAG_UNKNOWN_1) != 0; }

u32 CharaManager::getOffscrID() const { return m_offscrID; }

bool CharaManager::isSystemTicket960() const { return (unknown10 & FLAG_UNKNOWN_4) != 0; }

bool CharaManager::isAutoTalkMode() const { return (unknown10 & FLAG_UNKNOWN_2) != 0; }

CharaManager::CharaManager() : unknown10(0), unknown14(0), m_offscrID(0), m_reuseFlag(0) {}

void CharaManager::loadResource(const char *name) {
  if (!isStreamMode()) {
    mm::mtl::Singleton<ResManager>::getPtr()->load(mm::mtl::Singleton<Extend>::getPtr()->anm(name), nullptr, false);
  }
}

void CharaManager::loadMdlstream(f32 frame, const char *path, u32 value) {
  if (isOffscrMode()) {
    value = m_offscrID;
  }
  if (isStreamMode()) {
    bool isHood = isUseHood();
    mm::mtl::Singleton<MdlstmManager>::getPtr()->load(frame, path, value, isHood);
  }
}

void CharaManager::loadMdlstream(f32 frame, CHARA_TYPE type, u32 id, u32 value) {
  if (isOffscrMode()) {
    value = m_offscrID;
  }
  if (isStreamMode()) {
    bool isHood = isUseHood();
    switch (type) {
    case CHARA_TYPE_UNKNOWN_1:
      mm::mtl::Singleton<MdlstmManager>::getPtr()->load(frame, MODEL_TYPE_UNKNOWN_1, id, value, isHood);
      break;
    case CHARA_TYPE_UNKNOWN_2:
      mm::mtl::Singleton<MdlstmManager>::getPtr()->load(frame, MODEL_TYPE_UNKNOWN_2, id, value, isHood);
      break;
    case CHARA_TYPE_UNKNOWN_3:
      mm::mtl::Singleton<MdlstmManager>::getPtr()->load(frame, MODEL_TYPE_UNKNOWN_3, id, value, isHood);
      break;
    case CHARA_TYPE_UNKNOWN_5:
      mm::mtl::Singleton<MdlstmManager>::getPtr()->load(frame, MODEL_TYPE_UNKNOWN_4, id, value, isHood);
      break;
    }
  }
}

void CharaManager::clear() {
  m_offscrID = 0;
  m_reuseFlag = 0;
  unknown10 = 0;
}

void CharaManager::setStreamMode(bool isStreamMode) { setFlag(FLAG_UNKNOWN_0, isStreamMode); }

void CharaManager::setOffscrMode(bool isOffscrMode, u32 offscrID) {
  if (isOffscrMode) {
    unknown10 |= FLAG_UNKNOWN_1;
    m_offscrID = offscrID;
  } else {
    unknown10 &= ~FLAG_UNKNOWN_1;
    m_offscrID = 0;
  }
}

void CharaManager::setAutoTalkMode(bool isAutoTalkMode) { setFlag(FLAG_UNKNOWN_2, isAutoTalkMode); }

void CharaManager::setSeamlessAction(bool isSeamlessAction) { setFlag(FLAG_UNKNOWN_3, isSeamlessAction); }

void CharaManager::setSystemTicket960(bool isSystemTicket960) { setFlag(FLAG_UNKNOWN_4, isSystemTicket960); }

void CharaManager::setUseHood(bool isUseHood) { setFlag(FLAG_UNKNOWN_5, isUseHood); }

void CharaManager::setCharaDisp(bool isDisp) { setDispFlag(DISP_FLAG_UNKNOWN_0, isDisp); }

bool CharaManager::isCharaDisp() const { return (unknown14 & DISP_FLAG_UNKNOWN_0) != 0; }

void CharaManager::setFacialDisp(bool isDisp) { setDispFlag(DISP_FLAG_UNKNOWN_1, isDisp); }

bool CharaManager::isFacialDisp() const { return (unknown14 & DISP_FLAG_UNKNOWN_1) != 0; }

void CharaManager::setBoneDisp(bool isDisp) { setDispFlag(DISP_FLAG_UNKNOWN_2, isDisp); }

bool CharaManager::isBoneDisp() const { return (unknown14 & DISP_FLAG_UNKNOWN_2) != 0; }

void CharaManager::setReuseFlag(int reuseFlag) { m_reuseFlag = reuseFlag; }

void CharaManager::OnEventProc(MSG_TYPE type) {
  if (type == MSG_TYPE_UNKNOWN_4) {
    clear();
  }
}

} // namespace event
