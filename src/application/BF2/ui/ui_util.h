#pragma once
#include "fw/fw_lang_util.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_curve.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace fw {
struct PadData;
class MemHandlebaseAllocator;
class PointerMap;
} // namespace fw

namespace mm {
struct Col4;
struct Vec2;

namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace ui {

class UIImageObject;
class UILayoutObject;
class UIObject;
class UIObjectAcc;
class UITextObject;

enum UIBdatType {
  UI_BDAT_RES_IMAGE = 0,
  UI_BDAT_RES_LAYOUT = 1,
  UI_BDAT_RES_FONT = 2,
  UI_BDAT_RES_FONT_STYLE = 3,
  UI_BDAT_RES_MSPROJ = 4,
  UI_BDAT_MENU_MS = 5,
  UI_BDAT_LAYER = 6,
  UI_BDAT_INPUT_PAD = 7,
  UI_BDAT_INPUT_WHEEL = 8,
  UI_BDAT_INPUT_POINTER = 9,
  UI_BDAT_INPUT_ACT = 10,
  UI_BDAT_TEXT_PROPERTY = 11,
  UI_BDAT_COLOR_LIST = 12,
  UI_BDAT_FACE_PATTERN_LIST = 13,
  UI_BDAT_RES_MOTION = 14,
  UI_BDAT_RES_UIO = 15,
  UI_BDAT_MAX = 16,
};

enum UIDockType {
  UI_DOCK_CENTER = 0,
  UI_DOCK_LEFT = 1,
  UI_DOCK_RIGHT = 2,
  UI_DOCK_TOP = 3,
  UI_DOCK_BOTTOM = 4,
};

class UIUtil {
public:
  static void initLayerLib();
  static void termLayerLib();
  static void initObjectMap(u32 size);
  static mm::mtl::IAllocator *getProgAllocator();
  static void termObjectMap();
  static u32 getObjectMapRegistNum();
  static u32 getObjectMapRegistMax();
  static u32 registObject(UIObject *object);
  static void releaseObject(u32 handle);
  static UIObject *getObject(u32 handle);
  static UILayoutObject *getLayoutObject(u32 handle);
  static UIImageObject *getImageObject(u32 handle);
  static UITextObject *getTextObject(u32 handle);
  static u32 getHandle(const UIObject *object);
  static u32 searchChild(u32 handle, const char *name);
  static void setDisp(u32 handle, bool disp);
  static void setDispChild(u32 handle, bool disp, const char *name);
  static bool isValid(u32 handle);
  static bool isTerm(u32 handle);
  static void drawDisplayRect(const UIObjectAcc &acc, const mm::Col4 &color);
  static void initBdatFP();
  static u8 *getBdatFP(u8 type);
  static void makeMenuFontDataFileName(mm::mtl::FixStr<128> &fileName, const char *name);
  static void makeMenuFontStyleFileName(mm::mtl::FixStr<128> &fileName, const char *name);
  static void makeMSProjFileName(mm::mtl::FixStr<128> &fileName, const char *name);
  static void makeMenuImageFileName(mm::mtl::FixStr<128> &fileName, const char *name);
  static void makeMenuLayoutFileName(mm::mtl::FixStr<128> &fileName, const char *name);
  static void makeMenuUIOFileName(mm::mtl::FixStr<128> &fileName, const char *name);
  static void makeMenuUIMFileName(mm::mtl::FixStr<128> &fileName, const char *name);
  static void makeMenuUIPFileName(mm::mtl::FixStr<128> &fileName, const char *name);
  static void makeMenuEnvFileName(mm::mtl::FixStr<128> &fileName, const char *name);
  static void setupAllocator(mtl::ALLOC_HANDLE parent);
  static void destoryAllocator();
  static mm::mtl::IAllocator *getResourceAllocator();
  static u32 getGroupPriority(u32 group);
  static u32 convUIPadToFWPad(int pad, bool withStick);
  static void mergeRect(const mm::Rect<s16> &first, const mm::Rect<s16> &second, mm::Rect<s16> &result);
  static void setSafeMergin(u32 width, u32 height);
  static void dispSafeRect();
  static bool adjustScreen(mm::Rect<s16> &rect);
  static bool adjustRect(mm::Rect<s16> &rect, mm::Rect<s16> &area);
  static u64 getUITime();
  static f32 timeUITimeToSec(u64 time);
  static u64 timeSecToUITime(f32 sec);
  static u32 getScreenWidth();
  static u32 getScreenHeight();
  static bool checkNumberTextFormat(const char *format, u32 count);
  static const UICtrlCurve *getCurve(CURVE_TYPE type);
  static const fw::PadData &getPadData();
  static void setDockPos(u32 handle, u32 target, u8 dock, bool global);
  static void calcFitScale(u32 handle, u32 target, mm::Vec2 &scale);
  static char getMoneySeparetor(fw::LangType lang);

  static fw::PointerMap s_ObjPtrMap;
  static u32 s_ObjPtrMax;
  static fw::MemHandlebaseAllocator s_ProgAllocator;
  static fw::MemHandlebaseAllocator s_ResAllocator;
  static u8 *s_BdatFPs[UI_BDAT_MAX];
  static u32 s_SafeMarginW;
  static u32 s_SafeMarginH;
};

} // namespace ui
