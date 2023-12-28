/*-----------------------------------------------------------------------------------------------------------------------------------------
* File             :       Task1.c                                                                                                              
* AUTHOR           :      Mohamed Ahmed Fouad Youssef                                                                                                                                                                                                            
* SWC              :       DIO                                                                                                                 
* Target           :       Atmega32   
* Date             :       26/11/2023                                                                                                                                                                                                       
* Last Update      :       2/12/2023                                                                                                    */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------Inclusion Section-----------------------------------------*/
#include "BIT_MATH.h"
#include "DIO.h"
#include "std_types.h"
#include "utildelay.h"

/*---------------------------------------------------Inclusion Section End-----------------------------------------*/
/*----------------------------------------------------Main Program Section---------------------------------------------------*/
int main(void)

{
	DIO_enuSetPinConfiguration(DIO_enuPortA,DIO_enuPin1,DIO_enuOutptHigh);
	DIO_enuSetPinConfiguration(DIO_enuPortA,DIO_enuPin2,DIO_enuOutptHigh);
     
    while (1){

	    DIO_enuSetPinLogic(DIO_enuPortA , DIO_enuPin1 , DIO_enuLogicHigh);
	    DIO_enuSetPinLogic(DIO_enuPortA , DIO_enuPin2 , DIO_enuLogicLow); 
	      _delay_ms(100);
	    DIO_enuSetPinLogic(DIO_enuPortA , DIO_enuPin1 , DIO_enuLogicLow);
	    DIO_enuSetPinLogic(DIO_enuPortA , DIO_enuPin2 , DIO_enuLogicHigh);
		
	     _delay_ms(100); 

    }

   
	  
	  
	  
	  

}
/*----------------------------------------------------Main Program Section End---------------------------------------------------*/
