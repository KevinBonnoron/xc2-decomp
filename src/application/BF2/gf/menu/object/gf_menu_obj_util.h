#pragma once
#include <stddef.h>

#include "gf/data/gf_data_driver.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace fw {
enum VibrationID : int;
enum SoundCategory : int;
} // namespace fw

namespace ui {
class UICtrlCursorSelect;
class UIListInfoBase;
class UIObjectAcc;
class UIStr;
} // namespace ui

namespace mm {
struct Col3;
struct Vec3;
} // namespace mm

namespace gf {

class DataParamAcc;
class GfMenuBladeList;
struct SDataIdea;
class GfMenuCallContext;
struct QuestID;
struct GfRequestBladeData;
struct GF_OBJ_HANDLE;
class SoundHandle;

class GfMenuObjUtil {
public:
  struct ArtsIconInfo {
    ArtsIconInfo() : unknown00(0), unknown04(0), unknown08(0), _0c(), unknown10(0) {}

    int unknown00; // Inferred role: icon type; original member name unknown.
    int unknown04; // Inferred role: enhance icon; original member name unknown.
    u32 unknown08; // Inferred role: reaction icon; original member name unknown.
    u8 _0c[0x10 - 0x0c];
    int unknown10; // Inferred role: range icon; original member name unknown.
  };

  struct FitOption {
    FitOption() : unknown00(false), unknown01(false), unknown02(false), unknown04(0, 0), unknown08(0, 0) {}

    bool unknown00;         // Inferred role: half size margin flag; original member name unknown.
    bool unknown01;         // Inferred role: keep scale x flag; original member name unknown.
    bool unknown02;         // Inferred role: keep scale y flag; original member name unknown.
    mm::Pnt<s16> unknown04; // Inferred role: expand; original member name unknown.
    mm::Pnt<u16> unknown08; // Inferred role: min size; original member name unknown.
  };

  struct DockingOption {
    u32 unknown00;           // Inferred role: align type; original member name unknown.
    mm::Pnt<s16> unknown04;  // Inferred role: offset; original member name unknown.
    mm::Rect<s16> unknown08; // Inferred role: area; original member name unknown.
  };

  // Inferred role: menu parameters; original type name unknown.
  struct unknown001 {
    f32 unknown00; // Inferred role: preset control time; original member name unknown.
    f32 unknown04; // Inferred role: preset control time of preset 6; original member name unknown.
    u8 _08[0x18 - 0x08];
    f32 unknown18; // Inferred role: delay of the blade change opening; original member name unknown.
  };

  struct CtrlParam {
    CtrlParam()
        : unknown00(0.0f), unknown04(0), unknown08(0), unknown0c(0), unknown10(false), unknown11(false), unknown12(false), unknown14(0), unknown18(-1), unknown1c(0.0f), unknown20(8), unknown2c(0.0f),
          unknown34(0.0f), unknown38(0.0f), unknown3c(0.0f) {}

    // Inferred helper: plays a motion of the common left/right fade motion data; original name unknown.
    void unknown004(const char *motion) {
      unknown08 = 0x10000000;
      unknown50 = "cmn_fade_motion_lr";
      unknown58 = motion;
    }

    f32 unknown00;  // Inferred role: control time, 0 for the motion length; original member name unknown.
    u32 unknown04;  // Inferred role: control direction, 1 in and 2 out; original member name unknown.
    u32 unknown08;  // Inferred role: method flags; original member name unknown.
    u32 unknown0c;  // Inferred role: curve; original member name unknown.
    bool unknown10; // Inferred role: control slot reservation flag; original member name unknown.
    bool unknown11; // Inferred role: set default flag; original member name unknown.
    bool unknown12; // Inferred role: relative to default flag; original member name unknown.
    u32 unknown14;  // Inferred role: loop flags; original member name unknown.
    int unknown18;  // Inferred role: control slot, -1 to reserve one; original member name unknown.
    f32 unknown1c;  // Inferred role: delay time; original member name unknown.
    int unknown20;  // Inferred role: move distance; original member name unknown.
    u8 _24[0x2c - 0x24];
    f32 unknown2c; // Inferred role: scale; original member name unknown.
    u8 _30[0x34 - 0x30];
    f32 unknown34; // Inferred role: rotation; original member name unknown.
    f32 unknown38; // Inferred role: brightness; original member name unknown.
    f32 unknown3c; // Inferred role: alpha; original member name unknown.
    f32 unknown40; // Inferred role: control parameter; original member name unknown.
    f32 unknown44; // Inferred role: control parameter; original member name unknown.
    f32 unknown48; // Inferred role: control parameter; original member name unknown.
    u8 _4c[0x50 - 0x4c];
    const char *unknown50; // Inferred role: motion data name; original member name unknown.
    const char *unknown58; // Inferred role: motion name; original member name unknown.
  };

  struct ImageParam {
    s16 unknown00; // Inferred role: offset x; original member name unknown.
    s16 unknown02; // Inferred role: offset y; original member name unknown.
    f32 unknown04; // Inferred role: scale; original member name unknown.
  };

  struct MissionInfo {
    u32 unknown00; // Inferred role: category; original member name unknown.
    u32 unknown04; // Inferred role: reward; original member name unknown.
    u32 unknown08; // Inferred role: map; original member name unknown.
    u32 unknown0c; // Inferred role: state flags; original member name unknown.
    u32 unknown10; // Inferred role: team; original member name unknown.
    u32 unknown14; // Inferred role: first field skill; original member name unknown.
    u32 unknown18; // Inferred role: second field skill; original member name unknown.
    u32 unknown1c; // Inferred role: third field skill; original member name unknown.
  };

  struct PresetCtrlParam {
    PresetCtrlParam() : unknown00(0), unknown04(0), unknown08(-1), unknown10(0), unknown18(nullptr) {
      unknown0c = false;
      unknown0d = false;
    }

    u32 unknown00;         // Inferred role: preset; original member name unknown.
    u32 unknown04;         // Inferred role: direction, 0 in and 1 out; original member name unknown.
    int unknown08;         // Inferred role: control parameter; original member name unknown.
    bool unknown0c;        // Inferred role: control flag; original member name unknown.
    bool unknown0d;        // Inferred role: control flag; original member name unknown.
    u32 unknown10;         // Inferred role: control type; original member name unknown.
    const char *unknown18; // Inferred role: animation name; original member name unknown.
  };

  static s16 getBtnIconNumber(u32 button);
  static u32 getFavoriteStat(u32 objType, u32 id, FAVORITE favorite);
  static u32 getPadSelectIconNumber(u32 select);
  static u32 getPointerSelectIconNumber();
  static int setCommonFadeIn(u32 handle, u32 fade, u8 unknown);
  static int setCommonFadeOut(u32 handle, u32 fade, u8 unknown);
  static int startCtrl(u32 handle, const CtrlParam &param, const char *child);
  static void setPresetCtrl_Fadein(u32 preset, CtrlParam &param, int slot);
  static void setPresetCtrl_Fadeout(u32 preset, CtrlParam &param, int slot);
  static int startPresetCtrl(u32 handle, const PresetCtrlParam &param);
  static void setChildDisp(u32 handle, const char *name, bool disp);
  static void setChildMulColor(u32 handle, const char *name, const char *color);
  static void setChildAddColor(u32 handle, const char *name, const char *color);
  static u32 getMissionCondBladeCount(const GfRequestBladeData &data, const GfMenuBladeList *list);
  static bool checkMissionCond(u32 mission, const GfMenuBladeList *list);
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
  static f32 getPresetCtrlTime(u32 preset);
  static void setColMulandAdd(u32 handle, const char *color);
  static void createDockPlugin(u32 handle, u32 target, u32 dockType, const mm::Pnt<s16> &offset, u32 alignType);
  static void createDockPluginEx(u32 handle, u32 target, u32 dockType, const DockingOption &option);
  static void createFitPlugin(u32 handle, u32 target, int marginX, int marginY, const FitOption &option);
  static void createVScrollBarPlugin(u32 handle, ui::UIListInfoBase *list, const char *barName, bool isScaleEnable);
  static void createHScrollBarPlugin(u32 handle, ui::UIListInfoBase *list, const char *barName);
  static void createFollowDispPlugin(u32 handle, u32 target);
  static void createSyncPlugin(u32 handle, u32 target, u32 flags);
  static void createNumberPlugin(u32 handle, int number);
  static const unknown001 *getParamMenu();
  static f32 getCtrlMotionTime(const char *name, const char *motion);
  static void changeCursorTarget(ui::UICtrlCursorSelect *cursor, u32 handle, const char *format);
  static void changeCursorTarget(ui::UICtrlCursorSelect *cursor, u32 handle, const char **names, u16 count);
  static const char *getMenuMS(u32 id);
  static u32 getLeaderPartyID();
  static int getLeaderPartyType();
  static bool isExitDriver(u32 partyId);
  static u32 setupPartyDriver(const mm::mtl::FixedVector<u16, 16> &drivers);
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
  static u32 getBladeIDFromDriverSlot(u32 driver, int slot);
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
  static bool isBladeAchivementReleased(u32 blade);
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
  static u32 playBGM(u32 bgm, bool ignorePause, fw::SoundCategory category);
  static bool isValidSoundHandle(u32 handle);
  static void stopBGM(u32 handle, f32 time);
  static SoundHandle playJingle(u32 id);
  static void playVibration(fw::VibrationID id, f32 amplitude);
  static bool getBladeTeamName(u32 blade, ui::UIStr &name);
  static int getFaceIconID(const DataParamAcc &acc);
  static ui::UIStr getName(const DataParamAcc &acc);
  static bool isInBattle(GF_OBJ_HANDLE *handle);
  static ui::UIStr getEnemyArtsName(u32 arts);
  static ui::UIStr getDriverClassName(u32 driver);
  static ui::UIStr getElementComboName(u32 combo);
  static ui::UIStr getElementComboEffectName(u32 combo);
  static u8 getElementComboAtr(u32 combo);
  static u8 getElementComboEffect(u32 combo);
  static u8 getElementComboStage(u32 combo);
  static bool isQuestCompleted(QuestID quest);
  static bool getMenuCondition(u32 id);
  static bool getMissionInfo(u32 mission, MissionInfo &info);
  static bool getScreenPos(mm::Vec3 &screenPos, const mm::Vec3 &position);
  static void convViewSpace(mm::Vec3 &viewPos, const mm::Vec3 &position);
  static void placeObjectHLeft(u32 handle, const char *format, u32 count, const mm::Pnt<s16> &pos, u32 interval);
  static void placeObjectHRatio(u32 handle, u32 target, f32 ratio, s16 margin);
  static QuestID getCurrentQuest(u32 type);
  static bool getMenuFullOpenFlag();
  static bool isCustomEnableBlade(u32 blade);
  static int convMenuDriverID(u32 driver);
  static int convMenuBladeID(u32 blade);
  static int getDriverClassBuffRatio(u32 driverClass, u32 index);
  static u32 getDriverClassBuffType(u32 driverClass, u32 index);
  static u32 getDriverClassBuffLv(u32 driverClass, u32 index);
  static bool isBladeSelectable(u32 blade, const GfMenuBladeList *list);
  static bool isBladeReleasable(u32 blade, const GfMenuBladeList *list);
  static bool getImageParam(u32 type, u32 id, ImageParam &param, u32 index);
  static const mm::Col3 &getPresetColor(const char *name);
  static mm::Col3 getElementColor(u32 combo);
  static bool setPointSpeedRate(ui::UIObjectAcc acc, f32 rate);

  // Inferred helper: starts the preset 6 fade in control on a UI object; original name unknown.
  static int unknown002(u32 handle) {
    PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 0;
    param.unknown10 = 1;
    return startPresetCtrl(handle, param);
  }

  // Inferred helper: starts the preset 6 fade out control on a UI object; original name unknown.
  static int unknown003(u32 handle) {
    PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 1;
    param.unknown10 = 2;
    return startPresetCtrl(handle, param);
  }
};

static_assert(offsetof(GfMenuObjUtil::DockingOption, unknown04) == 0x04, "");
static_assert(offsetof(GfMenuObjUtil::DockingOption, unknown08) == 0x08, "");
static_assert(sizeof(GfMenuObjUtil::DockingOption) == 0x10, "");
static_assert(offsetof(GfMenuObjUtil::ImageParam, unknown04) == 0x04, "");
static_assert(sizeof(GfMenuObjUtil::ImageParam) == 0x08, "");
static_assert(offsetof(GfMenuObjUtil::unknown001, unknown04) == 0x04, "");
static_assert(offsetof(GfMenuObjUtil::unknown001, unknown18) == 0x18, "");
static_assert(offsetof(GfMenuObjUtil::FitOption, unknown04) == 0x04, "");
static_assert(offsetof(GfMenuObjUtil::FitOption, unknown08) == 0x08, "");
static_assert(sizeof(GfMenuObjUtil::FitOption) == 0x0c, "");
static_assert(offsetof(GfMenuObjUtil::PresetCtrlParam, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuObjUtil::PresetCtrlParam, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjUtil::PresetCtrlParam, unknown0d) == 0x0d, "");
static_assert(offsetof(GfMenuObjUtil::PresetCtrlParam, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjUtil::PresetCtrlParam, unknown18) == 0x18, "");
static_assert(sizeof(GfMenuObjUtil::PresetCtrlParam) == 0x20, "");
static_assert(offsetof(GfMenuObjUtil::CtrlParam, unknown04) == 0x04, "");
static_assert(offsetof(GfMenuObjUtil::CtrlParam, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuObjUtil::CtrlParam, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjUtil::CtrlParam, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjUtil::CtrlParam, unknown11) == 0x11, "");
static_assert(offsetof(GfMenuObjUtil::CtrlParam, unknown12) == 0x12, "");
static_assert(offsetof(GfMenuObjUtil::CtrlParam, unknown14) == 0x14, "");
static_assert(offsetof(GfMenuObjUtil::CtrlParam, unknown18) == 0x18, "");
static_assert(offsetof(GfMenuObjUtil::CtrlParam, unknown1c) == 0x1c, "");
static_assert(offsetof(GfMenuObjUtil::CtrlParam, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjUtil::CtrlParam, unknown2c) == 0x2c, "");
static_assert(offsetof(GfMenuObjUtil::CtrlParam, unknown34) == 0x34, "");
static_assert(offsetof(GfMenuObjUtil::CtrlParam, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjUtil::CtrlParam, unknown3c) == 0x3c, "");
static_assert(offsetof(GfMenuObjUtil::CtrlParam, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjUtil::CtrlParam, unknown58) == 0x58, "");
static_assert(sizeof(GfMenuObjUtil::CtrlParam) == 0x60, "");

} // namespace gf
