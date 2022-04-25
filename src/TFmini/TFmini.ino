/*
 * Using TFMini-S sensor to measure distance paired with M5Stack basic model 
 */
#include <M5Stack.h>
#define TFMINI_FRAME_SIZE 7

int getTFminiData(Stream* streamPtr, int* distance, int* strength) {
    uint8_t lastChar = 0x00;
    uint8_t frame[TFMINI_FRAME_SIZE];

    while (1) {
        if (streamPtr->available()) {      
            uint8_t curChar = streamPtr->read();
            if ((lastChar == 0x59) && (curChar == 0x59)) {
                break;  // Break to begin frame
            } else {
                lastChar = curChar;
            }
        }
    }

    uint8_t checksum = 0x59 + 0x59;
    for (int i=0; i<TFMINI_FRAME_SIZE; i++) {
        while (!streamPtr->available()) {
        }
        frame[i] = streamPtr->read();

        if (i < TFMINI_FRAME_SIZE-1) {
            checksum += frame[i];
        }
    }
    uint8_t checksumByte = frame[TFMINI_FRAME_SIZE-1];
    if (checksum != checksumByte) {
        *distance = -1;
        *strength = -1;
#ifdef DEBUG
        Serial.printf("ERROR: bad checksum %02x, %02x\n\r", checksum, checksumByte);
#endif
        return -1;
    }

    uint16_t dist = (frame[1] << 8) + frame[0];
    uint16_t st = (frame[3] << 8) + frame[2];
    uint8_t reserved = frame[4];
    uint8_t originalSignalQuality = frame[5];

    *distance = dist;
    *strength = st;

    return 0;
}

void setup() {
    M5.begin();
    Serial1.begin(115200, SERIAL_8N1, 5, 2);

    M5.Lcd.setTextSize(3);
    //M5.Lcd.setRotation(3);
}

void loop() {
    int distance = 0;
    int strength = 0;

    if (getTFminiData(&Serial1, &distance, &strength) == 0) {
        Serial.println(distance);
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(20, 20);
        M5.Lcd.printf("%4dcm\r\n", distance);
        M5.Lcd.printf("s: %d", strength);

        //delay(500);
    }
    
}
