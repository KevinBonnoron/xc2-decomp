#pragma once
#include <stddef.h>

#include "ml/dev_font.h"
#include "ml/msg_param.h"
#include "ml/reslist.h"
#include "ml/threadval.h"
#include "ml/win_view_frame.h"
#include "ml/work_obj.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "types.h"

namespace ml {
class IWorkEvent;

class WinView : public WorkObj, public FontLayer {
public:
  struct RENDER_INFO {
    mm::Pnt<int> unknown00; // Inferred role: size; original member name unknown.
    mm::Pnt<int> unknown08; // Inferred role: work size; original member name unknown.
    u8 _10[0x18 - 0x10];
    mm::Pnt<int> unknown18; // Inferred role: client offset from the top left; original member name unknown.
    mm::Pnt<int> unknown20; // Inferred role: client offset from the bottom right; original member name unknown.
    u8 _28[0x30 - 0x28];
    bool unknown30; // Inferred role: split horizontal; original member name unknown.
    u8 _31[0x34 - 0x31];
    s16 unknown34; // Inferred role: split line; original member name unknown.
    u8 _36[0x38 - 0x36];
    s16 unknown38; // Inferred role: split line when horizontal; original member name unknown.
    u8 _3a[0x3c - 0x3a];
    u32 unknown3c; // Inferred role: first split view wid; original member name unknown.
    u32 unknown40; // Inferred role: second split view wid; original member name unknown.
    u8 _44[0x48 - 0x44];
    WinViewFrame unknown48; // Inferred role: frame; original member name unknown.
  };

  void attachWorkEvent(IWorkEvent *event, bool isFront);
  const mm::Pnt<int> &getFramePos(bool isBack) const;
  void addFramePos(const mm::Pnt<int> &pos);
  mm::Pnt<int> getFrame2ViewOffset(bool isBack) const;
  mm::Pnt<int> getPos(bool isBack) const;
  mm::Pnt<int> getSize(bool isBack) const;
  mm::Rect<int> getRect(bool isBack) const;
  mm::Pnt<int> getClientPos(bool isBack) const;
  mm::Pnt<int> getClientSize(bool isBack) const;
  bool isSplitHolizon() const;
  bool isCurrent() const;
  WorkObj *getRootProc();
  void setRootRenderWID(WinView *view);
  void attachRenderWork(const WorkObj *work);
  WinView *getSplitView1();
  WinView *getSplitView2();
  const WinView *getSplitView1() const;
  const WinView *getSplitView2() const;
  void setDisp(bool isDisp, bool isInvalidCurrent);
  void deleteSplitView();
  bool hasCurrent() const;
  mm::Pnt<int> getFrameAbsPos(bool isBack) const;
  mm::Pnt<int> getAbsPos(bool isBack) const;
  mm::Rect<int> getAbsRect(bool isBack) const;
  mm::Rect<int> getRealAbsRect(bool isBack) const;
  void normalizeAbsRect(mm::Rect<int> &rect, bool isBack) const;
  s32 getSplitLine(bool isBack) const;
  WinView *getParentView();
  const WinView *getParentView() const;
  virtual void evtFocusOn();
  virtual void evtFocusOff();
  virtual void detachRenderWork(const WorkObj *work);
  virtual void detachWorkEvent(const IWorkEvent *event);

  threadval<RENDER_INFO> unknown1b8; // Inferred role: render info; original member name unknown.
  reslist<u32> unknown338;           // Inferred role: render work ids; original member name unknown.
  u8 _378[0x3b8 - 0x378];
  u32 unknown3b8;          // Inferred role: state flags; original member name unknown.
  u32 unknown3bc;          // Inferred role: frame flags; original member name unknown.
  MsgParam<10> unknown3c0; // Inferred role: event messages; original member name unknown.
  u8 _4d0[0x524 - 0x4d0];
  f32 unknown524; // Inferred role: transparency; original member name unknown.
};

static_assert(sizeof(WinView::RENDER_INFO) == 0xb0, "");
static_assert(offsetof(WinView::RENDER_INFO, unknown08) == 0x08, "");
static_assert(offsetof(WinView::RENDER_INFO, unknown30) == 0x30, "");
static_assert(offsetof(WinView::RENDER_INFO, unknown48) == 0x48, "");
static_assert(offsetof(WinView, unknown1b8) == 0x1b8, "");
static_assert(offsetof(WinView, unknown338) == 0x338, "");
static_assert(offsetof(WinView, unknown3b8) == 0x3b8, "");
static_assert(offsetof(WinView, unknown3c0) == 0x3c0, "");
static_assert(offsetof(WinView, unknown524) == 0x524, "");

inline mm::Pnt<int> WinViewFrame::getFrame2ViewOffset() const {
  mm::Pnt<int> offset(0, 0);
  u32 frameFlags = m_info->unknown3bc;
  if ((frameFlags & 1) && (m_info->unknown3b8 & 3) == 0) {
    s16 width = unknown60;
    offset.x = width;
    offset.y = offset.x;
    if (frameFlags & 2) {
      offset.y = offset.x * 2 + 0x16;
    }
  }
  return offset;
}

} // namespace ml
