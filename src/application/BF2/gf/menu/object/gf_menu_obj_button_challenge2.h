#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_simple.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjButtonChallenge2 : public GfMenuObject {
public:
  // Layout from the open overload with two bool arguments (0x7100420938): its arguments fill the first two members and the constant 0.25 the last one.
  struct OptionParam {
    bool unknown00; // Inferred role: display the button (isDispButton argument of open); original member name unknown.
    bool unknown01; // Inferred role: play the sound (isSound argument of open); original member name unknown.
    bool unknown02; // Role and original member name unknown.
    f32 unknown04;  // Inferred role: constant 0.25 set by open, a time; original member name unknown.
  };

  // Inferred role: one challenge of the open parameter; original name unknown.
  struct unknown002 {
    u8 unknown00;  // Role and original member name unknown.
    u8 unknown01;  // Role and original member name unknown.
    u8 unknown02;  // Role and original member name unknown.
    u16 unknown04; // Role and original member name unknown.
    u16 unknown06; // Role and original member name unknown.
    u8 unknown08;  // Role and original member name unknown.
    u16 unknown0a; // Role and original member name unknown.
    u16 unknown0c; // Role and original member name unknown.
    u16 unknown0e; // Role and original member name unknown.
    u16 unknown10; // Role and original member name unknown.
    u16 unknown12; // Role and original member name unknown.
  };

  struct OpenParam {
    OpenParam() : unknown00(0), unknown02(0), unknown04(false), unknown50{false, true, false, 0.25f} {}

    u16 unknown00;                                 // Role and original member name unknown.
    u16 unknown02;                                 // Role and original member name unknown.
    bool unknown04;                                // Role and original member name unknown.
    mm::mtl::FixedVector<unknown002, 3> unknown08; // Inferred role: challenges; original member name unknown.
    OptionParam unknown50;                         // Inferred role: display options; original member name unknown.
  };

  ~GfMenuObjButtonChallenge2() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void open(GfMenuCallContext *context, const OpenParam &param, unsigned int sequence);
  static bool isValidParam(const OpenParam &param);
  static void open(GfMenuCallContext *context, unsigned int challenge, bool isDispButton, bool isSound);
  static void open(GfMenuCallContext *context, unsigned int challenge, const OptionParam &option);
  static void importOpenParam(OpenParam &param, unsigned int challenge);
  static void openSequence(GfMenuCallContext *context, unsigned int challenge, bool isDispButton, bool isSound);
  static void openSequence(GfMenuCallContext *context, unsigned int challenge, const OptionParam &option);
  static void resume(GfMenuCallContext *context);
  static void close(GfMenuCallContext *context);
  void setup(const OpenParam &param, unsigned int challenge, bool);
  void setupV2(const OpenParam &param);
  bool seqStart();
  bool seqRunningV2();
  bool seqAppearCursor();
  bool seqCheckSequence();
  bool seqWaitRestartV2();
  bool seqWaitMashingV2();
  void nextChallenge();
  static void dispRelationHUD(bool);
  static void setSpeedFactor(GfMenuCallContext *context, f32 speedFactor);
  u32 getResultPoint() const;
  void stopSeqCtrl();
  bool seqEnd();
  void notifyChallengeResult();
  bool getChallengeMashingWait(u32 &wait);
  void setRingScale(f32 scale);
  void setRingScaleV2(u32 index, f32 scale);
  void updateChallenge();
  bool isSeqCtrlBusy();

  u8 _24[0x28 - 0x24];
  OpenParam unknown28;                                     // Inferred role: parameter of the running challenge; original member name unknown.
  u32 unknown80;                                           // Inferred role: current challenge; original member name unknown.
  u32 unknown84;                                           // Role and original member name unknown, cleared by the constructor.
  int unknown88;                                           // Role and original member name unknown, cleared by the constructor.
  u32 unknown8c;                                           // Role and original member name unknown, cleared by the constructor.
  int unknown90;                                           // Inferred role: challenge in progress; original member name unknown.
  u32 unknown94;                                           // Inferred role: number of challenges done before the current one; original member name unknown.
  u32 unknown98;                                           // Inferred role: points gained; original member name unknown.
  f32 unknown9c;                                           // Role and original member name unknown, 1.0 at start.
  GfMenuSequence<GfMenuObjButtonChallenge2, 8> unknown0a0; // Inferred role: queued steps; original member name unknown.
  mm::mtl::FixedVector<int, 4> unknown330;                 // Inferred role: running controls; original member name unknown.
  mm::mtl::FixedVector<f32, 2> unknown348;                 // Role and original member name unknown.
  bool unknown358;                                         // Role and original member name unknown, cleared by the constructor.
  bool unknown359;                                         // Inferred role: challenge result notified flag; original member name unknown, cleared by the constructor.
  u16 unknown35a;                                          // Role and original member name unknown, cleared by the constructor.
  u16 unknown35c;                                          // Role and original member name unknown.
  u16 unknown35e;                                          // Role and original member name unknown.
  mm::Pnt<s16> unknown360;                                 // Inferred role: center of the ring; original member name unknown.
  u8 _364[0x368 - 0x364];
  ui::UICtrlSimple<1> unknown368;                          // Role and original member name unknown.
  ui::UICtrlSimpleUpdater<ui::UICtrlSimple<1>> unknown390; // Role and original member name unknown.
  s16 unknown3b0;                                          // Inferred role: minimum ring size; original member name unknown.
  s16 unknown3b2;                                          // Inferred role: maximum ring size; original member name unknown.
  u8 _3b4[0x3b8 - 0x3b4];
  ui::UICtrlSimple<1> unknown3b8;                          // Role and original member name unknown.
  ui::UICtrlSimpleUpdater<ui::UICtrlSimple<1>> unknown3e0; // Role and original member name unknown.
  ui::UICtrlSimple<1> unknown400;                          // Role and original member name unknown.
  ui::UICtrlSimpleUpdater<ui::UICtrlSimple<1>> unknown428; // Role and original member name unknown.
  ui::UICtrlSimple<1> unknown448;                          // Role and original member name unknown.
  ui::UICtrlSimpleUpdater<ui::UICtrlSimple<1>> unknown470; // Role and original member name unknown.
  u32 unknown490;                                          // Role and original member name unknown, cleared by the constructor.
  f32 unknown494;                                          // Role and original member name unknown, cleared by the constructor.
  u32 unknown498;                                          // Role and original member name unknown, cleared by the constructor.
  u32 unknown49c;                                          // Role and original member name unknown, cleared by the constructor.
  bool unknown4a0;                                         // Role and original member name unknown, cleared by the constructor.
  u8 _4a1[0x4a8 - 0x4a1];
};

static_assert(offsetof(GfMenuObjButtonChallenge2::OptionParam, unknown04) == 0x4, "");
static_assert(sizeof(GfMenuObjButtonChallenge2::OptionParam) == 0x8, "");
static_assert(sizeof(GfMenuObjButtonChallenge2::unknown002) == 0x14, "");
static_assert(offsetof(GfMenuObjButtonChallenge2::OpenParam, unknown08) == 0x8, "");
static_assert(offsetof(GfMenuObjButtonChallenge2::OpenParam, unknown50) == 0x50, "");
static_assert(sizeof(GfMenuObjButtonChallenge2::OpenParam) == 0x58, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown80) == 0x80, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown90) == 0x90, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown94) == 0x94, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown98) == 0x98, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown9c) == 0x9c, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown0a0) == 0xa0, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown330) == 0x330, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown348) == 0x348, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown358) == 0x358, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown360) == 0x360, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown368) == 0x368, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown390) == 0x390, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown3b0) == 0x3b0, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown3b8) == 0x3b8, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown3e0) == 0x3e0, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown400) == 0x400, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown428) == 0x428, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown448) == 0x448, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown470) == 0x470, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown490) == 0x490, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown4a0) == 0x4a0, "");
static_assert(sizeof(GfMenuObjButtonChallenge2) == 0x4a8, "");

} // namespace gf
