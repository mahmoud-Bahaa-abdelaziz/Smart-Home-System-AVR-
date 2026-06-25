#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TWI_Interface.h"
#include "EEPROM_Interface.h"
#include "LCD_interfac.h"
#include "KEYPAD_interface.h"
#include "Lm35_interface.h"
#include "ADC_interface.h"
#include "DIO_intaeface.h"
#include "DCMOTOR_interface.h"  // added
#include <util/delay.h>

#define PASSWORD_LENGTH      4
#define EEPROM_DEVICE        0
#define EEPROM_START_ADDRESS 0x0000

#define SERVO_PORT  DIO_PORTB
#define SERVO_PIN   DIO_PIN0
#define LED_PORT    DIO_PORTB
#define LED_PIN     DIO_PIN1
#define BUZZER_PORT DIO_PORTB
#define BUZZER_PIN  DIO_PIN7

// ================= Helper Functions =================
u8 GetKey(void)
{
    u8 k;
    do { k = KEYPAD_GetPressedKey(); } while(k == 0xFF);
    _delay_ms(50);
    while(KEYPAD_GetPressedKey() != 0xFF);
    _delay_ms(50);
    if(k <= 9) k += '0'; // convert numeric keys to ASCII
    return k;
}

void Servo_Open(void)
{
    u8 i;
    for(i=0;i<50;i++)
    {
        DIO_SetPinValue(SERVO_PORT, SERVO_PIN, DIO_HIGH);
        _delay_ms(2);
        DIO_SetPinValue(SERVO_PORT, SERVO_PIN, DIO_LOW);
        _delay_ms(18);
    }
}

void Buzzer_On(void)  { DIO_SetPinValue(BUZZER_PORT, BUZZER_PIN, DIO_HIGH); }
void Buzzer_Off(void) { DIO_SetPinValue(BUZZER_PORT, BUZZER_PIN, DIO_LOW); }
void Buzzer_Beep(u16 delay_ms)
{
    Buzzer_On();
    _delay_ms(delay_ms);
    Buzzer_Off();
}

void GetPassword(u8 *pass)
{
    u8 i, key;
    for(i=0;i<PASSWORD_LENGTH;i++)
    {
        key = GetKey();
        pass[i] = key;
        LCD_SendChar('*');
    }
}

u8 ComparePasswords(u8 *pass1, u8 *pass2)
{
    for(u8 i=0;i<PASSWORD_LENGTH;i++)
    {
        if(pass1[i] != pass2[i]) return 0;
    }
    return 1;
}

void Password_Setup(u8 *stored)
{
    u8 pass1[PASSWORD_LENGTH];
    u8 pass2[PASSWORD_LENGTH];
    u8 ok = 0;
    while(!ok)
    {
        LCD_Clear();
        LCD_SendString("Set Password:");
        LCD_GotoXY(2,1);
        GetPassword(pass1);

        _delay_ms(500);
        LCD_Clear();
        LCD_SendString("Confirm Pass:");
        LCD_GotoXY(2,1);
        GetPassword(pass2);

        if(ComparePasswords(pass1, pass2))
        {
            for(u8 i=0;i<PASSWORD_LENGTH;i++)
            {
                EEPROM_voidWriteByte(EEPROM_START_ADDRESS+i, pass1[i], EEPROM_DEVICE);
                stored[i] = pass1[i];
            }
            LCD_Clear();
            LCD_SendString("Password Saved!");
            Buzzer_Beep(200);
            _delay_ms(1500);
            ok = 1;
        }
        else
        {
            LCD_Clear();
            LCD_SendString("Not Match! Retry");
            _delay_ms(1500);
        }
    }
}

// ================= Temperature & Motor Control =================
void Display_Temperature(void)
{
    u8 temp;
    LCD_Clear();
    LCD_SendString((u8*)"Temp: ");
    while(1)
    {
        temp = Lm35_ReadTemperature();
        LCD_GotoXY(1,6);
        LCD_SendNumber(temp);
        LCD_SendChar('C');

        if(temp > 20)
        {
            Buzzer_Beep(500);
            DCMOTOR_Forward();  // move DC motor if temp > 20°C
        }
        else
        {
            DCMOTOR_Stop();
        }

        _delay_ms(1000);

        u8 k = KEYPAD_GetPressedKey();
        if(k == '#') break; // allow return to password input
    }
}

// ================= Main =================
int main(void)
{
    u8 enteredPassword[PASSWORD_LENGTH];
    u8 storedPassword[PASSWORD_LENGTH];
    u8 key;
    u8 i,j;

    // Initialization
    TWI_voidMasterInit(0);
    LCD_Init();
    KEYPAD_Init();
    DCMOTOR_Init();  // initialize motor

    DIO_SetPinDirection(SERVO_PORT, SERVO_PIN, DIO_OUTPUT);
    DIO_SetPinDirection(LED_PORT, LED_PIN, DIO_OUTPUT);
    DIO_SetPinDirection(BUZZER_PORT, BUZZER_PIN, DIO_OUTPUT);

    DIO_SetPinValue(LED_PORT, LED_PIN, DIO_LOW);
    DIO_SetPinValue(BUZZER_PORT, BUZZER_PIN, DIO_LOW);

    ADC_Config_t adc_config = { ADC5, ADC_FCPU_8, AVCC, ADLAR_RIGHT, ADIE_DISABLE };
    ADC_Init(&adc_config);

    // Step 1: Setup Password
    Password_Setup(storedPassword);

    // Step 2: Enter Password loop
    while(1)
    {
        LCD_Clear();
        LCD_SendString("Enter Password:");
        LCD_GotoXY(2,1);
        GetPassword(enteredPassword);

        u8 correct = ComparePasswords(enteredPassword, storedPassword);

        LCD_Clear();
        if(correct)
        {
            DIO_SetPinValue(LED_PORT, LED_PIN, DIO_HIGH);
            LCD_SendString("Correct Password");
            _delay_ms(500);

            Servo_Open();
            for(j=0;j<10;j++)
            {
                Buzzer_Beep(200);
                _delay_ms(200);
            }

            Display_Temperature();
        }
        else
        {
            DIO_SetPinValue(LED_PORT, LED_PIN, DIO_LOW);
            LCD_SendString("Incorrect!");

            for(j=0;j<5;j++)
            {
                Buzzer_Beep(200);
                _delay_ms(200);
            }

            _delay_ms(500);

        }
    }
}


