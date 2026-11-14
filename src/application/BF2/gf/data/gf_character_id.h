#pragma once

namespace gf {

enum {
  DRIVER_UNKNOWN_1 = 1,   // Inferred role: driver rex; original name unknown.
  DRIVER_UNKNOWN_2 = 2,   // Inferred role: driver nia; original name unknown.
  DRIVER_UNKNOWN_3 = 3,   // Inferred role: driver jiku; original name unknown.
  DRIVER_UNKNOWN_4 = 4,   // Inferred role: driver tora; original name unknown.
  DRIVER_UNKNOWN_5 = 5,   // Inferred role: driver vandamme; original name unknown.
  DRIVER_UNKNOWN_6 = 6,   // Inferred role: driver meleph; original name unknown.
  DRIVER_UNKNOWN_7 = 7,   // Inferred role: driver shin; original name unknown.
  DRIVER_UNKNOWN_8 = 8,   // Inferred role: driver metsu; original name unknown.
  DRIVER_UNKNOWN_9 = 9,   // Inferred role: driver shin 2; original name unknown.
  DRIVER_UNKNOWN_10 = 10, // Inferred role: driver jiku hood; original name unknown.
  DRIVER_UNKNOWN_11 = 11, // Inferred role: driver rex 2; original name unknown.
  DRIVER_UNKNOWN_12 = 12,
  DRIVER_UNKNOWN_13 = 13,
};

enum {
  BLADE_HOMURA = 1001,       // Row 11109 of BDAT table EVT_setupBf01, column objID, reads "BLADE_HOMURA".
  BLADE_HIKARI = 1002,       // Row 14228 of BDAT table EVT_setupBf04, column objID, reads "BLADE_HIKARI".
  BLADE_HOMURI = 1003,       // Row 18003 of BDAT table EVT_setupBf08, column objID, reads "BLADE_HOMURI".
  BLADE_BYAKKO = 1004,       // Row 11032 of BDAT table EVT_setupBf01, column objID, reads "BLADE_BYAKKO".
  BLADE_UNKNOWN_1005 = 1005, // Inferred role: blade hana js; original name unknown.
  BLADE_UNKNOWN_1006 = 1006, // Inferred role: blade hana jk; original name unknown.
  BLADE_UNKNOWN_1007 = 1007, // Inferred role: blade hana jd; original name unknown.
  BLADE_SUZAKU = 1008,       // Row 13044 of BDAT table EVT_setupBf03, column objID, reads "BLADE_SUZAKU".
  BLADE_SAIKA = 1010,        // Row 15170 of BDAT table EVT_setupBf05, column objID, reads "BLADE_SAIKA".
  BLADE_UNKNOWN_1011 = 1011,
  BLADE_UNKNOWN_1012 = 1012, // Inferred role: blade rex dummy; original name unknown.
  BLADE_UNKNOWN_1013 = 1013, // Inferred role: blade shin dummy; original name unknown.
  BLADE_WADATSUMI = 1014,    // Row 14061 of BDAT table EVT_setupBf04, column objID, reads "BLADE_WADATSUMI".
  BLADE_UNKNOWN_1022 = 1022, // Inferred role: blade real alias target; original name unknown.
  BLADE_KOSMOS = 1039,       // Row 40749 of BDAT table EVT_setupFev01, column objID, reads "BLADE_KOSMOS".
  BLADE_UNKNOWN_1040 = 1040,
  BLADE_UNKNOWN_1042 = 1042, // Inferred role: blade whose event weapon belongs to driver metsu (GfInitParamWeapon::setupForEvent); original name unknown.
  BLADE_UNKNOWN_1043 = 1043, // Inferred role: first blade of the change weapon range, event weapon of driver shin (GfInitParamWeapon::setupForEvent); original name unknown.
  BLADE_UNKNOWN_1044 = 1044, // Inferred role: blade whose event weapon belongs to driver shin (GfInitParamWeapon::setupForEvent); original name unknown.
  BLADE_UNKNOWN_1045 = 1045, // Inferred role: blade whose event weapon belongs to driver shin (GfInitParamWeapon::setupForEvent); original name unknown.
  BLADE_UNKNOWN_1050 = 1050, // Inferred role: blade real alias; original name unknown.
  BLADE_UNKNOWN_1073 = 1073,
  BLADE_UNKNOWN_1074 = 1074, // Inferred role: Homuri loaded when GfDataBlade::isHomuriNameHikari; original name unknown.
  BLADE_UNKNOWN_1078 = 1078,
  BLADE_UNKNOWN_1079 = 1079,
  BLADE_UNKNOWN_1103 = 1103, // Inferred role: blade whose death blow effect uses the weapon motion name; original name unknown.
};

} // namespace gf
