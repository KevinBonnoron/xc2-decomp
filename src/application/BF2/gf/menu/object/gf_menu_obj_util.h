#pragma once
#include "types.h"

namespace ui {
class UIStr;
} // namespace ui

namespace gf {

class GfMenuCallContext;

class GfMenuObjUtil {
public:
  static u32 getBtnIconNumber(u32 button);
  static u32 getPadSelectIconNumber(u32 select);
  static u32 getPointerSelectIconNumber();
  static void setChildDisp(u32 handle, const char *name, bool disp);
  static void setChildMulColor(u32 handle, const char *name, const char *color);
  static void setChildAddColor(u32 handle, const char *name, const char *color);
  static void setChildText(u32 handle, const char *name, u16 id);
  static void setChildText(u32 handle, const char *name, const ui::UIStr &text);
  static void setChildIcon(u32 handle, const char *name, u16 icon);
  static u32 playAnime(u32 handle, const char *name, const char *anime);
  static u32 getMenuIcon(u32 id);
  static void setDockPos(u32 handle, u32 target, u8 dock, bool global);
  static void addPos(u32 handle, s16 x, s16 y);
  static bool isMenuObjectFull();
  static int getCtrlID(u32 handle);
  static void stopCtrl(int ctrl);
  static void suspendCtrl(int ctrl);
  static void releaseCtrl(int ctrl);
  static bool isBusyCtrl(int ctrl);
  static void setCtrlDefault(int ctrl);
  static void setCtrlSpeedFactor(int ctrl, f32 speedFactor);
  static u32 getPresetCtrlCurve(u32 preset);
  static const char *getMenuMS(u32 id);
  static u32 getLeaderPartyID();
  static int getLeaderPartyType();
  static bool isExitDriver(u32 partyId);
  static u16 getMsgIDFromList(u32 bdat, u16 id);
  static bool checkCCStart(GfMenuCallContext *context);
  static bool checkCCNext(GfMenuCallContext *context, u32 menu);
  static u32 playSE(u32 id);
  static u32 playSE(const char *name);
  static u32 playSECommonDecide();
  static u32 playSECommon(u32 type);
  static u32 playSECommonCancel();
  static u32 playSECommonCursor();
  static u32 playSECommonTab();
  static u32 playSECommonSort();
  static u32 playSECommonOpenSubMenu();
  static u32 playSECommonCloseSubMenu();
  static void stopSE(u32 handle, f32 time);
  static bool startBGM(u32 handle);
  static bool isValidSoundHandle(u32 handle);
  static void stopBGM(u32 handle, f32 time);
  static u32 playJingle(u32 id);
};

} // namespace gf
