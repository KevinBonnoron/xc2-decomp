#pragma once
#include "grlib/cglib_display_list.h"

namespace ml {

class DrResDisplayList : public grlib::CGLibDisplayList {
public:
  DrResDisplayList();
  ~DrResDisplayList();
};

class DrResOneDisplayList : public grlib::CGLibOneDisplayList {
public:
  DrResOneDisplayList();
  ~DrResOneDisplayList();
};

class DrResRenderDisplayList : public grlib::CGLibOneDisplayList {
public:
  DrResRenderDisplayList();
  ~DrResRenderDisplayList();
};

} // namespace ml
