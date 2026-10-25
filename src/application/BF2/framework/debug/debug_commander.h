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
  ~DebugCommander() override;
  virtual const char *getName() const;
  virtual void onEnter();
  virtual void onLeave();
  void enableDebugInput(bool enable);
  void setServerOption(const char *server, skt::SERVER_OPTION option);
  skt::SERVER_OPTION getServerOption(const char *server) const;

  u8 _08[0xae8 - 0x08];
  bool unknownae8; // Inferred role: debug input enabled; original member name unknown.
  u8 _ae9[0xaec - 0xae9];
  skt::SERVER_OPTION m_serverOption;
};

static_assert(offsetof(DebugCommander, unknownae8) == 0xae8, "");
static_assert(offsetof(DebugCommander, m_serverOption) == 0xaec, "");

} // namespace debug
} // namespace fw
