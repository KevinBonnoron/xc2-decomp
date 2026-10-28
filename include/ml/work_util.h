#pragma once
#include "ml/work_root.h"
#include "mtl/alloc_handle.h"

namespace ml {

class WorkObj;

namespace _wkut {

extern bool s_bDispLogH;

} // namespace _wkut

class WorkUtil {
public:
  static mtl::ALLOC_HANDLE getWorkMem();
  static void setDispLogH(bool isDisp);
  static bool isDispLogH();
  static bool isTopOfParent(const WorkObj *work);
  static bool searchWork(const WorkObj *parent, const WorkObj *work);
  static bool hasChild(WorkObj *parent, const char *name);
  static void dispTree(const WorkObj *work, int depth);

  template <typename T> static T *createWork(const char *name, WorkObj *parent, bool isFront) {
    T *work = new (WorkRootState::getWorkMem()) T(name, parent);
    WorkRootState::entryWork(work, parent, isFront);
    return work;
  }
};

} // namespace ml
