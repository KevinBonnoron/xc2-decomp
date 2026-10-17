#pragma once

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

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
};

} // namespace ml
