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
    OPTELOP_TYPE_UNKNOWN_0, // Inferred role: center; original name unknown.
    OPTELOP_TYPE_UNKNOWN_1, // Inferred role: left; original name unknown.
    OPTELOP_TYPE_UNKNOWN_2, // Inferred role: right; original name unknown.
  };

  enum {
    FLAG_UNKNOWN_0 = 1 << 0,                                                   // Inferred role: skip flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1,                                                   // Inferred role: common flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2,                                                   // Inferred role: common fade flag; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3,                                                   // Inferred role: field skill flag; original name unknown.
    FLAG_UNKNOWN_4 = 1 << 4,                                                   // Inferred role: shop flag; original name unknown.
    FLAG_UNKNOWN_5 = 1 << 5,                                                   // Inferred role: payoff flag; original name unknown.
    FLAG_UNKNOWN_6 = 1 << 6,                                                   // Inferred role: reward flag; original name unknown.
    FLAG_UNKNOWN_7 = 1 << 7,                                                   // Inferred role: blade name flag; original name unknown.
    FLAG_UNKNOWN_8 = 1 << 8,                                                   // Inferred role: chap telop flag; original name unknown.
    FLAG_UNKNOWN_9 = 1 << 9,                                                   // Inferred role: chap telop wait flag; original name unknown.
    FLAG_UNKNOWN_10 = 1 << 10,                                                 // Inferred role: avan title flag; original name unknown.
    FLAG_UNKNOWN_11 = 1 << 11,                                                 // Inferred role: zone telop flag; original name unknown.
    FLAG_UNKNOWN_12 = 1 << 12,                                                 // Inferred role: opening telop flag; original name unknown.
    FLAG_UNKNOWN_13 = 1 << 13,                                                 // Inferred role: staffroll flag; original name unknown.
    FLAG_UNKNOWN_14 = 1 << 14,                                                 // Inferred role: homura anm flag; original name unknown.
    FLAG_UNKNOWN_15 = 1 << 15,                                                 // Inferred role: name select flag; original name unknown.
    FLAG_UNKNOWN_16 = 1 << 16,                                                 // Inferred role: hikari anm flag; original name unknown.
    FLAG_UNKNOWN_114688 = FLAG_UNKNOWN_14 | FLAG_UNKNOWN_15 | FLAG_UNKNOWN_16, // Inferred role: homura hikari flag; original name unknown.
    FLAG_UNKNOWN_17 = 1 << 17,                                                 // Inferred role: new game wait flag; original name unknown.
    FLAG_UNKNOWN_18 = 1 << 18,                                                 // Inferred role: new game wait end flag; original name unknown.
    FLAG_UNKNOWN_19 = 1 << 19,                                                 // Inferred role: minigame flag; original name unknown.
    FLAG_UNKNOWN_20 = 1 << 20,                                                 // Inferred role: pad disable flag; original name unknown.
    FLAG_UNKNOWN_21 = 1 << 21,                                                 // Inferred role: pad enable wait flag; original name unknown.
  };

  enum {
    DISP_FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: now loading flag; original name unknown.
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
  bool openPayoffUI(const char *title, const mm::mtl::FixedVector<u32, 16> &values, const mm::mtl::FixedVector<const char *, 16> &names, const char *message);
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
  u32 unknown10;                    // Inferred role: flags; original member name unknown.
  u32 unknown14;                    // Inferred role: disp flags; original member name unknown.
  u32 unknown18;                    // Inferred role: state; original member name unknown.
  bool unknown1c;                   // Inferred role: field skill success; original member name unknown.
  gf::GfMenuCallContext *unknown20; // Inferred role: skip context; original member name unknown.
  gf::GfMenuCallContext *unknown28; // Inferred role: shop context; original member name unknown.
  gf::GfMenuCallContext *unknown30; // Inferred role: payoff context; original member name unknown.
  u32 m_payoffUI;
  gf::GfMenuCallContext *unknown40; // Inferred role: reward context; original member name unknown.
  gf::GfMenuCallContext *unknown48; // Inferred role: blade name context; original member name unknown.
  gf::GfMenuCallContext *unknown50; // Inferred role: chap telop context; original member name unknown.
  s32 unknown58;                    // Inferred role: chap telop wait; original member name unknown.
  gf::GfMenuCallContext *unknown60; // Inferred role: avan title context; original member name unknown.
  gf::GfMenuCallContext *unknown68; // Inferred role: zone telop context; original member name unknown.
  AnmF32 unknown70;                 // Inferred role: homura anm; original member name unknown.
  AnmF32 unknown180;                // Inferred role: hikari anm; original member name unknown.
  fw::UpdatableObject *unknown290;  // Inferred role: minigame; original member name unknown.
  s32 unknown298;                   // Inferred role: common wait; original member name unknown.
  s32 unknown29c;                   // Inferred role: skip wait; original member name unknown.
  s32 unknown2a0;                   // Inferred role: pad wait; original member name unknown.
};

static_assert(sizeof(UIManager) == 0x2a8, "");

} // namespace event
