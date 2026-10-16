#pragma once
#include "event/anm_f32.h"
#include "event/i_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
class UpdatableObject;
}

namespace gf {
class GfMenuCallContext;
}

namespace event {

class UIManager : public IManager, public mm::mtl::Singleton<UIManager> {
public:
  enum OPTELOP_TYPE {
    OPTELOP_TYPE_CENTER,
    OPTELOP_TYPE_LEFT,
    OPTELOP_TYPE_RIGHT,
  };

  enum {
    FLAG_SKIP = 1 << 0,
    FLAG_COMMON = 1 << 1,
    FLAG_COMMON_FADE = 1 << 2,
    FLAG_FIELD_SKILL = 1 << 3,
    FLAG_SHOP = 1 << 4,
    FLAG_PAYOFF = 1 << 5,
    FLAG_REWARD = 1 << 6,
    FLAG_BLADE_NAME = 1 << 7,
    FLAG_CHAP_TELOP = 1 << 8,
    FLAG_CHAP_TELOP_WAIT = 1 << 9,
    FLAG_AVAN_TITLE = 1 << 10,
    FLAG_ZONE_TELOP = 1 << 11,
    FLAG_OPENING_TELOP = 1 << 12,
    FLAG_STAFFROLL = 1 << 13,
    FLAG_HOMURA_ANM = 1 << 14,
    FLAG_NAME_SELECT = 1 << 15,
    FLAG_HIKARI_ANM = 1 << 16,
    FLAG_HOMURA_HIKARI = FLAG_HOMURA_ANM | FLAG_NAME_SELECT | FLAG_HIKARI_ANM,
    FLAG_NEW_GAME_WAIT = 1 << 17,
    FLAG_NEW_GAME_WAIT_END = 1 << 18,
    FLAG_MINIGAME = 1 << 19,
    FLAG_PAD_DISABLE = 1 << 20,
    FLAG_PAD_ENABLE_WAIT = 1 << 21,
  };

  enum {
    DISP_FLAG_NOW_LOADING = 1 << 0,
  };

  void setPadDisable(bool isDisable);
  UIManager();
  virtual ~UIManager() {}
  void logout();
  void clear();
  void update();
  void render();
  virtual void OnEventProc(MSG_TYPE type);
  bool openSkip(bool &isSkip);
  void closeSkip();
  bool isOpenSkipUI() const;
  bool openCommonUI(u32 window);
  bool isOpenCommonUI() const;
  bool execFieldSkill(u32 fieldSkill, bool &isSuccess);
  bool isFieldSkill() const;
  bool openShopUI(u32 shop, bool &isBought);
  bool isOpenShopUI() const;
  bool openPayoffUI(const char *title, const mm::mtl::FixedVector<u32, 16> &values, const mm::mtl::FixedVector<const char *, 16> &names,
                    const char *message);
  u32 getPayoffUI() const;
  bool isOpenPayoffUI() const;
  bool openRewardUI(u32 item);
  bool isOpenRewardUI() const;
  void openBladeNameUI();
  bool openChapTelopUI(u32 chapter);
  bool isOpenChapTelopUI() const;
  void openAvanTitleUI(u32 title);
  void closeAvanTitleUI(int title);
  bool isAvanTitleUI() const;
  void openZoneTelopUI(u32 zone);
  void closeZoneTelopUI();
  bool isZoneTelopUI() const;
  void startOpeningTelop();
  void openOpeningTelopUI(OPTELOP_TYPE type, u32 telop);
  void closeOpeningTelopUI(OPTELOP_TYPE type);
  void openStaffroll();
  void startStaffrollUI(f32 frame, int type);
  void endStaffroll();
  bool openHomuraHikariUI();
  bool isOpenHomuraHikariUI() const;
  bool startNewGameWait();
  void finishNewGameWait();
  bool isNewGameWait() const;
  bool openMinigame();
  bool isOpenMinigame() const;
  void setDispNowLoading(bool isDisp);

private:
  u32 flags;
  u32 dispFlags;
  u32 state;
  bool isFieldSkillSuccess;
  gf::GfMenuCallContext *skipContext;
  gf::GfMenuCallContext *shopContext;
  gf::GfMenuCallContext *payoffContext;
  u32 payoffResult;
  gf::GfMenuCallContext *rewardContext;
  gf::GfMenuCallContext *bladeNameContext;
  gf::GfMenuCallContext *chapTelopContext;
  s32 chapTelopWait;
  gf::GfMenuCallContext *avanTitleContext;
  gf::GfMenuCallContext *zoneTelopContext;
  AnmF32 homuraAnm;
  AnmF32 hikariAnm;
  fw::UpdatableObject *minigame;
  s32 commonWait;
  s32 skipWait;
  s32 padWait;
};

static_assert(sizeof(UIManager) == 0x2a8, "");

} // namespace event
