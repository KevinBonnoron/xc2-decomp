#pragma once
#include <stddef.h>

namespace ml {
class DrMan;
class DrShdDataList;
class DrShdFetchMan;
class DrShdLgtMan;
class DrShdMdoMan;

class DrShdMan {
public:
  DrShdMan(DrMan *drMan);
  ~DrShdMan();
  void beginUpdate();
  void debugRender();
  void setupCate(int cate);
  void beforeUpdateCate(int cate);
  void updateCate(int cate);
  void addViewInfo(int cate);
  void delViewInfo(int cate);
  void resetColorBuff(int index);

  DrShdDataList *m_drShdDataList; // Inferred role: data list; original member name unknown.
  DrShdMdoMan *m_drShdMdoMan;     // Inferred role: mdo man; original member name unknown.
  DrShdFetchMan *m_drShdFetchMan; // Inferred role: fetch man (DrShdMdoDecRes::releaseObj 0x71008a152c); original member name unknown.
  DrShdLgtMan *m_drShdLgtMan;     // Inferred role: lgt man; original member name unknown.
  DrMan *m_drMan;                 // Inferred role: dr man; original member name unknown.
};

static_assert(offsetof(DrShdMan, m_drShdMdoMan) == 0x08, "");
static_assert(offsetof(DrShdMan, m_drShdFetchMan) == 0x10, "");
static_assert(offsetof(DrShdMan, m_drShdLgtMan) == 0x18, "");
static_assert(offsetof(DrShdMan, m_drMan) == 0x20, "");

} // namespace ml
