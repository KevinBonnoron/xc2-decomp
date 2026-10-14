#pragma once
#include "mm_mtl/singleton.h"

namespace btl {

class DataManager : public mm::mtl::PtrSingleton<DataManager> {
public:
  void SetPartyGauge(int partyGauge, bool isNotify);
};

} // namespace btl
