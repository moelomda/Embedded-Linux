/*-----------------------------------------------------------------------------------------------------------------------------------------
* File             :       DIO.h
* AUTHOR           :      Mohamed Ahmed Fouad Youssef
* SWC              :       DIO
* Target           :       Atmega32
* Date             :       26/11/2023
* Last Update      :       10/12/2023                                                                                                    */
#ifndef DIO_H_
#define DIO_H_
/*------------------------------------------Inclusion section--------------------------------------*/

#include "BIT_MATH.h"
#include "std_types.h"
#include "Registers.h"
                  
/*-----------------------------------------Inclusion section End------------------------------------*/
/*----------------------------------------------Macro Section---------------------------------------*/


/*---------------------------------------------Macro Section End--------------------------------------*/
/*---------------------------------------------Enumeration Section--------------------------------------*/
typedef enum
{
	DIO_enuPortA,        /*Port A*/
	DIO_enuPortB,          /*Port B*/
	DIO_enuPortC,          /*Port C*/
	DIO_enuPortD,	      /*Port D*/
}DIO_enuPortNumber_t;

typedef enum{
    DIO_enuOutptHigh,      /*Configure Pin as Output High*/
	DIO_enuOutptLow,       /*Configure Pin as Output Low*/
	DIO_enuInputInternalPullUP,	     /*Configure Pin as Input (Internal Pull Up)*/
	DIO_enuInputExternalPullDown,    /*Configure Pin as Input (External Pull Down)*/
	
}DIO_enuPinConfiguration_t;


typedef enum {
	
	DIO_enuInvalidPortNumber,                 /* User Entered Invalid Port Number  */                      
	DIO_enuInvalidPinNumber,                  /* User Entered Invalid Pin Number  */
	DIO_enuInvalidPinLogic,                   /* User Entered Invalid Pin Logic  */
	DIO_enuIvalidpinConfiguration,            /* User Entered Invalid Pin Configuration*/                              
	DIO_enuSucceded,                          /* Operation Completed Successfully */  
	DIO_enuNullPtr, 
	
} DIO_enuErrorStatus_t;                         /* User Passed A NULL Pointer */
	
typedef enum {
	
	
	DIO_enuPin0,       /*pin 0*/
	DIO_enuPin1,      /*Pin 1*/
    DIO_enuPin2,      /*Pin 2*/
    DIO_enuPin3,	 /*Pin 3*/
	DIO_enuPin4,     /*Pin 4*/
	DIO_enuPin5,      /*Pin 5*/
	DIO_enuPin6,       /*Pin 6*/
	DIO_enuPin7,        /*Pin 7*/
	   
		
}DIO_enuPinNumber_t;

typedef enum {
	DIO_enuLogicLow,                     /*Input Low*/
	DIO_enuLogicHigh,                   /*Input High*/                   
}DIO_enuSetPinLogic_t;
	
/*---------------------------------------------Enumeration Section End--------------------------------------*/

/*---------------------------------------------Function Declaration Section ------------------------------------------*/
/* 
 *@brief  : Function to Set the Configuration of a Specific Pin.
 *@param  : Port Number ,Pin Number,Pin Configuration(Output High / Output Low / Internal Pull up / External PullDown ).
 *@return : Error State
 Note that each port contains 8 Pins (from Pin0 to Pin7 )
*/

DIO_enuErrorStatus_t DIO_enuSetPinConfiguration( DIO_enuPortNumber_t Copy_PortNum , DIO_enuPinNumber_t Copy_PinNum , DIO_enuPinConfiguration_t Copy_PinConfiguration );
/* 
 *@brief  : Function to Set the Pins to be Logic HIGH  or Logic LOW.
 *@param  : Port Number ,Pin Number,Logic State(HIGH/LOW).
 *@return : Error State
*/
DIO_enuErrorStatus_t DIO_enuSetPinLogic(DIO_enuPortNumber_t Copy_PortNum , DIO_enuPinNumber_t Copy_PinNUm , DIO_enuSetPinLogic_t Copy_PinLogic);
/*
*@brief  : Function to Read the Logic State of the Pin (Is it HIGH or LOW).
*@param  : Port Number,Pin Number, Pointer points to unsigned char passed by address (to return the value of pin state).
*@return : Error State
*/ 
DIO_enuErrorStatus_t DIO_enuGetPinLogic(DIO_enuPortNumber_t Copy_PortNum ,  DIO_enuPinNumber_t Copy_PinNUm , u8 *Add_Pu8PinValue);  
 /*
 *@brief : Function to Set the whole Port(8 pins) at one time to be Logic HIGH  or Logic LOW.
 *@param : Port Number,Logic State(HIGH/LOW).
 *@return: Error State.
  */     
DIO_enuErrorStatus_t DIO_enuSetPortLogic(DIO_enuPortNumber_t Copy_PortNum , DIO_enuSetPinLogic_t Copy_PinsLogic);



/*---------------------------------------------Function Declaration Section End------------------------------------------*/


#endif