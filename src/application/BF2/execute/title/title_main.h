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

  ai::Fsm unknown08;                       // Inferred role: state machine; original member name unknown.
  MicroUpdater<TitleMain> *unknown80;      // Inferred role: update thread; original member name unknown.
  fw::UpdateInfo unknown88;                // Inferred role: update info passed to the state machine; original member name unknown.
  bool unknown94;                          // Inferred role: finish request; original member name unknown.
  bool unknown95;                          // Inferred role: return to title request; original member name unknown.
  gf::SoundHandle unknown98;               // Inferred role: title bgm; original member name unknown.
  bool unknowna0;                          // Inferred role: play title bgm; original member name unknown.
  gf::SAVESLOT unknowna4;                  // Inferred role: slot to load for debug; original member name unknown.
  mm::mtl::FixStr<128> unknowna8;          // Inferred role: file to load for debug; original member name unknown.
  gf::SDataSave *unknown130;               // Inferred role: save buffer; original member name unknown.
  gf::SDataOption *unknown138;             // Inferred role: option buffer; original member name unknown.
  mm::mtl::FixedVector<u16, 8> unknown140; // Inferred role: events to play in the event theater; original member name unknown.
  TitleMenu unknown158;                    // Inferred role: title menu; original member name unknown.
  u32 unknown168;                          // Inferred role: event of the title; original member name unknown.
  gf::GF_SE_CATEGORY_HANDLE *unknown170;   // Inferred role: mask volume category; original member name unknown.
  bool unknown178;                         // Inferred role: game clear flag; original member name unknown.
};

static_assert(offsetof(TitleMain, unknown08) == 0x08, "");
static_assert(offsetof(TitleMain, unknown80) == 0x80, "");
static_assert(offsetof(TitleMain, unknown88) == 0x88, "");
static_assert(offsetof(TitleMain, unknown94) == 0x94, "");
static_assert(offsetof(TitleMain, unknown98) == 0x98, "");
static_assert(offsetof(TitleMain, unknowna0) == 0xa0, "");
static_assert(offsetof(TitleMain, unknowna4) == 0xa4, "");
static_assert(offsetof(TitleMain, unknowna8) == 0xa8, "");
static_assert(offsetof(TitleMain, unknown130) == 0x130, "");
static_assert(offsetof(TitleMain, unknown138) == 0x138, "");
static_assert(offsetof(TitleMain, unknown140) == 0x140, "");
static_assert(offsetof(TitleMain, unknown158) == 0x158, "");
static_assert(offsetof(TitleMain, unknown168) == 0x168, "");
static_assert(offsetof(TitleMain, unknown170) == 0x170, "");
static_assert(offsetof(TitleMain, unknown178) == 0x178, "");
static_assert(sizeof(TitleMain) == 0x180, "");

} // namespace tl
