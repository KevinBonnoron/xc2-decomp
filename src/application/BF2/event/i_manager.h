#pragma once

namespace event {

enum MSG_TYPE {
  MSG_TYPE_UNKNOWN_1 = 1,   // Inferred role: init begin; original name unknown.
  MSG_TYPE_UNKNOWN_2 = 2,   // Inferred role: update sequence; original name unknown.
  MSG_TYPE_UNKNOWN_3 = 3,   // Inferred role: init load; original name unknown.
  MSG_TYPE_UNKNOWN_4 = 4,   // Inferred role: init; original name unknown.
  MSG_TYPE_UNKNOWN_5 = 5,   // Inferred role: setup scene; original name unknown.
  MSG_TYPE_UNKNOWN_6 = 6,   // Inferred role: setup scene end; original name unknown.
  MSG_TYPE_UNKNOWN_7 = 7,   // Inferred role: start scene; original name unknown.
  MSG_TYPE_UNKNOWN_8 = 8,   // Inferred role: start page; original name unknown.
  MSG_TYPE_UNKNOWN_9 = 9,   // Inferred role: end scene begin; original name unknown.
  MSG_TYPE_UNKNOWN_10 = 10, // Inferred role: end scene; original name unknown.
  MSG_TYPE_UNKNOWN_11 = 11, // Inferred role: stop; original name unknown.
  MSG_TYPE_UNKNOWN_12 = 12, // Inferred role: clear; original name unknown.
  MSG_TYPE_UNKNOWN_13 = 13, // Inferred role: clear post; original name unknown.
  MSG_TYPE_UNKNOWN_14 = 14, // Inferred role: update; original name unknown.
  MSG_TYPE_UNKNOWN_15 = 15, // Inferred role: update post; original name unknown.
  MSG_TYPE_UNKNOWN_16 = 16, // Inferred role: render; original name unknown.
  MSG_TYPE_UNKNOWN_17 = 17, // Inferred role: render post; original name unknown.
  MSG_TYPE_UNKNOWN_18 = 18, // Inferred role: tail; original name unknown.
  MSG_TYPE_UNKNOWN_19 = 19, // Inferred role: tail post; original name unknown.
};

class IManager {
public:
  virtual ~IManager() {}
  virtual void OnEventProc(MSG_TYPE type) {}
};

} // namespace event
