#pragma once
#include "types.h"

// Character encoding functions of the SDK. The function names and parameter types come from the imports of the game
// (_ZN2nn4util30ConvertStringUtf8ToUtf16NativeEPtiPKc...); the result type is the public name of open-ead nnheaders
// include/nn/util.h (https://github.com/open-ead/nnheaders).

namespace nn {
namespace util {

enum CharacterEncodingResult {};

CharacterEncodingResult ConvertStringUtf8ToUtf16Native(u16 *destination, int destinationLength, const char *source);
CharacterEncodingResult ConvertStringUtf16NativeToUtf8(char *destination, int destinationLength, const u16 *source);
CharacterEncodingResult GetLengthOfConvertedStringUtf8ToUtf16Native(int *length, const char *source, int sourceLength);
CharacterEncodingResult GetLengthOfConvertedStringUtf16NativeToUtf8(int *length, const u16 *source, int sourceLength);

} // namespace util
} // namespace nn
