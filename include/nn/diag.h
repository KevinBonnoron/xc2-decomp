#pragma once
#include <stddef.h>

#define NN_LOG(...)                                                                                                                                                                                    \
  do {                                                                                                                                                                                                 \
    ::nn::diag::LogMetaData logMetaData;                                                                                                                                                               \
    logMetaData.sourceInfo.lineNumber = __LINE__;                                                                                                                                                      \
    logMetaData.sourceInfo.fileName = __FILE__;                                                                                                                                                        \
    logMetaData.sourceInfo.functionName = __FUNCTION__;                                                                                                                                                \
    logMetaData.moduleName = "";                                                                                                                                                                       \
    logMetaData.severity = ::nn::diag::LogSeverity_Info;                                                                                                                                               \
    logMetaData.verbosity = 0;                                                                                                                                                                         \
    logMetaData.useDefaultLocaleCharset = false;                                                                                                                                                       \
    logMetaData.pAdditionalData = nullptr;                                                                                                                                                             \
    logMetaData.additionalDataBytes = 0;                                                                                                                                                               \
    ::nn::diag::detail::LogImpl(logMetaData, __VA_ARGS__);                                                                                                                                             \
  } while (0)

#define NN_ABORT_UNLESS(condition)                                                                                                                                                                     \
  do {                                                                                                                                                                                                 \
    if (!(condition)) {                                                                                                                                                                                \
      ::nn::diag::detail::AbortImpl("", "", "", 0);                                                                                                                                                    \
    }                                                                                                                                                                                                  \
  } while (0)

#define NN_ASSERT(condition)                                                                                                                                                                           \
  do {                                                                                                                                                                                                 \
    if (!(condition)) {                                                                                                                                                                                \
      ::nn::diag::detail::OnAssertionFailure(::nn::diag::ASSERTION_TYPE_UNKNOWN_2, "", "", "", 0);                                                                                                     \
    }                                                                                                                                                                                                  \
  } while (0)

namespace nn {
namespace detail {

// Provenance: imported symbol _ZN2nn6detail21UnexpectedDefaultImplEPKcS2_i (work/syms_base.txt). The prototype is
// inferred from the call in the memory callback of grlib::CGLibCmdBuffer (0x71007b29fc): two string pointers and
// an integer, with no code after the call.
[[noreturn]] void UnexpectedDefaultImpl(const char *functionName, const char *fileName, int lineNumber);

} // namespace detail

namespace diag {

enum LogSeverity {
  LogSeverity_Trace,
  LogSeverity_Info,
  LogSeverity_Warn,
  LogSeverity_Error,
  LogSeverity_Fatal,
};

struct SourceInfo {
  int lineNumber;
  const char *fileName;
  const char *functionName;
};

struct LogMetaData {
  SourceInfo sourceInfo;
  const char *moduleName;
  LogSeverity severity;
  int verbosity;
  bool useDefaultLocaleCharset;
  void *pAdditionalData;
  size_t additionalDataBytes;
};

static_assert(offsetof(LogMetaData, moduleName) == 0x18, "");
static_assert(offsetof(LogMetaData, severity) == 0x20, "");
static_assert(offsetof(LogMetaData, useDefaultLocaleCharset) == 0x28, "");
static_assert(offsetof(LogMetaData, pAdditionalData) == 0x30, "");
static_assert(sizeof(LogMetaData) == 0x40, "");

// Provenance: AssertionType and OnAssertionFailure are the public SDK names, as declared in the open-ead nnheaders
// project (https://github.com/open-ead/nnheaders, include/nn/diag.h), where the enumerators are not given; the
// game calls _ZN2nn4diag6detail18OnAssertionFailureENS0_13AssertionTypeEPKcS4_S4_i (work/syms_base.txt) with 2 and
// empty strings in grlib::CGLibDeviceVI::init (0x71007b33f0).
enum AssertionType {
  ASSERTION_TYPE_UNKNOWN_2 = 2,
};

namespace detail {

void LogImpl(const LogMetaData &metaData, const char *format, ...);
[[noreturn]] void AbortImpl(const char *condition, const char *functionName, const char *fileName, int lineNumber);
void OnAssertionFailure(AssertionType type, const char *condition, const char *functionName, const char *fileName, int lineNumber);

} // namespace detail
} // namespace diag
} // namespace nn
