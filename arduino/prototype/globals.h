#define LED_TYPE    NEOPIXEL
#define NUM_DISCS  9
#define NUM_PETAL_GROUPS  6

#define PIN_1  2
#define PIN_2  4
#define PIN_3  5
#define PIN_4  12
#define PIN_5  13
#define PIN_6  14
#define PIN_7  18

#define NUM_LEDS_PIN_1  200
#define NUM_LEDS_PIN_2  184
#define NUM_LEDS_PIN_3  196
#define NUM_LEDS_PIN_4  202
#define NUM_LEDS_PIN_5  198
#define NUM_LEDS_PIN_6  190
#define NUM_LEDS_PIN_7  114

CRGB LEDS_PIN_1[NUM_LEDS_PIN_1];
CRGB LEDS_PIN_2[NUM_LEDS_PIN_2];
CRGB LEDS_PIN_3[NUM_LEDS_PIN_3];
CRGB LEDS_PIN_4[NUM_LEDS_PIN_4];
CRGB LEDS_PIN_5[NUM_LEDS_PIN_5];
CRGB LEDS_PIN_6[NUM_LEDS_PIN_6];
CRGB LEDS_PIN_7[NUM_LEDS_PIN_7];

uint8_t NUM_LEDS[] = {240, 216, 186, 168, 150, 120, 90, 72, 42};

CRGB *leds;

// Generated from javascript prototype
int16_t radiusDisc0[] = {27, 42, 56, 71, 86, 101, 115, 130, 142, 151, 161, 172, 184, 196, 209, 222, 235, 248, 248, 235, 222, 209, 196, 184, 172, 161, 151, 142, 194, 204, 214, 225, 237, 249, 249, 237, 225, 214, 204, 194};
int16_t radiusDisc1[] = {26, 40, 53, 66, 80, 93, 106, 120, 131, 140, 151, 162, 174, 186, 199, 213, 226, 226, 213, 199, 186, 174, 162, 151, 140, 131, 179, 189, 201, 213, 226, 226, 213, 201, 189, 179};
int16_t radiusDisc2[] = {26, 40, 54, 67, 81, 95, 108, 120, 132, 144, 158, 172, 187, 203, 203, 187, 172, 158, 144, 132, 120, 162, 172, 182, 193, 205, 205, 193, 182, 172, 162};
int16_t radiusDisc3[] = {27, 41, 55, 69, 83, 97, 109, 119, 130, 142, 155, 168, 182, 182, 168, 155, 142, 130, 119, 109, 147, 157, 169, 182, 182, 169, 157, 147};
int16_t radiusDisc4[] = {27, 42, 56, 71, 86, 98, 108, 120, 132, 146, 160, 160, 146, 132, 120, 108, 98, 130, 139, 150, 161, 161, 150, 139, 130, 27};
int16_t radiusDisc5[] = {27, 43, 59, 74, 87, 98, 110, 123, 137, 137, 123, 110, 98, 87, 115, 125, 138, 138, 125, 115};
int16_t radiusDisc6[] = {28, 45, 63, 76, 87, 101, 115, 115, 101, 87, 76, 100, 114, 114, 100};
int16_t radiusDisc7[] = {30, 50, 65, 78, 93, 93, 78, 65, 82, 94, 94, 82};
int16_t radiusDisc8[] = {34, 55, 70, 70, 55, 69, 69};
int16_t *radius[] = {
  radiusDisc0,
  radiusDisc1,
  radiusDisc2,
  radiusDisc3,
  radiusDisc4,
  radiusDisc5,
  radiusDisc6,
  radiusDisc7,
  radiusDisc8
};
