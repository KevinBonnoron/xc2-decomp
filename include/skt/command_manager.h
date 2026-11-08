#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace skt {

// Inferred role: parsed argument of a command; original type name unknown.
struct unknown001 {
  const char *unknown00; // Inferred role: argument string, read by CommandParam::getArg; original member name unknown.
  u32 unknown08;         // Inferred role: argument type; original member name unknown.
};

class CommandParam {
public:
  void parseCommand(s8 separator);
  bool isValid(int index) const;
  const char *getArg(int index) const {
    if (!isValid(index)) {
      return "";
    }

    const char *arg = unknown800[index].unknown00;
    if (arg == nullptr) {
      arg = "";
    }

    return arg;
  }
  mm::mtl::FixStr<128> getStr(int index) const;
  bool getS32(int index, int &value) const;
  bool getF32(int index, f32 &value) const;

  char unknown000[0x400];                          // Inferred role: command line parsed by parseCommand; original member name unknown.
  char unknown400[0x400];                          // Inferred role: copy of the command line split in place into arguments; original member name unknown.
  mm::mtl::FixedVector<unknown001, 32> unknown800; // Inferred role: arguments; original member name unknown.
  u8 _a08[0xa18 - 0xa08];
};

static_assert(sizeof(unknown001) == 0x10, "");
static_assert(offsetof(CommandParam, unknown400) == 0x400, "");
static_assert(offsetof(CommandParam, unknown800) == 0x800, "");
static_assert(sizeof(CommandParam) == 0xa18, "");

class ICommandCallback {
public:
  virtual void OnRecv(const CommandParam &param) = 0;
  virtual void OnDisconnect(const char *name) {}
};

struct PortRegistInfo {
  PortRegistInfo() : unknownb0(nullptr), unknownb8(-2), unknownbc(0), unknownc0(0x10000), unknownc4(' ') {}

  u16 unknown00; // Inferred role: port number; original member name unknown.
  u8 _02[0x04 - 0x02];
  mm::mtl::FixStr<32> unknown04;  // Inferred role: server name; original member name unknown.
  mm::mtl::FixStr<128> unknown28; // Role and original member name unknown.
  ICommandCallback *unknownb0;    // Inferred role: receive callback; original member name unknown.
  int unknownb8;                  // Role and original member name unknown.
  u32 unknownbc;                  // Role and original member name unknown.
  u32 unknownc0;                  // Inferred role: buffer size; original member name unknown.
  char unknownc4;                 // Inferred role: argument separator; original member name unknown.
};

static_assert(offsetof(PortRegistInfo, unknown04) == 0x04, "");
static_assert(offsetof(PortRegistInfo, unknown28) == 0x28, "");
static_assert(offsetof(PortRegistInfo, unknownb0) == 0xb0, "");
static_assert(offsetof(PortRegistInfo, unknownb8) == 0xb8, "");
static_assert(offsetof(PortRegistInfo, unknownc4) == 0xc4, "");
static_assert(sizeof(PortRegistInfo) == 0xc8, "");

enum SERVER_OPTION : int;

class CommandManager {
public:
  static bool sendCommand(const char *server, const char *command);
  static bool sendCommandHtcs(const char *server, const char *command);
  static bool openServer(const PortRegistInfo &info, SERVER_OPTION option);
  static bool closeServer(const char *server);
  static bool isConnectedHtcs(const char *server);
  static bool setServerOption(const char *server, SERVER_OPTION option);
};

} // namespace skt
