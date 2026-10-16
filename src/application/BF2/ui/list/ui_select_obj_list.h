#pragma once
#include "types.h"
#include "ui/list/ui_list_info.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace ui {

class UISelectObjList : public UIListInfo<u32> {
public:
  struct CreateParam {
    mm::mtl::IAllocator *allocator;
  };

  UISelectObjList();
  virtual ~UISelectObjList();

  static UISelectObjList *create(const CreateParam &param);
  void setObject(u32 index, u32 handle);
  void addObject(u32 handle);
  void insertObject(u32 index, u32 handle);
  void delObject(u32 handle);
  void pickupObject(u32 parent, const char *format, u32 start);
  u32 getObject(u32 index);
  u32 getSelectObject();
};

static_assert(sizeof(UISelectObjList) == 0x68, "");

} // namespace ui
