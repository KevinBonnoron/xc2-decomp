#pragma once

namespace Bdat {

int getIdTop(unsigned char *bdat);
int getIdCount(unsigned char *bdat);
const char *getMSText(unsigned char *bdat, int id);
unsigned int getValCheck(unsigned char *bdat, const char *name, int id, int type);

} // namespace Bdat
