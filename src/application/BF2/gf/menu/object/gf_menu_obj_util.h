#pragma once
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace ui {
class UIStr;
} // namespace ui

namespace gf {

class GfMenuCallContext;
struct QuestID;
struct GF_OBJ_HANDLE;

class GfMenuObjUtil {
public:
  struct ArtsIconInfo {
    ArtsIconInfo() : iconType(0), enhanceIcon(0), reactionIcon(0), _0c(), rangeIcon(0) {}

    int iconType;
    int enhanceIcon;
    int reactionIcon;
    u8 _0c[0x10 - 0x0c];
    int rangeIcon;
  };

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
  static bool isLeaderBladeEnable();
  static bool isBladeEnable(u32 partyId, int slot);
  static bool isValidBlade(u32 blade);
  static bool isBladeEnableOffset(u32 partyId, int offset);
  static int getSetBladeID(u32 partyId, int offset, bool isVirtual);
  static bool isBladeContorolable(u32 blade);
  static bool isBladeContorolable(u32 partyId, int slot);
  static GF_OBJ_HANDLE *getLeaderBladeHandle(bool isVirtual);
  static GF_OBJ_HANDLE *getBladeHandle(u32 partyId, u32 slot);
  static GF_OBJ_HANDLE *getBladeHandleFromPartySlot(u32 partyId, int offset, bool isVirtual);
  static GF_OBJ_HANDLE *getBladeHandleFromPartyBackSlot(u32 partyId, int offset, bool isVirtual);
  static u32 getBladeIDFromPartyBackSlot(u32 partyId, int offset, bool isVirtual);
  static GF_OBJ_HANDLE *getBladeHandleOffset(u32 partyId, int offset);
  static u32 getBladeSlotMax();
  static u16 getBladeFaceIconID(GF_OBJ_HANDLE *handle);
  static u16 getBladeFaceIconID(u32 blade);
  static u32 getBladeWeaponTypeIconID(u32 blade);
  static u32 getBladeAttributeIconID(u32 blade);
  static u16 getBladeCompatibilityIconID(u32 driver, u32 blade);
  static u32 getBladeAttributeID(u32 blade);
  static u32 getBladeRank(u32 blade);
  static bool isScenarioBlade(u32 blade);
  static u32 getBladeRarity(u32 blade);
  static bool isExtraBlade(u32 blade);
  static bool isBladeNoBuildWeapon(u32 blade);
  static bool isBladeCurrent(u32 blade);
  static u32 canRemoveBladeEx(u32 blade, u32 driver, const mm::mtl::FixedVector<u16, 422> *blades);
  static bool canRemoveBlade(u32 blade, const mm::mtl::FixedVector<u16, 422> *blades);
  static bool hasHomura(u32 driver);
  static u16 getMsgIDFromList(u32 bdat, u16 id);
  static bool checkCCStart(GfMenuCallContext *context);
  static bool checkCCNext(GfMenuCallContext *context, u32 menu);
  static u32 convIdeaPointToLevel(u32 point);
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
  static u8 getElementComboAtr(u32 combo);
  static u32 getElementComboEffect(u32 combo);
  static u8 getElementComboStage(u32 combo);
  static bool isQuestCompleted(QuestID quest);
  static bool getMenuCondition(u32 id);
  static bool getMenuFullOpenFlag();
  static bool isCustomEnableBlade(u32 blade);
};

} // namespace gf
