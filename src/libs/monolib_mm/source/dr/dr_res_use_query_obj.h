#pragma once
#include "types.h"

namespace ml {
class DrPixlOccQuery;
struct DrResQueryObj;

class DrResUseQueryObj {
public:
  enum QueryFlag {
    QUERY_FLAG_BEGIN = 0x1,
    QUERY_FLAG_RESULT = 0x4,
  };

  DrResUseQueryObj();
  ~DrResUseQueryObj();
  void update();
  void begin(DrPixlOccQuery *occQuery);
  void end();

  DrResQueryObj *m_query;
  u32 m_pixel;
};

} // namespace ml
