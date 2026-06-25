/*
 * DIO_program.c
 *
 *  Created on: Aug 25, 2025
 *      Author: Ahmed Saeed
 */
#include "STD_Types.h"
#include "BIT_Math.h"
#include "DIO_intaeface.h"
#include "DIO_private.h"


void DIO_SetPinDirection(u8 PortName ,u8 PinNumber,u8 Direction)
{
	switch(PortName)
	{
	case  DIO_PORTA :
		if(Direction==DIO_OUTPUT)
		{
			SET_BIT(DDRA,PinNumber);
		}
		else if (Direction==DIO_INPUT)
		{
			CLR_BIT(DDRA,PinNumber);
		}
		break;

	case  DIO_PORTB :
		if(Direction==DIO_OUTPUT)
		{
			SET_BIT(DDRB,PinNumber);
		}
		else if (Direction==DIO_INPUT)
		{
			CLR_BIT(DDRB,PinNumber);
		}
		break;
	case  DIO_PORTC :
		if(Direction==DIO_OUTPUT)
		{
			SET_BIT(DDRC,PinNumber);
		}
		else if (Direction==DIO_INPUT)
		{
			CLR_BIT(DDRC,PinNumber);
		}
		break;

	case  DIO_PORTD :
		if(Direction==DIO_OUTPUT)
		{
			SET_BIT(DDRD,PinNumber);
		}
		else if (Direction==DIO_INPUT)
		{
			CLR_BIT(DDRD,PinNumber);
		}
		break;
	}

}
void DIO_SetPinValue(u8 PortName ,u8 PinNumber,u8 Value)
{
	switch(PortName)
	{
	case  DIO_PORTA :
		if(Value==DIO_HIGH)
		{
			SET_BIT(PORTA,PinNumber);
		}
		else if (Value==DIO_LOW)
		{
			CLR_BIT(PORTA,PinNumber);
		}
		break;
	case  DIO_PORTB :
		if(Value==DIO_HIGH)
		{
			SET_BIT(PORTB,PinNumber);
		}
		else if (Value==DIO_LOW)
		{
			CLR_BIT(PORTB,PinNumber);
		}
		break;

	case  DIO_PORTC :
		if(Value==DIO_HIGH)
		{
			SET_BIT(PORTC,PinNumber);
		}
		else if (Value==DIO_LOW)
		{
			CLR_BIT(PORTC,PinNumber);
		}
		break;
	case  DIO_PORTD :
		if(Value==DIO_HIGH)
		{
			SET_BIT(PORTD,PinNumber);
		}
		else if (Value==DIO_LOW)
		{
			CLR_BIT(PORTD,PinNumber);
		}
		break;

	}

}
u8 DIO_ReadPinValue(u8 PortName ,u8 PinNumber)
{
	u8 state;
	switch(PortName)
	{
	case DIO_PORTA :
		state=GET_BIT(PINA,PinNumber);
		break;
	case DIO_PORTB :
		state=GET_BIT(PINB,PinNumber);
		break;
	case DIO_PORTC :
		state=GET_BIT(PINC,PinNumber);
		break;
	case DIO_PORTD :
		state=GET_BIT(PIND,PinNumber);
		break;
	}
	return state;
}


void DIO_SetPortDirection(u8 PortName ,u8 Direction)
{
	switch(PortName)
	{
	case DIO_PORTA :
		DDRA =Direction;
		break ;

	case DIO_PORTB :
		DDRB =Direction;
		break ;
	case DIO_PORTC :
		DDRC =Direction;
		break ;
	case DIO_PORTD :
		DDRD =Direction;
		break ;
	}
}
void DIO_SetPortValue(u8 PortName ,u8 Value)
{
	switch(PortName)
	{
	case DIO_PORTA :
		PORTA =Value;
		break ;
	case DIO_PORTB :
		PORTB =Value;
		break ;
	case DIO_PORTC :
		PORTC =Value;
		break ;
	case DIO_PORTD :
		PORTD =Value;
		break ;
	}
}

void DIO_SetPinSRangeDirection(u8 PortName,u8 start ,u8 end,u8 Direction)

{
	for (u8 i= start ;i<=end;i++)
	{
		DIO_SetPinDirection(PortName,i,Direction);
	}

}


void DIO_Activate_Pullup(u8 PortName, u8 PinNumber)
{
	switch (PortName)
	{
	case DIO_PORTA:
		SET_BIT(PORTA, PinNumber);
		break;
	case DIO_PORTB:
		SET_BIT(PORTB, PinNumber);
		break;
	case DIO_PORTC:
		SET_BIT(PORTC, PinNumber);
		break;
	case DIO_PORTD:
		SET_BIT(PORTD, PinNumber);
		break;
	}
}

void DIO_TogglePin(u8 PortName, u8 PinNumber)
{
    switch(PortName)
    {
    case DIO_PORTA: TOG_BIT(PORTA, PinNumber); break;
    case DIO_PORTB: TOG_BIT(PORTB, PinNumber); break;
    case DIO_PORTC: TOG_BIT(PORTC, PinNumber); break;
    case DIO_PORTD: TOG_BIT(PORTD, PinNumber); break;
    }
}

