#pragma once

namespace movie {

enum Status {
  Status_Success = 0,
  Status_UNKNOWN_4096 = 0x1000, // Returned by GetMediaTime while no anchor time is set; original name unknown.
};

} // namespace movie
