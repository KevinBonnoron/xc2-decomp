#include "event/chara_manager.h"

namespace event {

bool CharaManager::isSeamlessAction() const { return (unknown10 & FLAG_SEAMLESS_ACTION) != 0; }

bool CharaManager::isStreamMode() const { return (unknown10 & FLAG_STREAM_MODE) != 0; }

int CharaManager::getReuseFlag() const { return m_reuseFlag; }

bool CharaManager::isUseHood() const { return (unknown10 & FLAG_USE_HOOD) != 0; }

bool CharaManager::isOffscrMode() const { return (unknown10 & FLAG_OFFSCR_MODE) != 0; }

u32 CharaManager::getOffscrID() const { return m_offscrID; }

bool CharaManager::isSystemTicket960() const { return (unknown10 & FLAG_SYSTEM_TICKET960) != 0; }

bool CharaManager::isAutoTalkMode() const { return (unknown10 & FLAG_AUTO_TALK_MODE) != 0; }

CharaManager::CharaManager() : unknown10(0), unknown14(0), m_offscrID(0), m_reuseFlag(0) {}

void CharaManager::clear() {
  m_offscrID = 0;
  m_reuseFlag = 0;
  unknown10 = 0;
}

void CharaManager::setStreamMode(bool isStreamMode) { setFlag(FLAG_STREAM_MODE, isStreamMode); }

void CharaManager::setOffscrMode(bool isOffscrMode, u32 offscrID) {
  if (isOffscrMode) {
    unknown10 |= FLAG_OFFSCR_MODE;
    m_offscrID = offscrID;
  } else {
    unknown10 &= ~FLAG_OFFSCR_MODE;
    m_offscrID = 0;
  }
}

void CharaManager::setAutoTalkMode(bool isAutoTalkMode) { setFlag(FLAG_AUTO_TALK_MODE, isAutoTalkMode); }

void CharaManager::setSeamlessAction(bool isSeamlessAction) { setFlag(FLAG_SEAMLESS_ACTION, isSeamlessAction); }

void CharaManager::setSystemTicket960(bool isSystemTicket960) { setFlag(FLAG_SYSTEM_TICKET960, isSystemTicket960); }

void CharaManager::setUseHood(bool isUseHood) { setFlag(FLAG_USE_HOOD, isUseHood); }

void CharaManager::setCharaDisp(bool isDisp) { setDispFlag(DISP_FLAG_CHARA, isDisp); }

bool CharaManager::isCharaDisp() const { return (unknown14 & DISP_FLAG_CHARA) != 0; }

void CharaManager::setFacialDisp(bool isDisp) { setDispFlag(DISP_FLAG_FACIAL, isDisp); }

bool CharaManager::isFacialDisp() const { return (unknown14 & DISP_FLAG_FACIAL) != 0; }

void CharaManager::setBoneDisp(bool isDisp) { setDispFlag(DISP_FLAG_BONE, isDisp); }

bool CharaManager::isBoneDisp() const { return (unknown14 & DISP_FLAG_BONE) != 0; }

void CharaManager::setReuseFlag(int reuseFlag) { m_reuseFlag = reuseFlag; }

void CharaManager::OnEventProc(MSG_TYPE type) {
  if (type == MSG_TYPE_INIT) {
    clear();
  }
}

} // namespace event
