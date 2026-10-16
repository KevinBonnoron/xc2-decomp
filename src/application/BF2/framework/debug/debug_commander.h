#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace skt {
struct PortRegistInfo;
enum SERVER_OPTION : int;
} // namespace skt

namespace fw {
namespace debug {

class CommandManager {
public:
  static bool sendCommand(const char *server, const char *command);
  static bool sendCommandHtcs(const char *server, const char *command);
  static bool openServer(const skt::PortRegistInfo &info);
  static bool closeServer(const char *server);
  static bool isConnectedHtcs(const char *server);
  static bool setServerOption(const char *server, skt::SERVER_OPTION option);
  static skt::SERVER_OPTION getServerOption(const char *server);
};

class DebugCommander : public mm::mtl::PtrSingleton<DebugCommander> {
public:
  void setServerOption(const char *server, skt::SERVER_OPTION option);
  skt::SERVER_OPTION getServerOption(const char *server) const;

  u8 _08[0xaec - 0x08];
  skt::SERVER_OPTION serverOption;
};

static_assert(offsetof(DebugCommander, serverOption) == 0xaec, "");

} // namespace debug
} // namespace fw
