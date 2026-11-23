#pragma once
#include <stddef.h>

#include "ai/ai_state_fsm.h"
#include "execute/title/title_menu.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_data_save.h"
#include "gf/sound/gf_sound.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {
class MLTHG;
} // namespace ml
namespace nn {
namespace os {
struct FiberType;
} // namespace os
} // namespace nn

namespace gf {
struct SDataOption;
struct SDataSave;
struct GF_SE_CATEGORY_HANDLE;
} // namespace gf

// Template known from the game symbol MicroUpdater<tl::TitleMain>::fnMicroUpdate(void*): it holds the micro thread of an owner and calls its update function.
template <typename T> struct MicroUpdater {
  MicroUpdater() : unknown00(reinterpret_cast<ml::MLTHG *>(-1)), unknown08(-1), unknown10(nullptr) {}

  static nn::os::FiberType *fnMicroUpdate(void *);

  ml::MLTHG *unknown00;                   // Inferred role: group; original member name unknown.
  u64 unknown08;                          // Inferred role: thread handle; original member name unknown.
  T *unknown10;                           // Inferred role: owner; original member name unknown.
  mm::mtl::Delegate<void(T *)> unknown18; // Inferred role: update function; original member name unknown.
};

namespace tl {

class TitleMain : public mm::mtl::PtrSingleton<TitleMain> {
public:
  TitleMain();
  ~TitleMain() override;
  static TitleMain *create();
  void initialize();
  static void destroy();
  void finalize();
  void createSaveBuffer();
  static void fnUpdate(TitleMain *main);
  void destroyMaskVolume();
  void stopTitleBGM(f32 fadeTime);
  void destroySaveBuffer();
  static void update(const fw::UpdateInfo &info);
  static void sleep(u32 frame);
  static void returnTitle(gf::SAVESLOT slot);
  bool isStateGame() const;
  bool isStateEvent() const;
  bool isStateSelect() const;
  void setMaskVolume(f32 volume, f32 fadeTime);
  static void returnTitle(const char *name);
  static bool isReturnTitle();
  void playTitleBGM();
  bool isStateReturnTitle() const;
  gf::SDataSave *getSaveBuffer();
  gf::SDataOption *getOptionBuffer();
  void clearSaveBuffer();
  void setupTitleOptionToGameOption();
  u32 getChapterIdFromSaveData();
  void playTitleEvent(u32 event);
  u32 getPlayTitleEvent();
  void getGameClearFlagFromSaveData();

  ai::Fsm m_fsm;                           // Inferred role: state machine; original member name unknown.
  MicroUpdater<TitleMain> *unknown80;      // Inferred role: update thread; original member name unknown.
  fw::UpdateInfo m_updateInfo;             // Inferred role: update info passed to the state machine; original member name unknown.
  bool unknown94;                          // Inferred role: finish request; original member name unknown.
  bool unknown95;                          // Inferred role: return to title request; original member name unknown.
  gf::SoundHandle m_soundHandle;           // Inferred role: title bgm; original member name unknown.
  bool unknowna0;                          // Inferred role: play title bgm; original member name unknown.
  gf::SAVESLOT unknowna4;                  // Inferred role: slot to load for debug; original member name unknown.
  mm::mtl::FixStr<128> unknowna8;          // Inferred role: file to load for debug; original member name unknown.
  gf::SDataSave *m_saveBuffer;             // Inferred role: save buffer; named after the game accessor tl::TitleMain::getSaveBuffer.
  gf::SDataOption *m_optionBuffer;         // Inferred role: option buffer; named after the game accessor tl::TitleMain::getOptionBuffer.
  mm::mtl::FixedVector<u16, 8> unknown140; // Inferred role: events to play in the event theater; original member name unknown.
  TitleMenu m_titleMenu;                   // Inferred role: title menu; original member name unknown.
  u32 m_playTitleEvent;                    // Inferred role: event of the title; named after the game accessor tl::TitleMain::getPlayTitleEvent.
  gf::GF_SE_CATEGORY_HANDLE *unknown170;   // Inferred role: mask volume category; original member name unknown.
  bool unknown178;                         // Inferred role: game clear flag; original member name unknown.
};

static_assert(offsetof(TitleMain, m_fsm) == 0x08, "");
static_assert(offsetof(TitleMain, unknown80) == 0x80, "");
static_assert(offsetof(TitleMain, m_updateInfo) == 0x88, "");
static_assert(offsetof(TitleMain, unknown94) == 0x94, "");
static_assert(offsetof(TitleMain, m_soundHandle) == 0x98, "");
static_assert(offsetof(TitleMain, unknowna0) == 0xa0, "");
static_assert(offsetof(TitleMain, unknowna4) == 0xa4, "");
static_assert(offsetof(TitleMain, unknowna8) == 0xa8, "");
static_assert(offsetof(TitleMain, m_saveBuffer) == 0x130, "");
static_assert(offsetof(TitleMain, m_optionBuffer) == 0x138, "");
static_assert(offsetof(TitleMain, unknown140) == 0x140, "");
static_assert(offsetof(TitleMain, m_titleMenu) == 0x158, "");
static_assert(offsetof(TitleMain, m_playTitleEvent) == 0x168, "");
static_assert(offsetof(TitleMain, unknown170) == 0x170, "");
static_assert(offsetof(TitleMain, unknown178) == 0x178, "");
static_assert(sizeof(TitleMain) == 0x180, "");

} // namespace tl
