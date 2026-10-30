#pragma once
#include "types.h"

namespace ml {
class DrPixlOccQuery;
struct DrResQueryObj;

class DrResUseQueryObj {
public:
  // Inferred role: query flag; original type name unknown.
  enum unknown001 {
    unknown001_1 = 0x1, // Inferred role: begin; original name unknown.
    unknown001_4 = 0x4, // Inferred role: result; original name unknown.
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
