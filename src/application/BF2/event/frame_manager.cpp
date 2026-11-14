#include "event/frame_manager.h"

#include <stddef.h>

#include "event/copydata_manager.h"
#include "event/cpu_manager.h"
#include "event/cs_snd_manager.h"
#include "event/manager.h"
#include "event/movie_manager.h"
#include "event/skip_manager.h"
#include "event/voice_manager.h"
#include "fw/fw_debug.h"
#include "gf/gf_pause.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"

namespace event {

static constexpr u32 PAUSE_BITS_UNKNOWN_5108 = 0x13f4;                                           // Inferred role: pause bits acc frame; original name unknown.
static constexpr u32 PAUSE_BITS_UNKNOWN_120842 = 0x1d80a;                                        // Inferred role: pause bits stream stop; original name unknown.
static constexpr u32 PAUSE_BITS_UNKNOWN_129 = gf::PAUSE_BIT_UNKNOWN_0 | gf::PAUSE_BIT_UNKNOWN_7; // Inferred role: gf pause bits; original name unknown.
static constexpr u32 PAUSE_BITS_UNKNOWN_141 =
    gf::PAUSE_BIT_UNKNOWN_0 | gf::PAUSE_BIT_UNKNOWN_2 | gf::PAUSE_BIT_UNKNOWN_3 | gf::PAUSE_BIT_UNKNOWN_7; // Inferred role: gf pause bits; original name unknown.
static constexpr u32 PAUSE_BITS_UNKNOWN_653 =
    gf::PAUSE_BIT_UNKNOWN_0 | gf::PAUSE_BIT_UNKNOWN_2 | gf::PAUSE_BIT_UNKNOWN_3 | gf::PAUSE_BIT_UNKNOWN_7 | gf::PAUSE_BIT_UNKNOWN_9; // Inferred role: gf pause bits; original name unknown.
static constexpr u32 PAUSE_BITS_UNKNOWN_124930 = 0x1e802;                                                                            // Inferred role: pause bits cs sound; original name unknown.
static constexpr u32 PAUSE_BITS_UNKNOWN_124938 = 0x1e80a;                                                                            // Inferred role: pause bits voice; original name unknown.

f32 FrameManager::getFrame() const { return m_frame; }

bool FrameManager::isPause(PAUSE_TYPE type) const { return (unknown18 & (type == PAUSE_TYPE_UNKNOWN_17_2 ? ~0u : 1u << type)) != 0; }

const FrameInfo &FrameManager::frameInfo() {
  unknown1170.unknown00 = m_frame;
  unknown1170.unknown04 = unknown13c - m_frame;
  if (isPause(PAUSE_TYPE_UNKNOWN_17_2)) {
    unknown1170.unknown04 = 0.0f;
  }
  unknown1170.unknown08 = unknown1170.unknown04;
  if ((unknown18 & PAUSE_BITS_UNKNOWN_5108) != 0 && unknown1170.unknown04 <= 0.0f) {
    unknown1170.unknown08 = __builtin_fmaxf(unknown160, 0.0f) + 1.0f;
  }
  unknown1170.unknown0c = unknown1170.unknown04;
  if ((unknown10 & FLAG_UNKNOWN_0) == 0) {
    unknown1170.unknown0c = __builtin_fmaxf(unknown160, 0.0f) + 1.0f;
  }
  if ((unknown18 & PAUSE_BITS_UNKNOWN_120842) != 0) {
    unknown1170.unknown0c = 0.0f;
  }
  unknown1170.unknown10 = unknown160;
  return unknown1170;
}

f32 FrameManager::getTotalFrame() const { return m_totalFrame; }

void FrameManager::pause(PAUSE_TYPE type, bool isPause) {
  u32 bit = 1u << type;
  if (((unknown18 & bit) != 0) == isPause) {
    return;
  }
  if (unknown20[type] != reinterpret_cast<gf::GF_PAUSE_HANDLE *>(-1)) {
    gf::GfPause::destroyHandle(unknown20[type]);
    unknown20[type] = reinterpret_cast<gf::GF_PAUSE_HANDLE *>(-1);
  }
  if (isPause) {
    switch (type) {
    case PAUSE_TYPE_UNKNOWN_1:
      unknown20[type] = gf::GfPause::reqPause(PAUSE_BITS_UNKNOWN_653);
      break;
    case PAUSE_TYPE_UNKNOWN_3:
      unknown20[type] = gf::GfPause::reqPause(PAUSE_BITS_UNKNOWN_129);
      break;
    case PAUSE_TYPE_UNKNOWN_11:
    case PAUSE_TYPE_UNKNOWN_16:
      unknown20[type] = gf::GfPause::reqPause(PAUSE_BITS_UNKNOWN_141);
      break;
    case PAUSE_TYPE_UNKNOWN_14:
    case PAUSE_TYPE_UNKNOWN_15:
      if (unknown14 & DISP_FLAG_UNKNOWN_4) {
        unknown20[type] = gf::GfPause::reqPause(PAUSE_BITS_UNKNOWN_141);
      }
      break;
    default:
      break;
    }
    unknown18 |= bit;
  } else {
    unknown18 &= ~bit;
  }
  mm::mtl::Singleton<CsSndManager>::getPtr()->pause((unknown18 & PAUSE_BITS_UNKNOWN_124930) != 0);
  mm::mtl::Singleton<VoiceManager>::getPtr()->pause((unknown18 & PAUSE_BITS_UNKNOWN_124938) != 0);
  mm::mtl::Singleton<MovieManager>::getPtr()->pause((unknown18 & PAUSE_BITS_UNKNOWN_120842) != 0);
  mm::mtl::Singleton<CpuManager>::getPtr()->pause(unknown18 != 0);
  if (type == PAUSE_TYPE_UNKNOWN_1) {
    if (isPause) {
      unknown10 |= FLAG_UNKNOWN_10;
    } else {
      unknown10 |= FLAG_UNKNOWN_11;
    }
  }
}

void FrameManager::requestFrame(f32 frame) {
  unknown10 |= FLAG_UNKNOWN_7;
  unknown154 = frame;
}

void FrameManager::setLockFrame(bool isLock, f32 frame) {
  setFlag(FLAG_UNKNOWN_3, isLock);
  unknown14c = frame;
}

FrameManager::FrameManager()
    : unknown10(0), unknown18(0), m_frame(0.0f), m_totalFrame(0.0f), unknown138(0.0f), unknown13c(0.0f), unknown144(0.0f), m_maxFrame(unknown003), m_accType(ACC_TYPE_UNKNOWN_1), unknown1170() {
  unknown14 = DISP_FLAG_UNKNOWN_1;
  for (u32 i = 0; i < PAUSE_TYPE_UNKNOWN_17; i++) {
    unknown20[i] = reinterpret_cast<gf::GF_PAUSE_HANDLE *>(-1);
  }
}

void FrameManager::login() {
  m_totalFrame = 0.0f;
  unknown138 = 0.0f;
}

void FrameManager::initPage() {
  m_maxFrame = unknown003;
  m_pageName = "";
  m_pageID = 0;
  m_frame = 0.0f;
  unknown13c = 0.0f;
  unknown144 = 0.0f;
  unknown158 = 0.0f;
  unknown1188 = -1;
  unknown168.clear();
  unknown138 = m_totalFrame;
  unknown160 = 0.0f;
  unknown10 |= FLAG_UNKNOWN_8;
  CpuManager::get().start();
}

void FrameManager::render() {
  if (!(unknown14 & DISP_FLAG_UNKNOWN_0)) {
    return;
  }
  s32 height = ml::DevGraph::getRootHeight();
  s32 top = height - 60;
  s32 width = ml::DevGraph::getRootWidth();
  fw::debug::drawSquare2D(mm::Rect<s32>(25, top, width - 50, 45), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(25, top, width - 50, 45), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(30, height - 55, "TIME");
  fw::debug::drawLineSquare2D(mm::Rect<s32>(65, height - 37, width - 130, 15), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawSquare2D(mm::Rect<s32>(65, height - 36, (width - 130) * this->m_frame / __builtin_fmaxf(m_maxFrame, 1.0f), 14), mm::Col4(1.0f, 0.0f, 0.0f, 0.25f));
  s32 lineTop = height - 46;
  s32 barWidth = ml::DevGraph::getRootWidth() - 130;
  for (size_t i = 0; i < unknown168.size(); i++) {
    s32 frame = unknown168[i].unknown00;
    s32 x = frame * barWidth / static_cast<s32>(__builtin_fmaxf(m_maxFrame, 1.0f)) + 65;
    if (unknown168[i].unknown04) {
      fw::debug::drawLine2D(mm::Pnt<s32>(x, lineTop), mm::Pnt<s32>(x, height - 16), mm::Col4(1.0f, 0.0f, 0.0f, 1.0f));
      fw::debug::drawFontColor(mm::Col4(1.0f, 0.0f, 0.0f, 1.0f));
    } else {
      fw::debug::drawLine2D(mm::Pnt<s32>(x, lineTop), mm::Pnt<s32>(x, height - 16), mm::Col4(0.7f, 0.0f, 0.0f, 1.0f));
      fw::debug::drawFontColor(mm::Col4(0.7f, 0.0f, 0.0f, 1.0f));
    }
    fw::debug::drawFont(x, height - 56, "%d", frame);
  }
  s32 reachedFrame = unknown144;
  s32 x = reachedFrame * barWidth / static_cast<s32>(__builtin_fmaxf(m_maxFrame, 1.0f)) + 65;
  fw::debug::drawLine2D(mm::Pnt<s32>(x, lineTop), mm::Pnt<s32>(x, height - 16), mm::Col4(1.0f, 0.0f, 0.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(0.7f, 0.0f, 0.0f, 1.0f));
  fw::debug::drawFont(x, height - 56, "%d", reachedFrame);
}

void FrameManager::tail() {
  u32 dispFlags = unknown14;
  if (dispFlags & DISP_FLAG_UNKNOWN_5) {
    frameInfo();
  }
  if ((dispFlags & DISP_FLAG_UNKNOWN_1) && ((unknown10 & FLAG_UNKNOWN_8) || m_frame != unknown13c) && m_pageName.c_str()[0] != '\0') {
    mm::mtl::Singleton<CopydataManager>::getPtr();
  }
  if (unknown14 & DISP_FLAG_UNKNOWN_2) {
    if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() && unknown1184++ > 9) {
      unknown14 &= ~DISP_FLAG_UNKNOWN_2;
    }
  }
  unknown10 &= ~(FLAG_UNKNOWN_6 | FLAG_UNKNOWN_8);
}

void FrameManager::tailAlways() {
  if (unknown10 & FLAG_UNKNOWN_10) {
    f32 frame = unknown13c;
    unknown10 &= ~FLAG_UNKNOWN_10;
    unknown140 = frame;
    return;
  }
  if (unknown10 & FLAG_UNKNOWN_11) {
    f32 frame = unknown140;
    unknown10 &= ~FLAG_UNKNOWN_11;
    unknown13c = frame;
  }
  this->m_frame = unknown13c;
  if (unknown144 < this->m_frame) {
    unknown144 = this->m_frame;
  }
}

void FrameManager::setStreamMode(bool isStreamMode) { setFlag(FLAG_UNKNOWN_0, isStreamMode); }

void FrameManager::setCsSndAccEnable(bool isEnable) { setFlag(FLAG_UNKNOWN_1, isEnable); }

void FrameManager::setCpuAccEnable(bool isEnable) { setFlag(FLAG_UNKNOWN_2, isEnable); }

void FrameManager::setInfomation(const char *pageName, int pageID, f32 maxFrame) {
  bool isMakeCapture = (unknown10 & FLAG_UNKNOWN_4) != 0;
  m_pageName = pageName;
  m_pageID = pageID;
  m_maxFrame = __builtin_fmaxf(maxFrame, 0.0f);
  if (isMakeCapture && Manager::get()->getStartPageID() <= pageID) {
    unknown10 |= FLAG_UNKNOWN_5;
    unknown150 = m_maxFrame - 1.0f;
  }
}

const char *FrameManager::getPageName() const { return m_pageName.c_str(); }

int FrameManager::getPageID() const { return m_pageID; }

void FrameManager::pauseClearAll() {
  for (u32 i = 0; i < PAUSE_TYPE_UNKNOWN_17; i++) {
    pause(static_cast<PAUSE_TYPE>(i), false);
  }
}

void FrameManager::koma(PAUSE_TYPE type) {
  pause(type, false);
  unknown1188 = 1;
  unknown118c = type;
}

void FrameManager::setFrame(f32 frame) {
  frame = frame < m_maxFrame ? frame : m_maxFrame;
  unknown13c = frame;
  this->m_frame = frame;
}

f32 FrameManager::getMaxFrame() const { return m_maxFrame; }

void FrameManager::setMakeCaptureFrame(bool isMake) { setFlag(FLAG_UNKNOWN_4, isMake); }

bool FrameManager::isCaptureFrame() const { return (unknown10 & FLAG_UNKNOWN_6) != 0; }

void FrameManager::setSkipAbleFrame(f32 frame) {
  unknown158 = frame;
  m_totalFrame = unknown138 + frame;
}

void FrameManager::addKeyFrame(f32 frame, bool isCut) {
  unknown001 key;
  key.unknown00 = frame;
  key.unknown04 = isCut;
  if (!unknown168.empty() && !(unknown168.back().unknown00 < frame)) {
    for (size_t i = 0; i < unknown168.size(); i++) {
      unknown001 &keyFrame = unknown168[i];
      if (key.unknown00 == keyFrame.unknown00) {
        if (isCut) {
          keyFrame.unknown04 = true;
        }
        return;
      }
      if (key.unknown00 < keyFrame.unknown00) {
        f32 nextFrame = keyFrame.unknown00;
        bool nextIsCut = keyFrame.unknown04;
        keyFrame.unknown00 = key.unknown00;
        keyFrame.unknown04 = key.unknown04;
        key.unknown00 = nextFrame;
        key.unknown04 = nextIsCut;
      }
    }
  }
  unknown168.push_back(key);
}

void FrameManager::shiftFrame(f32 frame) {
  if (unknown168.empty()) {
    return;
  }
  if (this->m_frame < frame) {
    f32 lastFrame = unknown168.back().unknown00;
    shiftRight(false, lastFrame > frame ? frame : lastFrame);
    unknown14 |= DISP_FLAG_UNKNOWN_2;
    unknown1184 = 0;
  } else if (this->m_frame > frame) {
    shiftLeft(false, frame > 0.0f ? frame : 0.0f);
  }
}

void FrameManager::setAccframe(bool isAcc, ACC_TYPE type) { m_accType = isAcc ? type : ACC_TYPE_UNKNOWN_0; }

ACC_TYPE FrameManager::getAccType() const { return m_accType; }

void FrameManager::queryCutList(mm::mtl::FixedVector<f32, KEY_FRAME_UNKNOWN_512> &cutList) const {
  cutList.clear();
  for (size_t i = 0; i < unknown168.size(); i++) {
    if (unknown168[i].unknown04) {
      cutList.push_back(unknown168[i].unknown00);
    }
  }
}

void FrameManager::setDisp(bool isDisp) { setDispFlag(DISP_FLAG_UNKNOWN_0, isDisp); }

bool FrameManager::isDisp() const { return (unknown14 & DISP_FLAG_UNKNOWN_0) != 0; }

void FrameManager::setUseSkip(bool isUse) { setDispFlag(DISP_FLAG_UNKNOWN_3, isUse); }

void FrameManager::setUseStop3D(bool isUse) { setDispFlag(DISP_FLAG_UNKNOWN_4, isUse); }

void FrameManager::setUseAccPrint(bool isUse) { setDispFlag(DISP_FLAG_UNKNOWN_5, isUse); }

bool FrameManager::isUseAccPrint() const { return (unknown14 & DISP_FLAG_UNKNOWN_5) != 0; }

void FrameManager::setSyncframe(bool isSync) { setDispFlag(DISP_FLAG_UNKNOWN_1, isSync); }

bool FrameManager::isSyncframe() const { return (unknown14 & DISP_FLAG_UNKNOWN_1) != 0; }

bool FrameManager::isWaiting() const { return (unknown10 & FLAG_UNKNOWN_9) != 0; }

} // namespace event
