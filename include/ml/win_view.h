#pragma once
#include <stddef.h>

#include "ml/critical_section.h"
#include "ml/dev_font.h"
#include "ml/msg_param.h"
#include "ml/reslist.h"
#include "ml/threadval.h"
#include "ml/win_split_frame.h"
#include "ml/win_view_frame.h"
#include "ml/win_view_port.h"
#include "ml/work_obj.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace ml {
class IWorkEvent;

class WinView : public WorkObj, public FontLayer {
public:
  // Inferred base: the constructor runs the WinViewPort constructor and updateViewPort inlines WinViewPort::setSize.
  // The split frame and the frame members are proven by applyRect, which calls WinSplitFrame::apply on +0x28, and by
  // the constructor, which inlines the WinSplitFrame and WinViewFrame constructors on +0x28 and +0x48.
  struct RENDER_INFO : public WinViewPort {
    WinSplitFrame unknown28; // Inferred role: split frame; original member name unknown.
    WinViewFrame unknown48;  // Inferred role: frame; original member name unknown.
  };

  WinView(const char *name, WorkObj *parent);
  ~WinView() override;
  static WinView *getView(bool isResetShadow);
  static void setDefaultFrameColor(const mm::Col4 &color);
  static void setInitialBackCol(const mm::Col4 &color);
  static const mm::Col4 &getDefaultTitleBarColor();
  void updateViewPort(const mm::Rect<int> &rect);
  void renderView();
  void setRect(const mm::Rect<int> &rect);
  void setTitle(const char *title);
  void setSize(int width, int height);
  void setFrameRect(const mm::Rect<int> &rect);
  void setSplitLine(int line);
  void createSplitView(bool isHorizontal, WinView *view1, WinView *view2);
  bool attachWorkEvent(IWorkEvent *event, bool isFront);
  WinView *getPointedView(const mm::Pnt<int> &pos);
  const mm::Pnt<int> &getFramePos(bool isBack) const;
  void addFramePos(const mm::Pnt<int> &pos);
  void addScroll(const mm::Pnt<int> &scroll);
  mm::Pnt<int> getFrame2ViewOffset(bool isBack) const;
  mm::Pnt<int> getPos(bool isBack) const;
  mm::Pnt<int> getSize(bool isBack) const;
  mm::Rect<int> getRect(bool isBack) const;
  mm::Pnt<int> getClientPos(bool isBack) const;
  mm::Pnt<int> getClientSize(bool isBack) const;
  mm::Rect<int> getClientRect(bool isBack) const;
  bool isSplitHolizon() const;
  bool isCurrent() const;
  WorkObj *getRootProc();
  void setRootRenderWID(WinView *view);
  bool attachRenderWork(const WorkObj *work);
  WinView *getSplitView1();
  WinView *getSplitView2();
  const WinView *getSplitView1() const;
  const WinView *getSplitView2() const;
  void setDisp(bool isDisp, bool isInvalidCurrent);
  void setCurrent();
  void setFullScreen();
  void deleteSplitView();
  bool hasCurrent() const;
  mm::Pnt<int> getFrameAbsPos(bool isBack) const;
  mm::Pnt<int> getAbsPos(bool isBack) const;
  mm::Rect<int> getAbsRect(bool isBack) const;
  mm::Rect<int> getRealAbsRect(bool isBack) const;
  void normalizeAbsRect(mm::Rect<int> &rect, bool isBack) const;
  mm::Rect<int> getFrameRect(bool isBack) const;
  mm::Rect<int> getFrameAbsRect(bool isBack) const;
  mm::Rect<int> getScissorRect(bool isBack) const;
  mm::Rect<int> getScissorAbsRect(bool isBack) const;
  mm::Rect<int> getSplitRect(const WinView *view, bool isBack) const;
  mm::Rect<int> getClientSplitRect(const WinView *view, bool isBack) const;
  mm::Rect<int> getClientAbsRect(bool isBack) const;
  mm::Rect<int> getClientScissorAbsRect(bool isBack) const;
  mm::Rect<int> getClientScissorRect(bool isBack) const;
  bool isSplit(bool isBack) const;
  void initializeClientScreen(bool isSkipClear);
  s32 getSplitLine(bool isBack) const;
  WinView *getParentView();
  const WinView *getParentView() const;
  virtual bool evtFocusOn();
  virtual bool evtFocusOff();
  virtual bool detachRenderWork(const WorkObj *work);
  virtual bool detachWorkEvent(const IWorkEvent *event);
  virtual void destroyCtrlMemory();
  virtual void applyRect();
  virtual void getViewOfs(mm::Rect<int> &rect, bool isBack);
  void wkTail() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
  void updateMsg();
  void applyPrio();

  threadval<RENDER_INFO> unknown1b8; // Inferred role: render info; original member name unknown.
  reslist<u32> unknown338;           // Inferred role: render work ids; original member name unknown.
  reslist<IWorkEvent *> unknown378;  // Inferred role: attached work events; original member name unknown.
  u32 unknown3b8;                    // Inferred role: state flags; original member name unknown.
  u32 unknown3bc;                    // Inferred role: frame flags; original member name unknown.
  MsgParam<10> unknown3c0;           // Inferred role: event messages; original member name unknown.
  mm::mtl::FixStr<64> unknown4d0;    // Inferred role: title; original member name unknown.
  mm::Col4 unknown514;               // Inferred role: back color, scaled by the transparency for the clear color; original member name unknown.
  f32 unknown524;                    // Inferred role: transparency; original member name unknown.
  s32 unknown528;                    // Inferred role: sort priority among the child views; original member name unknown.
  mm::Rect<int> unknown52c;          // Inferred role: rect saved while the view is full screen; original member name unknown.
  bool unknown53c;                   // Inferred role: copy the back render info to the front when the rect changes; original member name unknown.
  CriticalSection unknown540;        // Inferred role: lock of the message queue; original member name unknown.
  CriticalSection unknown568;        // Inferred role: lock of the work event list; original member name unknown.
};

inline mm::Rect<int> WinViewFrame::unknown001(bool isBack) const {
  const WinView::RENDER_INFO *viewInfo = isBack ? m_info->unknown1b8.m_back : m_info->unknown1b8.m_front;
  mm::Pnt<int> size = m_info->getSize(isBack);
  mm::Rect<int> rect(viewInfo->unknown48.unknown58, size);
  u32 frameFlags = m_info->unknown3bc;
  if ((frameFlags & 1) && (m_info->unknown3b8 & 3) == 0) {
    s16 border = unknown60;
    rect.width = size.x + border * 2;
    if (frameFlags & 2) {
      rect.height = size.y + border * 3 + 0x16;
    } else {
      rect.height = size.y + border * 2;
    }
  }
  return rect;
}

static_assert(sizeof(WinView::RENDER_INFO) == 0xb0, "");
static_assert(offsetof(WinView::RENDER_INFO, unknown28) == 0x28, "");
static_assert(offsetof(WinView::RENDER_INFO, unknown48) == 0x48, "");
static_assert(offsetof(WinView, unknown1b8) == 0x1b8, "");
static_assert(offsetof(WinView, unknown338) == 0x338, "");
static_assert(offsetof(WinView, unknown378) == 0x378, "");
static_assert(offsetof(WinView, unknown3b8) == 0x3b8, "");
static_assert(offsetof(WinView, unknown3c0) == 0x3c0, "");
static_assert(offsetof(WinView, unknown4d0) == 0x4d0, "");
static_assert(offsetof(WinView, unknown514) == 0x514, "");
static_assert(offsetof(WinView, unknown524) == 0x524, "");
static_assert(offsetof(WinView, unknown528) == 0x528, "");
static_assert(offsetof(WinView, unknown52c) == 0x52c, "");
static_assert(offsetof(WinView, unknown53c) == 0x53c, "");
static_assert(offsetof(WinView, unknown540) == 0x540, "");
static_assert(offsetof(WinView, unknown568) == 0x568, "");
static_assert(sizeof(WinView) == 0x590, "");

} // namespace ml
