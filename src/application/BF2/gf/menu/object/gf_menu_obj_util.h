#pragma once
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace ui {
class UIStr;
} // namespace ui

namespace mm {
struct Vec3;
}

namespace gf {

class DataParamAcc;
class GfMenuBladeList;
struct SDataIdea;
class GfMenuCallContext;
struct QuestID;
struct GF_OBJ_HANDLE;

class GfMenuObjUtil {
public:
  struct ArtsIconInfo {
    ArtsIconInfo() : unknown00(0), unknown04(0), unknown08(0), _0c(), unknown10(0) {}

    int unknown00; // Inferred role: icon type; original member name unknown.
    int unknown04; // Inferred role: enhance icon; original member name unknown.
    int unknown08; // Inferred role: reaction icon; original member name unknown.
    u8 _0c[0x10 - 0x0c];
    int unknown10; // Inferred role: range icon; original member name unknown.
  };

  static u32 getBtnIconNumber(u32 button);
  static u32 getPadSelectIconNumber(u32 select);
  static u32 getPointerSelectIconNumber();
  static void setCommonFadeOut(u32 handle, u32 fade, u8 unknown);
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
  static u32 getBladeIDFromPartySlot(u32 partyId, int offset, bool isVirtual);
  static GF_OBJ_HANDLE *getBladeHandleOffset(u32 partyId, int offset);
  static u32 getBladeSlotMax();
  static u32 getBladeCorrectiveType(u32 blade);
  static u32 getBladeCorrectiveRatio(u32 blade);
  static bool isBladeDifferentImage(u32 blade, u32 other);
  static void getIdeagramDriver(u32 driver, SDataIdea &idea);
  static void getIdeagramBlade(u32 blade, SDataIdea &idea);
  static void getIdeagramDriverFromHandle(GF_OBJ_HANDLE *handle, SDataIdea &idea);
  static int getDriverPartyID(u32 driver);
  static u16 getBladeFaceIconID(GF_OBJ_HANDLE *handle);
  static u16 getBladeFaceIconID(u32 blade);
  static u32 getBladeWeaponTypeIconID(u32 blade);
  static u16 getBladeAttributeIconID(u32 blade);
  static u16 getBladeRareIconID(u32 blade);
  static bool isEnemyBoss(GF_OBJ_HANDLE *handle);
  static bool isEnemyNamed(GF_OBJ_HANDLE *handle);
  static void setColDefault(u32 handle);
  static u16 getBladeCompatibilityIconID(u32 driver, u32 blade);
  static u16 getBladeAttributeID(u32 blade);
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
  static bool getArtsIconInfo(u32 arts, u32 level, ArtsIconInfo &info);
  static int getEnableArts(mm::mtl::FixedArray<u32, 4> &arts, u32 driver, u32 weaponType);
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
  static bool getBladeTeamName(u32 blade, ui::UIStr &name);
  static int getFaceIconID(const DataParamAcc &acc);
  static ui::UIStr getEnemyArtsName(u32 arts);
  static ui::UIStr getDriverClassName(u32 driver);
  static ui::UIStr getElementComboName(u32 combo);
  static ui::UIStr getElementComboEffectName(u32 combo);
  static u8 getElementComboAtr(u32 combo);
  static u8 getElementComboEffect(u32 combo);
  static u8 getElementComboStage(u32 combo);
  static bool isQuestCompleted(QuestID quest);
  static bool getMenuCondition(u32 id);
  static bool getScreenPos(mm::Vec3 &screenPos, const mm::Vec3 &position);
  static bool getMenuFullOpenFlag();
  static bool isCustomEnableBlade(u32 blade);
  static int convMenuDriverID(u32 driver);
  static int convMenuBladeID(u32 blade);
  static int getDriverClassBuffRatio(u32 driverClass, u32 index);
  static u8 getDriverClassBuffLv(u32 driverClass, u32 index);
  static bool isBladeSelectable(u32 blade, const GfMenuBladeList *list);
  static bool isBladeReleasable(u32 blade, const GfMenuBladeList *list);
};

} // namespace gf
