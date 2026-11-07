#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjOperationInfo : public GfMenuObject {
public:
  static void open(u32 handle, u32 unknown0, u32 unknown1, u32 unknown2);
  static void close();
  static void setDisp(bool isDisp);
  static void setGuideText(u32 param0, u32 param1);
  static void setGuideDisp(bool param0);
  static void add(u32 param0, u32 param1, u32 param2, u32 param3);
  static void remove(u32 param0, u32 param1, u32 param2, u32 param3);
  static void changeText(u32 param0, u32 param1, bool param2);
  static void changeText(u32 param0, u32 param1, u32 param2);
  static void setActionEnable(u32 param0, u32 param1, bool param2);
  static void moveGuide(u32 param0, bool param1);
  static void fadeGuide(bool param0);
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf
