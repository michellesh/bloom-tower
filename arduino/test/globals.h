#include "sdkconfig.h"
#include "esp_attr.h"

#define NUM_DISCS            8
#define NUM_STRIPS_PER_DISC  16

#define NUM_LEDS_DISC_0      522  // 10.875'
#define NUM_LEDS_DISC_1      468  // 9.75'
#define NUM_LEDS_DISC_2      414  // 8.625'
#define NUM_LEDS_DISC_3      360  // 7.5'
#define NUM_LEDS_DISC_4      306  // 6.375'
#define NUM_LEDS_DISC_5      252  // 5.25'
#define NUM_LEDS_DISC_6      198  // 4.125'
#define NUM_LEDS_DISC_7      144  // 3'

CRGB *DISC_0_STRIP_00;
CRGB *DISC_0_STRIP_01;
CRGB *DISC_0_STRIP_02;
CRGB *DISC_0_STRIP_03;
CRGB *DISC_0_STRIP_04;
CRGB *DISC_0_STRIP_05;
CRGB *DISC_0_STRIP_06;
CRGB *DISC_0_STRIP_07;
CRGB *DISC_0_STRIP_08;
CRGB *DISC_0_STRIP_09;
CRGB *DISC_0_STRIP_10;
CRGB *DISC_0_STRIP_11;
CRGB *DISC_0_STRIP_12;
CRGB *DISC_0_STRIP_13;
CRGB *DISC_0_STRIP_14;
CRGB *DISC_0_STRIP_15;

CRGB *DISC_1_STRIP_00;
CRGB *DISC_1_STRIP_01;
CRGB *DISC_1_STRIP_02;
CRGB *DISC_1_STRIP_03;
CRGB *DISC_1_STRIP_04;
CRGB *DISC_1_STRIP_05;
CRGB *DISC_1_STRIP_06;
CRGB *DISC_1_STRIP_07;
CRGB *DISC_1_STRIP_08;
CRGB *DISC_1_STRIP_09;
CRGB *DISC_1_STRIP_10;
CRGB *DISC_1_STRIP_11;
CRGB *DISC_1_STRIP_12;
CRGB *DISC_1_STRIP_13;
CRGB *DISC_1_STRIP_14;
CRGB *DISC_1_STRIP_15;

CRGB *DISC_2_STRIP_00;
CRGB *DISC_2_STRIP_01;
CRGB *DISC_2_STRIP_02;
CRGB *DISC_2_STRIP_03;
CRGB *DISC_2_STRIP_04;
CRGB *DISC_2_STRIP_05;
CRGB *DISC_2_STRIP_06;
CRGB *DISC_2_STRIP_07;
CRGB *DISC_2_STRIP_08;
CRGB *DISC_2_STRIP_09;
CRGB *DISC_2_STRIP_10;
CRGB *DISC_2_STRIP_11;
CRGB *DISC_2_STRIP_12;
CRGB *DISC_2_STRIP_13;
CRGB *DISC_2_STRIP_14;
CRGB *DISC_2_STRIP_15;

CRGB *DISC_3_STRIP_00;
CRGB *DISC_3_STRIP_01;
CRGB *DISC_3_STRIP_02;
CRGB *DISC_3_STRIP_03;
CRGB *DISC_3_STRIP_04;
CRGB *DISC_3_STRIP_05;
CRGB *DISC_3_STRIP_06;
CRGB *DISC_3_STRIP_07;
CRGB *DISC_3_STRIP_08;
CRGB *DISC_3_STRIP_09;
CRGB *DISC_3_STRIP_10;
CRGB *DISC_3_STRIP_11;
CRGB *DISC_3_STRIP_12;
CRGB *DISC_3_STRIP_13;
CRGB *DISC_3_STRIP_14;
CRGB *DISC_3_STRIP_15;

CRGB *DISC_4_STRIP_00;
CRGB *DISC_4_STRIP_01;
CRGB *DISC_4_STRIP_02;
CRGB *DISC_4_STRIP_03;
CRGB *DISC_4_STRIP_04;
CRGB *DISC_4_STRIP_05;
CRGB *DISC_4_STRIP_06;
CRGB *DISC_4_STRIP_07;
CRGB *DISC_4_STRIP_08;
CRGB *DISC_4_STRIP_09;
CRGB *DISC_4_STRIP_10;
CRGB *DISC_4_STRIP_11;
CRGB *DISC_4_STRIP_12;
CRGB *DISC_4_STRIP_13;
CRGB *DISC_4_STRIP_14;
CRGB *DISC_4_STRIP_15;

CRGB *DISC_5_STRIP_00;
CRGB *DISC_5_STRIP_01;
CRGB *DISC_5_STRIP_02;
CRGB *DISC_5_STRIP_03;
CRGB *DISC_5_STRIP_04;
CRGB *DISC_5_STRIP_05;
CRGB *DISC_5_STRIP_06;
CRGB *DISC_5_STRIP_07;
CRGB *DISC_5_STRIP_08;
CRGB *DISC_5_STRIP_09;
CRGB *DISC_5_STRIP_10;
CRGB *DISC_5_STRIP_11;
CRGB *DISC_5_STRIP_12;
CRGB *DISC_5_STRIP_13;
CRGB *DISC_5_STRIP_14;
CRGB *DISC_5_STRIP_15;

CRGB *DISC_6_STRIP_00;
CRGB *DISC_6_STRIP_01;
CRGB *DISC_6_STRIP_02;
CRGB *DISC_6_STRIP_03;
CRGB *DISC_6_STRIP_04;
CRGB *DISC_6_STRIP_05;
CRGB *DISC_6_STRIP_06;
CRGB *DISC_6_STRIP_07;
CRGB *DISC_6_STRIP_08;
CRGB *DISC_6_STRIP_09;
CRGB *DISC_6_STRIP_10;
CRGB *DISC_6_STRIP_11;
CRGB *DISC_6_STRIP_12;
CRGB *DISC_6_STRIP_13;
CRGB *DISC_6_STRIP_14;
CRGB *DISC_6_STRIP_15;

CRGB *DISC_7_STRIP_00;
CRGB *DISC_7_STRIP_01;
CRGB *DISC_7_STRIP_02;
CRGB *DISC_7_STRIP_03;
CRGB *DISC_7_STRIP_04;
CRGB *DISC_7_STRIP_05;
CRGB *DISC_7_STRIP_06;
CRGB *DISC_7_STRIP_07;
CRGB *DISC_7_STRIP_08;
CRGB *DISC_7_STRIP_09;
CRGB *DISC_7_STRIP_10;
CRGB *DISC_7_STRIP_11;
CRGB *DISC_7_STRIP_12;
CRGB *DISC_7_STRIP_13;
CRGB *DISC_7_STRIP_14;
CRGB *DISC_7_STRIP_15;
