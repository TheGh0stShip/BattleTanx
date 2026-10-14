#include "types.h"

/*
 * Campaign briefing text, mission objective/result strings and the pause
 * menu line list, together with the ROM image table the briefing screens
 * stream their backgrounds from.  ROM addresses are cartridge (PI) addresses.
 */

typedef struct RomImage {
    u32 romStart;
    u32 romEnd;
    s32 width;
    s32 height;
} RomImage;

typedef struct BriefingPage {
    s32 lineCount;
    char *text;
} BriefingPage;

typedef struct MenuLine {
    s32 kind;
    u8 color[4];
    char *text;
} MenuLine;

s32 D_80141700[16] = { 13, 15, 14, 1, 11, 5, 6, 1, 9, 8, 3, 1, 10, 2, 12, 1 };
s32 D_80141740[10] = { -1, -1, -1, -1, -1, -1, 16, -1, -1, -1 };

RomImage gRomImages[17] __asm__("D_80141768") = {
    { 0xB07D58F0, 0xB07D7CD0, 228, 38 },
    { 0xB07B7FB0, 0xB07B9280, 113, 38 },
    { 0xB07BB850, 0xB07BD750, 195, 38 },
    { 0xB07BD750, 0xB07BF860, 209, 38 },
    { 0xB07BF860, 0xB07C3890, 155, 30 },
    { 0xB07C3890, 0xB07C74D0, 184, 81 },
    { 0xB07C74D0, 0xB07C8E50, 158, 38 },
    { 0xB07C8E50, 0xB07CD1F0, 168, 30 },
    { 0xB07B69A0, 0xB07B7FB0, 135, 38 },
    { 0xB07CD1F0, 0xB07D14B0, 202, 82 },
    { 0xB07D14B0, 0xB07D58F0, 212, 80 },
    { 0xB07D7CD0, 0xB07DA500, 257, 38 },
    { 0xB07DA500, 0xB07DB6F0, 107, 38 },
    { 0xB07DB6F0, 0xB07DD680, 199, 38 },
    { 0xB07DD680, 0xB07E2040, 224, 82 },
    { 0xB07B9280, 0xB07BB850, 229, 40 },
    { 0xB07E2040, 0xB07E3210, 109, 37 },
};

char gBriefingText00[] = "The weapons of choice for all gangs\n"
    "are the BattleTanx.  Tanks are\n"
    "rebuilt and maintained using\n"
    "whatever scraps and spare parts\n"
    "can be salvaged from the aftermath\n"
    "of the Apocalypse.\n"
    "\n"
    "The once great city known as New\n"
    "York is now a nightmare of scorched\n"
    "concrete canyons ruled by a mutant\n"
    "gang known as The Urban Decay.\n"
    "";

char gBriefingText01[] = "Having survived the Urban Decay's\n"
    "forces in Queens, Griffin now heads\n"
    "towards what remains of Manhattan.\n"
    "\n"
    "Griffin will need to cross through\n"
    "the Queens Midtown Tunnel, which\n"
    "is named \"No Man's Land\" because\n"
    "no man has ever crossed it and\n"
    "survived.\n"
    "";

char gBriefingText02[] = "Times Square, the soul of \"The Big\n"
    "Apple,\" was a place where thousands\n"
    "used to come to ring in the New Year\n"
    "with tidings of good cheer and joy.\n"
    "\n"
    "When the ball dropped in 2001, it\n"
    "opened the doors of Armageddon,\n"
    "ringing in a nightmare of mass\n"
    "destruction.  Now Times Square is\n"
    "the territorial home of the Urban\n"
    "Decay.\n"
    "";

char gBriefingText03[] = "The George Washington Bridge is the\n"
    "only way out of New York City and is\n"
    "also the Urban Decay's stronghold.\n"
    "The bridge is guarded with mines,\n"
    "gun emplacements, and a huge\n"
    "Goliath Tanx.\n"
    "\n"
    "To escape from New York, Griffin\n"
    "must first run this gauntlet, which\n"
    "is known as \"Stranglehold Bridge.\"\n"
    "";

char gBriefingText04[] = "Griffin's army must break through\n"
    "the Psycho Brigade's defenses, find\n"
    "their fortress and destroy it.\n"
    "Griffin can then rescue their Queen.\n"
    "";

char gBriefingText05[] = "Griffin's army, now in possession of\n"
    "a Queen Lord, has entered the city\n"
    "of Chicago, stronghold of the\n"
    "Psycho Brigade.\n"
    "\n"
    "Griffin's forces must defend their\n"
    "Queen Lord, while trying to rescue\n"
    "another Queen Lord from the\n"
    "Psycho Brigade.  After all, the\n"
    "more Queen Lords a tribe has, the\n"
    "better its chances of survival.\n"
    "";

char gBriefingText06[] = "Having secured the northern sector\n"
    "of Chicago, Griffin's army heads\n"
    "for the southern sector, which is\n"
    "occupied by the remaining Psycho\n"
    "Brigade forces and by the Skull\n"
    "Riderz biker gang.\n"
    "\n"
    "The two gangs have temporarily\n"
    "allied so that they can stop\n"
    "Griffin's ever-growing army\n"
    "dead in its tracks.\n"
    "";

char gBriefingText07[] = "Driven by his visions, Griffin pushes\n"
    "his mechanized army forward,\n"
    "deeper into the dangers that\n"
    "occupy the West.\n"
    "\n"
    "Griffin's army must break through\n"
    "the defenses of the Mech Maniacs,\n"
    "Charlie Company and the Nuclear\n"
    "Knights, who guard a stretch of\n"
    "road known as \"Armageddon\n"
    "Highway.\"\n"
    "";

char gBriefingText08[] = "Having made it across Armageddon\n"
    "Highway, Griffin's mighty army\n"
    "finds the top-secret military base\n"
    "known as Area 51.\n"
    "\n"
    "The base is rich in high-tech\n"
    "weapons technology and holds\n"
    "several Queen Lords.  It is guarded\n"
    "by the Mech Maniacs, Charlie\n"
    "Company, and the Nuclear Knights.\n"
    "";

char gBriefingText09[] = "Having secured Area 51, Griffin's\n"
    "army now moves south towards the\n"
    "city of Las Vegas, which is the\n"
    "headquarters of the alliance.\n"
    "\n"
    "The three gang fortresses are\n"
    "located on a street named Fremont.\n"
    "Griffin must again, somehow,\n"
    "manage to rescue three Queen Lords\n"
    "and crush the three enemy gangs\n"
    "for good.\n"
    "";

char gBriefingText10[] = "Griffin and his army prepare to\n"
    "cross the Crimson Gate Bridge.\n"
    "The famous bridge has been\n"
    "renamed by the Dark Angels\n"
    "because of the torrents of blood\n"
    "spilled on it by defeated invading\n"
    "armies.\n"
    "\n"
    "The Bridge is the only way in or out\n"
    "of the city.\n"
    "";

char gBriefingText11[] = "Having done the impossible, Griffin's\n"
    "army now makes its way towards\n"
    "\"The Wharf,\" stronghold of the Skull\n"
    "Riderz and the Aftershocks.\n"
    "\n"
    "Securing the Wharf with minimum\n"
    "casualties is paramount if Griffin\n"
    "is to ever rescue Madison from the\n"
    "Quarantine zone.\n"
    "";

char gBriefingText12[] = "The Quarantine Zone is where the\n"
    "Government quarantined females\n"
    "during the \"Plague Years.\"  It is\n"
    "Griffin's last hope for ever finding\n"
    "Madison.\n"
    "\n"
    "The \"Q-Zone\" is an island fortress,\n"
    "guarded by the elite forces of the\n"
    "Dark Angels.\n"
    "\n"
    "It is where the final battle of good\n"
    "versus evil will be fought.\n"
    "";

BriefingPage gBriefingPages[17] __asm__("D_8014268C") = {
    { 11, gBriefingText00 },
    { 9, gBriefingText01 },
    { 11, gBriefingText02 },
    { 10, gBriefingText03 },
    { 0, 0 },
    { 4, gBriefingText04 },
    { 11, gBriefingText05 },
    { 11, gBriefingText06 },
    { 0, 0 },
    { 11, gBriefingText07 },
    { 10, gBriefingText08 },
    { 11, gBriefingText09 },
    { 0, 0 },
    { 10, gBriefingText10 },
    { 9, gBriefingText11 },
    { 0, 0 },
    { 12, gBriefingText12 },
};

char gObjectiveText00[] = "DESTROY 5 TANKS";
char gObjectiveText01[] = "CROSS THE TUNNEL";
char gObjectiveText02[] = "DESTROY 15 TANKS";
char gObjectiveText03[] = "CROSS THE BRIDGE";
char gObjectiveText04[] = "RESCUE 1 QUEEN LORD";
char gObjectiveText05[] = "RESCUE 2 QUEEN LORDS";
char gObjectiveText06[] = "RESCUE 3 QUEEN LORDS";
char gObjectiveText07[] = "CROSS THE HIGHWAY";
char gObjectiveText08[] = "RESCUE MADISON";

char *gMissionObjectives[17] __asm__("D_801427C8") = {
    gObjectiveText00, gObjectiveText01, gObjectiveText02, gObjectiveText03,
    0, gObjectiveText04, gObjectiveText04, gObjectiveText05,
    0, gObjectiveText07, gObjectiveText06, gObjectiveText06,
    0, gObjectiveText03, gObjectiveText06, 0,
    gObjectiveText08,
};

char gResultText00[] = "GROUND ZERO CLEARED";
char gResultText01[] = "MADE IT!!!";
char gResultText02[] = "TIMES SQUARE CLEARED";
char gResultText03[] = "QUEEN LORD RESCUED";
char gResultText04[] = "2 QUEEN LORDS RESCUED";
char gResultText05[] = "3 QUEEN LORDS RESCUED";
char gResultText06[] = "TRIUMPH!";

char *gMissionResults[17] __asm__("D_80142894") = {
    gResultText00, gResultText01, gResultText02, gResultText01,
    0, gResultText03, gResultText03, gResultText04,
    0, gResultText01, gResultText05, gResultText05,
    0, gResultText01, gResultText05, 0,
    gResultText06,
};

s32 D_801428D8 = 0;
s32 D_801428DC = 169;
s32 D_801428E0 = 77;
s32 D_801428E4[4] = { 33, 173, 33, 173 };
s32 D_801428F4[4] = { 45, 45, 158, 158 };

/* Menu line strings live in this object's .rodata. */
extern char D_8007517C[];
extern char D_80075188[];
extern char D_80075194[];
extern char D_800751A4[];
extern char D_800751B0[];
extern char D_800751C0[];
extern char D_800751D0[];
extern char D_800751D8[];
extern char D_800751E4[];
extern char D_800751EC[];
extern char D_800751F8[];
extern char D_80075200[];
extern char D_8007520C[];
extern char D_80075218[];
extern char D_80075228[];
extern char D_80075234[];
extern char D_80075244[];
extern char D_80075254[];
extern char D_80075264[];
extern char D_80075274[];
extern char D_80075284[];
extern char D_80075294[];
extern char D_800752A4[];
extern char D_800752B4[];
extern char D_800752C0[];
extern char D_800752CC[];
extern char D_800752D8[];
extern char D_800752E4[];
extern char D_800752F4[];
extern char D_80075304[];
extern char D_8007530C[];
extern char D_80075320[];
extern char D_8007532C[];
extern char D_80075338[];
extern char D_80075348[];
extern char D_8007535C[];
extern char D_8007536C[];
extern char D_8007537C[];
extern char D_80075388[];
extern char D_80075394[];
extern char D_800753A0[];
extern char D_800753AC[];
extern char D_800753BC[];
extern char D_800753CC[];
extern char D_800753E0[];
extern char D_800753F4[];
extern char D_80075404[];

MenuLine gPauseMenuLines[48] __asm__("D_80142904") = {
    { 2, { 0xB4, 0x28, 0x00, 0xFF }, D_80075404 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_800753F4 },
    { 2, { 0xB4, 0x28, 0x00, 0xFF }, D_800753E0 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_800753CC },
    { 2, { 0xB4, 0x28, 0x00, 0xFF }, D_800753BC },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_800753AC },
    { 2, { 0xB4, 0x28, 0x00, 0xFF }, D_800753A0 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_80075394 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_80075388 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_8007537C },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_8007536C },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_8007535C },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_80075348 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_80075338 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_8007532C },
    { 2, { 0xB4, 0x28, 0x00, 0xFF }, D_80075320 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_8007530C },
    { 2, { 0xB4, 0x28, 0x00, 0xFF }, D_80075304 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_800752F4 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_800752E4 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_800752D8 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_800752CC },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_800752C0 },
    { 2, { 0xB4, 0x28, 0x00, 0xFF }, D_800752B4 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_800752A4 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_80075294 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_80075284 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_80075274 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_80075264 },
    { 2, { 0xB4, 0x28, 0x00, 0xFF }, D_80075254 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_80075244 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_800752A4 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_80075234 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_80075228 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_80075218 },
    { 2, { 0xB4, 0x28, 0x00, 0xFF }, D_8007520C },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_80075200 },
    { 2, { 0xB4, 0x28, 0x00, 0xFF }, D_800751F8 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_800751EC },
    { 2, { 0xB4, 0x28, 0x00, 0xFF }, D_800751E4 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_800751D8 },
    { 2, { 0xB4, 0x28, 0x00, 0xFF }, D_800751D0 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_800751C0 },
    { 2, { 0xB4, 0x28, 0x00, 0xFF }, D_800751B0 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_800751A4 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_80075194 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_80075188 },
    { 4, { 0xFF, 0xFF, 0xFF, 0xFF }, D_8007517C },
};

u16 D_80142B44[6] = { 'T', 'F', 'R', 'A', 'M', 'E' };
