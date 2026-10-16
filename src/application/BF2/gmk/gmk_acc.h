#pragma once

namespace gmk {

class IGmkList;

class GmkAccManager {
public:
  static void invalidateAccs(const IGmkList &list);
};

} // namespace gmk
