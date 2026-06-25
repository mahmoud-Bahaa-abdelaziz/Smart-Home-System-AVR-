/*
 * LCD_program.c
 *
 *  Created on: Jun 30, 2025
 *      Author: Ahmed Saeed
 */

#include "STD_Types.h"
#include "BIT_Math.h"
#include "LCD_interfac.h"
#include "LCD_config.h"
#include <util/delay.h>
#include "DIO_intaeface.h"

void LCD_Init(void)
{
    // Set control pins as output
    DIO_SetPinDirection(LCD_CTL_PORT, LCD_RS_PIN, DIO_OUTPUT);
    DIO_SetPinDirection(LCD_CTL_PORT, LCD_RW_PIN, DIO_OUTPUT);
    DIO_SetPinDirection(LCD_CTL_PORT, LCD_E_PIN,  DIO_OUTPUT);

    // Set data port as output
    DIO_SetPortDirection(LCD_DATA_PORT, 0xFF); // All 8 pins

    // Initialization sequence
    _delay_ms(35);
    LCD_SendCommand(lcd_Home);
    _delay_ms(15);
    LCD_SendCommand(lcd_FunctionSet8bit);
    _delay_ms(1);
    LCD_SendCommand(lcd_DisplayOn);
    _delay_ms(1);
    LCD_SendCommand(lcd_Clear);
    _delay_ms(15);
    LCD_SendCommand(lcd_EntryMode);
    _delay_ms(2);
}

void LCD_SendChar(u8 character)
{
    // RS = 1 (Data)
    DIO_SetPinValue(LCD_CTL_PORT, LCD_RS_PIN, DIO_HIGH);
    // RW = 0 (Write)
    DIO_SetPinValue(LCD_CTL_PORT, LCD_RW_PIN, DIO_LOW);
    // Put data on data bus
    DIO_SetPortValue(LCD_DATA_PORT, character);
    // Enable pulse
    DIO_SetPinValue(LCD_CTL_PORT, LCD_E_PIN, DIO_HIGH);
    _delay_us(1);
    DIO_SetPinValue(LCD_CTL_PORT, LCD_E_PIN, DIO_LOW);
    _delay_ms(2);
}

void LCD_SendCommand(u8 command)
{
    // RS = 0 (Command)
    DIO_SetPinValue(LCD_CTL_PORT, LCD_RS_PIN, DIO_LOW);
    // RW = 0 (Write)
    DIO_SetPinValue(LCD_CTL_PORT, LCD_RW_PIN, DIO_LOW);
    // Put command on data bus
    DIO_SetPortValue(LCD_DATA_PORT, command);
    // Enable pulse
    DIO_SetPinValue(LCD_CTL_PORT, LCD_E_PIN, DIO_HIGH);
    _delay_us(1);
    DIO_SetPinValue(LCD_CTL_PORT, LCD_E_PIN, DIO_LOW);
    _delay_ms(2);
}

void LCD_GotoXY(u8 Y, u8 X)
{
    if (X >= 1 && X <= 16)
    {
        switch(Y)
        {
            case 1:
                LCD_SendCommand(0x80 + (X - 1));
                break;
            case 2:
                LCD_SendCommand(0xC0 + (X - 1));
                break;
        }
    }
}

void LCD_Clear(void)
{
    LCD_SendCommand(lcd_Clear);
    _delay_ms(2);
}

void LCD_SendString(u8* str)
{
    while (*str)
    {
        LCD_SendChar(*str++);
    }
}

void LCD_SendNumber(u32 number)
{
    u8 str[11];
    u8 i = 0;

    if (number == 0)
    {
        LCD_SendChar('0');
        return;
    }

    while (number > 0)
    {
        str[i++] = (number % 10) + '0';
        number /= 10;
    }

    while (i > 0)
    {
        LCD_SendChar(str[--i]);
    }
}
