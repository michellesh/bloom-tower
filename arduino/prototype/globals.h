#define BRIGHTNESS 255
#define LED_TYPE WS2813
#define COLOR_ORDER GRB

#define NUM_DISCS 7
#define NUM_SIDES 4

#define PIN_1 2
#define PIN_2 4
#define PIN_3 5
#define PIN_4 12
#define PIN_5 13
#define PIN_6 14
#define PIN_7 18

// Incremented once per iteration of the loop
unsigned long ticks = 0;

// TODO change these numbers to the real ones
// should be ordered top/smallest level -> bottom/largest level
int16_t NUM_LEDS[] = {100, 200, 300, 400, 600, 800, 1000};
int16_t NUM_LEDS_TOTAL = NUM_LEDS[0] + NUM_LEDS[1] + NUM_LEDS[2] + NUM_LEDS[3] +
                         NUM_LEDS[4] + NUM_LEDS[5] + NUM_LEDS[6];

uint8_t PERCENT_HEIGHT_DISC[] = {100, 89, 78, 67, 56, 45, 34, 23, 12};

// Generated from javascript prototype
int16_t RADII_DISC_0[] = {27,  42,  56,  71,  86,  101, 115, 130, 142, 151,
                          161, 172, 184, 196, 209, 222, 235, 248, 248, 235,
                          222, 209, 196, 184, 172, 161, 151, 142, 194, 204,
                          214, 225, 237, 249, 249, 237, 225, 214, 204, 194};
int16_t RADII_DISC_1[] = {26,  40,  53,  66,  80,  93,  106, 120, 131,
                          140, 151, 162, 174, 186, 199, 213, 226, 226,
                          213, 199, 186, 174, 162, 151, 140, 131, 179,
                          189, 201, 213, 226, 226, 213, 201, 189, 179};
int16_t RADII_DISC_2[] = {26,  40,  54,  67,  81,  95,  108, 120, 132, 144, 158,
                          172, 187, 203, 203, 187, 172, 158, 144, 132, 120, 162,
                          172, 182, 193, 205, 205, 193, 182, 172, 162};
int16_t RADII_DISC_3[] = {27,  41,  55,  69,  83,  97,  109, 119, 130, 142,
                          155, 168, 182, 182, 168, 155, 142, 130, 119, 109,
                          147, 157, 169, 182, 182, 169, 157, 147};
int16_t RADII_DISC_4[] = {27,  42,  56,  71,  86,  98,  108, 120, 132,
                          146, 160, 160, 146, 132, 120, 108, 98,  130,
                          139, 150, 161, 161, 150, 139, 130, 27};
int16_t RADII_DISC_5[] = {27,  43,  59, 74, 87,  98,  110, 123, 137, 137,
                          123, 110, 98, 87, 115, 125, 138, 138, 125, 115};
int16_t RADII_DISC_6[] = {28,  45, 63, 76,  87,  101, 115, 115,
                          101, 87, 76, 100, 114, 114, 100};
int16_t RADII_DISC_7[] = {30, 50, 65, 78, 93, 93, 78, 65, 82, 94, 94, 82};
int16_t RADII_DISC_8[] = {34, 55, 70, 70, 55, 69, 69};
int16_t *RADII[] = {RADII_DISC_0, RADII_DISC_1, RADII_DISC_2,
                    RADII_DISC_3, RADII_DISC_4, RADII_DISC_5,
                    RADII_DISC_6, RADII_DISC_7, RADII_DISC_8};
int16_t MAX_RADIUS_DISC[] = {249, 226, 205, 182, 161, 138, 115, 94, 70};

int16_t ANGLES_DISC_0[] = {
    0,   0,   0,   0,   0,   0,   0,   0,   3,   7,   11,  15,  18,  21,  23,
    26,  27,  29,  31,  33,  34,  37,  39,  42,  45,  49,  53,  57,  77,  74,
    70,  67,  64,  61,  59,  56,  53,  50,  46,  43,  60,  60,  60,  60,  60,
    60,  60,  60,  63,  67,  71,  75,  78,  81,  83,  86,  87,  89,  91,  93,
    94,  97,  99,  102, 105, 109, 113, 117, 137, 134, 130, 127, 124, 121, 119,
    116, 113, 110, 106, 103, 120, 120, 120, 120, 120, 120, 120, 120, 123, 127,
    131, 135, 138, 141, 143, 146, 147, 149, 151, 153, 154, 157, 159, 162, 165,
    169, 173, 177, 197, 194, 190, 187, 184, 181, 179, 176, 173, 170, 166, 163,
    180, 180, 180, 180, 180, 180, 180, 180, 183, 187, 191, 195, 198, 201, 203,
    206, 207, 209, 211, 213, 214, 217, 219, 222, 225, 229, 233, 237, 257, 254,
    250, 247, 244, 241, 239, 236, 233, 230, 226, 223, 240, 240, 240, 240, 240,
    240, 240, 240, 243, 247, 251, 255, 258, 261, 263, 266, 267, 269, 271, 273,
    274, 277, 279, 282, 285, 289, 293, 297, 317, 314, 310, 307, 304, 301, 299,
    296, 293, 290, 286, 283, 300, 300, 300, 300, 300, 300, 300, 300, 303, 307,
    311, 315, 318, 321, 323, 326, 327, 329, 331, 333, 334, 337, 339, 342, 345,
    349, 353, 357, 17,  14,  10,  7,   4,   1,   359, 356, 353, 350, 346, 343};
int16_t ANGLES_DISC_1[] = {
    300, 300, 300, 300, 300, 300, 300, 300, 303, 308, 312, 316, 320, 322, 325,
    327, 329, 331, 333, 335, 338, 340, 344, 348, 352, 357, 17,  12,  8,   5,
    1,   359, 355, 352, 348, 343, 0,   0,   0,   0,   0,   0,   0,   0,   3,
    8,   12,  16,  20,  22,  25,  27,  29,  31,  33,  35,  38,  40,  44,  48,
    52,  57,  77,  72,  68,  65,  61,  59,  55,  52,  48,  43,  60,  60,  60,
    60,  60,  60,  60,  60,  63,  68,  72,  76,  80,  82,  85,  87,  89,  91,
    93,  95,  98,  100, 104, 108, 112, 117, 137, 132, 128, 125, 121, 119, 115,
    112, 108, 103, 120, 120, 120, 120, 120, 120, 120, 120, 123, 128, 132, 136,
    140, 142, 145, 147, 149, 151, 153, 155, 158, 160, 164, 168, 172, 177, 197,
    192, 188, 185, 181, 179, 175, 172, 168, 163, 180, 180, 180, 180, 180, 180,
    180, 180, 183, 188, 192, 196, 200, 202, 205, 207, 209, 211, 213, 215, 218,
    220, 224, 228, 232, 237, 257, 252, 248, 245, 241, 239, 235, 232, 228, 223,
    240, 240, 240, 240, 240, 240, 240, 240, 243, 248, 252, 256, 260, 262, 265,
    267, 269, 271, 273, 275, 278, 280, 284, 288, 292, 297, 317, 312, 308, 305,
    301, 299, 295, 292, 288, 283};
int16_t ANGLES_DISC_2[] = {
    240, 240, 240, 240, 240, 240, 240, 244, 250, 255, 259, 263, 266, 269, 271,
    274, 277, 281, 285, 290, 296, 317, 312, 308, 305, 301, 299, 295, 292, 288,
    283, 300, 300, 300, 300, 300, 300, 300, 304, 310, 315, 319, 323, 326, 329,
    331, 334, 337, 341, 345, 350, 356, 17,  12,  8,   5,   1,   359, 355, 352,
    348, 343, 0,   0,   0,   0,   0,   0,   0,   4,   10,  15,  19,  23,  26,
    29,  31,  34,  37,  41,  45,  50,  56,  77,  72,  68,  65,  61,  59,  55,
    52,  48,  43,  60,  60,  60,  60,  60,  60,  60,  64,  70,  75,  79,  83,
    86,  89,  91,  94,  97,  101, 105, 110, 116, 137, 132, 128, 125, 121, 119,
    115, 112, 108, 103, 120, 120, 120, 120, 120, 120, 120, 124, 130, 135, 139,
    143, 146, 149, 151, 154, 157, 161, 165, 170, 176, 197, 192, 188, 185, 181,
    179, 175, 172, 168, 163, 180, 180, 180, 180, 180, 180, 180, 184, 190, 195,
    199, 203, 206, 209, 211, 214, 217, 221, 225, 230, 236, 257, 252, 248, 245,
    241, 239, 235, 232, 228, 223};
int16_t ANGLES_DISC_3[] = {
    60,  60,  60,  60,  60,  60,  64,  70,  75,  79,  83,  86,  89,  91,
    94,  97,  101, 105, 110, 116, 136, 131, 126, 122, 118, 114, 109, 104,
    120, 120, 120, 120, 120, 120, 124, 130, 135, 139, 143, 146, 149, 151,
    154, 157, 161, 165, 170, 176, 196, 191, 186, 182, 178, 174, 169, 164,
    180, 180, 180, 180, 180, 180, 184, 190, 195, 199, 203, 206, 209, 211,
    214, 217, 221, 225, 230, 236, 256, 251, 246, 242, 238, 234, 229, 224,
    240, 240, 240, 240, 240, 240, 244, 250, 255, 259, 263, 266, 269, 271,
    274, 277, 281, 285, 290, 296, 316, 311, 306, 302, 298, 294, 289, 284,
    300, 300, 300, 300, 300, 300, 304, 310, 315, 319, 323, 326, 329, 331,
    334, 337, 341, 345, 350, 356, 16,  11,  6,   2,   358, 354, 349, 344,
    0,   0,   0,   0,   0,   0,   4,   10,  15,  19,  23,  26,  29,  31,
    34,  37,  41,  45,  50,  56,  76,  71,  66,  62,  58,  54,  49,  44};
int16_t ANGLES_DISC_4[] = {
    60,  60,  60,  60,  60,  64,  71,  77,  82,  85,  89,  91,  95,  98,  103,
    109, 116, 136, 131, 126, 122, 118, 114, 109, 104, 120, 120, 120, 120, 120,
    124, 131, 137, 142, 145, 149, 151, 155, 158, 163, 169, 176, 196, 191, 186,
    182, 178, 174, 169, 164, 180, 180, 180, 180, 180, 184, 191, 197, 202, 205,
    209, 211, 215, 218, 223, 229, 236, 256, 251, 246, 242, 238, 234, 229, 224,
    240, 240, 240, 240, 240, 244, 251, 257, 262, 265, 269, 271, 275, 278, 283,
    289, 296, 316, 311, 306, 302, 298, 294, 289, 284, 300, 300, 300, 300, 300,
    304, 311, 317, 322, 325, 329, 331, 335, 338, 343, 349, 356, 16,  11,  6,
    2,   358, 354, 349, 344, 0,   0,   0,   0,   0,   4,   11,  17,  22,  25,
    29,  31,  35,  38,  43,  49,  56,  76,  71,  66,  62,  58,  54,  49,  44};
int16_t ANGLES_DISC_5[] = {
    0,   0,   0,   0,   5,   13,  19,  24,  28,  32,  36,  41,  47,  55,  75,
    68,  63,  57,  52,  45,  60,  60,  60,  60,  65,  73,  79,  84,  88,  92,
    96,  101, 107, 115, 135, 128, 123, 117, 112, 105, 120, 120, 120, 120, 125,
    133, 139, 144, 148, 152, 156, 161, 167, 175, 195, 188, 183, 177, 172, 165,
    180, 180, 180, 180, 185, 193, 199, 204, 208, 212, 216, 221, 227, 235, 255,
    248, 243, 237, 232, 225, 240, 240, 240, 240, 245, 253, 259, 264, 268, 272,
    276, 281, 287, 295, 315, 308, 303, 297, 292, 285, 300, 300, 300, 300, 305,
    313, 319, 324, 328, 332, 336, 341, 347, 355, 15,  8,   3,   357, 352, 345};
int16_t ANGLES_DISC_6[] = {
    300, 300, 300, 306, 315, 322, 328, 332, 338, 345, 354, 13,  4,   356, 347,
    0,   0,   0,   6,   15,  22,  28,  32,  38,  45,  54,  73,  64,  56,  47,
    60,  60,  60,  66,  75,  82,  88,  92,  98,  105, 114, 133, 124, 116, 107,
    120, 120, 120, 126, 135, 142, 148, 152, 158, 165, 174, 193, 184, 176, 167,
    180, 180, 180, 186, 195, 202, 208, 212, 218, 225, 234, 253, 244, 236, 227,
    240, 240, 240, 246, 255, 262, 268, 272, 278, 285, 294, 313, 304, 296, 287};
int16_t ANGLES_DISC_7[] = {
    240, 240, 247, 259, 267, 273, 281, 293, 313, 304, 296, 287, 300, 300, 307,
    319, 327, 333, 341, 353, 13,  4,   356, 347, 0,   0,   7,   19,  27,  33,
    41,  53,  73,  64,  56,  47,  60,  60,  67,  79,  87,  93,  101, 113, 133,
    124, 116, 107, 120, 120, 127, 139, 147, 153, 161, 173, 193, 184, 176, 167,
    180, 180, 187, 199, 207, 213, 221, 233, 253, 244, 236, 227};
int16_t ANGLES_DISC_8[] = {
    240, 250, 265, 275, 290, 308, 292, 300, 310, 325, 335, 350, 8,   352,
    0,   10,  25,  35,  50,  68,  52,  60,  70,  85,  95,  110, 128, 112,
    120, 130, 145, 155, 170, 188, 172, 180, 190, 205, 215, 230, 248, 232};
int16_t *ANGLES[] = {ANGLES_DISC_0, ANGLES_DISC_1, ANGLES_DISC_2,
                     ANGLES_DISC_3, ANGLES_DISC_4, ANGLES_DISC_5,
                     ANGLES_DISC_6, ANGLES_DISC_7, ANGLES_DISC_8};
