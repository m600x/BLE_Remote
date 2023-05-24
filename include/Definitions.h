/*******************************************************************************
 * Apps definition
*******************************************************************************/

#define BLE_NAME                    "MotiveMonkey"
#define BLE_AUTHOR                  "M600"
#define PIN_A                       21
#define PIN_B                       13
#define PIN_C                       12
#define PIN_D                       14
#define PIN_CENTER                  27
#define PIN_BTN_A                   23
#define PIN_BTN_B                   22
#define SPLASH_TIMEOUT_MS           3000
#define SCREEN_TIMEOUT_MS           5000
#define LONG_KEYPRESS_THRESHOLD_MS  300
#define SHORT_KEYPRESS_DELAY_MS     20
#define LONG_KEYPRESS_DELAY_MS      100

/*******************************************************************************
 * Apps definition
*******************************************************************************/

#define APP_UNITS    3

const app_unit osmand = {"OsmAnd+",
                        LOGO_OSMAND,
                        {"UP", "LEFT", "DOWN", "RIGHT", "MyLoc"},
                        {KEY_UP_ARROW, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, 'C'},
                        {"ZOOM +", "ZOOM -", "ZOOM -", "ZOOM +", "Orientation"},
                        {KEY_NUM_PLUS, KEY_NUM_MINUS,  KEY_NUM_PLUS,  KEY_NUM_MINUS,    'D'}};
const app_unit scenic = {"Scenic",
                        LOGO_SCENIC,
                        {"UP", "LEFT", "DOWN", "RIGHT", "Enter"},
                        {KEY_UP_ARROW, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, KEY_RETURN},
                        {"UP", "LEFT", "DOWN", "RIGHT", "Return"},
                        {0,            0,              0,              0,               KEY_ESC}};
const app_unit spotify = {"Spotify",
                        LOGO_SPOTIFY,
                        {"Volume +", "Previous", "Volume -", "Next", "Play/Pause"},
                        {},
                        {"Volume +", "Previous", "Volume -", "Next", "Play/Pause"},
                        {}};
const uint8_t *keymap_media[5] = {
                                    KEY_MEDIA_VOLUME_UP,
                                    KEY_MEDIA_PREVIOUS_TRACK,
                                    KEY_MEDIA_VOLUME_DOWN,
                                    KEY_MEDIA_NEXT_TRACK,
                                    KEY_MEDIA_PLAY_PAUSE
                                };

const app_unit apps[] = {osmand, scenic, spotify};

typedef struct {
    String name;
    const unsigned char *logo PROGMEM;
    String keyShortName[5];
    uint8_t keyShortMap[5];
    String keyLongName[5];
    uint8_t keyLongMap[5];
} app_unit; 