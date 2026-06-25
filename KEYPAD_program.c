#include "STD_Types.h"
#include "BIT_Math.h"
#include "DIO_intaeface.h"
#include "KEYPAD_interface.h"
#include "KEYPAD_config.h"
#include <util/delay.h>

// Struct for handling pins on different ports
typedef struct {
    u8 port;
    u8 pin;
} KEYPAD_Pin;

// Define Rows (PORT, PIN)
KEYPAD_Pin Rows[4] = {
    {KEYPAD_ROW0_PORT, KEYPAD_ROW0_PIN},
    {KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN},
    {KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN},
    {KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN}
};

// Define Cols (PORT, PIN)
KEYPAD_Pin Cols[4] = {
    {KEYPAD_COL0_PORT, KEYPAD_COL0_PIN},
    {KEYPAD_COL1_PORT, KEYPAD_COL1_PIN},
    {KEYPAD_COL2_PORT, KEYPAD_COL2_PIN},
    {KEYPAD_COL3_PORT, KEYPAD_COL3_PIN}
};

void KEYPAD_Init(void)
{
    // Set Rows as OUTPUT -> High (inactive)
    for (u8 i = 0; i < 4; i++) {
        DIO_SetPinDirection(Rows[i].port, Rows[i].pin, DIO_OUTPUT);
        DIO_SetPinValue(Rows[i].port, Rows[i].pin, DIO_HIGH);
    }

    // Set Cols as INPUT -> Pullup enabled
    for (u8 i = 0; i < 4; i++) {
        DIO_SetPinDirection(Cols[i].port, Cols[i].pin, DIO_INPUT);
        DIO_Activate_Pullup(Cols[i].port, Cols[i].pin);
    }
}

u8 KEYPAD_GetPressedKey(void)
{
    for (u8 row = 0; row < 4; row++) {
        // Activate current row (set LOW)
        DIO_SetPinValue(Rows[row].port, Rows[row].pin, DIO_LOW);

        for (u8 col = 0; col < 4; col++) {
            if (DIO_ReadPinValue(Cols[col].port, Cols[col].pin) == KEY_IS_PRESSED) {
                _delay_ms(20); // debounce

                // Wait until released
                while (DIO_ReadPinValue(Cols[col].port, Cols[col].pin) == KEY_IS_PRESSED);

                _delay_ms(20);

                // Deactivate row again
                DIO_SetPinValue(Rows[row].port, Rows[row].pin, DIO_HIGH);

                return KEYPAD_KEYS[row][col];
            }
        }

        // Deactivate row (set HIGH again)
        DIO_SetPinValue(Rows[row].port, Rows[row].pin, DIO_HIGH);
    }

    return 0xFF; // No key pressed
}
