/*-----------------------------------------------------------------------------------------------------------------------------------------
* File             :       DIO.c                                                                                                              
* AUTHOR           :      Mohamed Ahmed Fouad Youssef                                                                                                                                                                                                            
* SWC              :       DIO                                                                                                                 
* Target           :       Atmega32   
* Date             :       26/11/2023                                                                                                                                                                                                       
* Last Update      :       10/12/2023                                                                                                    */
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------Inclusion Section-----------------------------------------*/
#include "DIO.h"
/*---------------------------------------------------Inclusion Section End-----------------------------------------*/
#define  NUM_OF_PORTS 4

/*----------------------------------------------------API'S Implementation Section-----------------------------------------------*/
DIO_enuErrorStatus_t DIO_enuSetPinConfiguration( DIO_enuPortNumber_t Copy_PortNum , DIO_enuPinNumber_t Copy_PinNum , DIO_enuPinConfiguration_t Copy_PinConfiguration ){
	DIO_enuErrorStatus_t Loc_enuErorState=  DIO_enuSucceded;
	
	if (Copy_PortNum > NUM_OF_PORTS || Copy_PortNum < DIO_enuPortA  )
	{
		Loc_enuErorState= DIO_enuInvalidPortNumber;
	}
	else if (Copy_PinNum > DIO_enuPin7 || Copy_PinNum <DIO_enuPin0)
	{
		Loc_enuErorState=  DIO_enuInvalidPinNumber;
	}
	else if  (Copy_PinConfiguration < DIO_enuOutptHigh || Copy_PinConfiguration > DIO_enuInputExternalPullDown)
	{
		
		Loc_enuErorState = DIO_enuIvalidpinConfiguration;
	}
	
	else
	{
		
		switch(Copy_PortNum)
		{
			case DIO_enuPortA :
			
			switch(Copy_PinConfiguration)
			{
				
				case DIO_enuOutptLow:
				SET_BIT(DDRA,Copy_PinNum);
				CLR_BIT(PORTA,Copy_PinNum);
				
				break;
				case DIO_enuOutptHigh:
				SET_BIT(DDRA,Copy_PinNum);
				SET_BIT(PORTA,Copy_PinNum);
				
				break;
				case DIO_enuInputInternalPullUP:
				CLR_BIT(DDRA,Copy_PinNum);
				SET_BIT(PORTA,Copy_PinNum);
				break;
				case DIO_enuInputExternalPullDown:
				CLR_BIT(DDRA,Copy_PinNum);
				CLR_BIT(PORTA,Copy_PinNum);
				break;
				
				
				
			}
			break;
			
			case DIO_enuPortB :
			
			switch(Copy_PinConfiguration)
			{
				
				case DIO_enuOutptLow:
				SET_BIT(DDRB,Copy_PinNum);
				CLR_BIT(PORTB,Copy_PinNum);
				
				break;
				case DIO_enuOutptHigh:
				SET_BIT(DDRB,Copy_PinNum);
				SET_BIT(PORTB,Copy_PinNum);
				
				break;
				case DIO_enuInputInternalPullUP:
				CLR_BIT(DDRB,Copy_PinNum);
				SET_BIT(PORTB,Copy_PinNum);
				break;
				case DIO_enuInputExternalPullDown:
				CLR_BIT(DDRB,Copy_PinNum);
				CLR_BIT(PORTB,Copy_PinNum);
				break;
				
				
			}
			break;
			
			case DIO_enuPortC :
			switch(Copy_PinConfiguration)
			{
				
				case DIO_enuOutptLow:
				SET_BIT(DDRC,Copy_PinNum);
				CLR_BIT(PORTC,Copy_PinNum);
				
				break;
				case DIO_enuOutptHigh:
				SET_BIT(DDRC,Copy_PinNum);
				SET_BIT(PORTC,Copy_PinNum);
				
				break;
				case DIO_enuInputInternalPullUP:
				CLR_BIT(DDRC,Copy_PinNum);
				SET_BIT(PORTC,Copy_PinNum);
				break;
				case DIO_enuInputExternalPullDown:
				CLR_BIT(DDRC,Copy_PinNum);
				CLR_BIT(PORTC,Copy_PinNum);
				break;
				
				
			}
			break;
			
			case DIO_enuPortD :
			switch(Copy_PinConfiguration)
			{
				case DIO_enuOutptLow:
				SET_BIT(DDRD,Copy_PinNum);
				CLR_BIT(PORTD,Copy_PinNum);
				
				break;
				case DIO_enuOutptHigh:
				SET_BIT(DDRD,Copy_PinNum);
				SET_BIT(PORTD,Copy_PinNum);
				
				break;
				case DIO_enuInputInternalPullUP:
				CLR_BIT(DDRD,Copy_PinNum);
				SET_BIT(PORTD,Copy_PinNum);
				break;
				case DIO_enuInputExternalPullDown:
				CLR_BIT(DDRD,Copy_PinNum);
				CLR_BIT(PORTD,Copy_PinNum);
				break;
				
				
				
			}
			break;
			
			
		}
		
	}
	
	return Loc_enuErorState;
}
DIO_enuErrorStatus_t DIO_enuSetPinLogic(DIO_enuPortNumber_t Copy_PortNum , DIO_enuPinNumber_t Copy_PinNUm , DIO_enuSetPinLogic_t Copy_PinLogic)
{ 
	  DIO_enuErrorStatus_t Loc_enuErorState= DIO_enuSucceded;
	  
	if (Copy_PortNum > NUM_OF_PORTS || Copy_PortNum < DIO_enuPortA  )
	{
       Loc_enuErorState= DIO_enuInvalidPortNumber;
	}
	else if(Copy_PinNUm > DIO_enuPin7 || Copy_PinNUm < DIO_enuPin0)
	{
        Loc_enuErorState= DIO_enuInvalidPinNumber;
	}
	else if (Copy_PinLogic != DIO_enuLogicHigh && Copy_PinLogic != DIO_enuLogicLow)
	{
		Loc_enuErorState= DIO_enuInvalidPinLogic;
	}
	else
	{
	   switch(Copy_PortNum)	
	   {
		   case DIO_enuPortA:
		          switch(Copy_PinLogic)
				  {
					  case DIO_enuLogicHigh :
					      SET_BIT(PORTA,Copy_PinNUm);
					       break;
					  case DIO_enuLogicLow :
					      CLR_BIT(PORTA,Copy_PinNUm);
						   break;
					  default:
					       break; 
				  }
				  break;
			case DIO_enuPortB:
			         switch(Copy_PinLogic)
			         {
				         case DIO_enuLogicHigh :
				         SET_BIT(PORTB,Copy_PinNUm);
				         break;
				         case DIO_enuLogicLow :
				         CLR_BIT(PORTB,Copy_PinNUm);
				         break;
				         default:
				         break;
			         }
			         break;
			case DIO_enuPortC:
			     switch(Copy_PinLogic)
			      {
				    case DIO_enuLogicHigh :
				       SET_BIT(PORTC,Copy_PinNUm);
				        break;
				    case DIO_enuLogicLow :
				       CLR_BIT(PORTC,Copy_PinNUm);
				       break;
				    default:
				      break;
			      }
			   break;
			case DIO_enuPortD:
			   switch(Copy_PinLogic)
			    {
				  case DIO_enuLogicHigh :
				      SET_BIT(PORTD,Copy_PinNUm);
				       break;
				  case DIO_enuLogicLow :
				      CLR_BIT(PORTD,Copy_PinNUm);
				       break;
				 default:
				       break;
			    }
			break;	
			
		   default:
		      break;
 }
		
		
		
}
	
	return Loc_enuErorState;
	
}
DIO_enuErrorStatus_t DIO_enuGetPinLogic(DIO_enuPortNumber_t Copy_PortNum ,  DIO_enuPinNumber_t Copy_PinNUm , u8 *Add_Pu8PinValue)
{
	DIO_enuErrorStatus_t Loc_enuErorState= DIO_enuSucceded;
	
  if(Copy_PortNum > NUM_OF_PORTS || Copy_PortNum < DIO_enuPortA)
  {
	Loc_enuErorState = DIO_enuInvalidPortNumber;
  }
  else if (Copy_PinNUm > DIO_enuPin7 || Copy_PinNUm < DIO_enuPin0)
  {
	  Loc_enuErorState = DIO_enuInvalidPinNumber;
	  
  }
  else if (!Add_Pu8PinValue)
  {
	Loc_enuErorState= DIO_enuNullPtr;  	  
  }
  else 
  {
	switch(Copy_PortNum)
	{
	  case  DIO_enuPortA:
	        *Add_Pu8PinValue=GET_BIT(PINA,Copy_PinNUm);
			break;
	  case  DIO_enuPortB:
	       *Add_Pu8PinValue=GET_BIT(PINB,Copy_PinNUm);
	        break;
	  case  DIO_enuPortC:
	      *Add_Pu8PinValue=GET_BIT(PINC,Copy_PinNUm);
	       break;
	  case  DIO_enuPortD:
	      *Add_Pu8PinValue=GET_BIT(PIND,Copy_PinNUm);
	       break;
	  default:
	       break;
		
	}
   	  
    

  }
	
	
	 return Loc_enuErorState;
	
}
DIO_enuErrorStatus_t DIO_enuSetPortLogic(DIO_enuPortNumber_t Copy_PortNum , DIO_enuSetPinLogic_t Copy_PinsLogic)
{
	DIO_enuErrorStatus_t Loc_enuErorState= DIO_enuSucceded;
	if (Copy_PortNum > NUM_OF_PORTS || Copy_PortNum < DIO_enuPortA)
	{
		Loc_enuErorState= DIO_enuInvalidPortNumber;
	}
	else if (Copy_PinsLogic != DIO_enuLogicHigh && Copy_PinsLogic != DIO_enuLogicLow  )
	{
	     Loc_enuErorState= DIO_enuInvalidPinLogic;	
	}
	else
	{
	 switch (Copy_PortNum)
 {
 case DIO_enuPortA :
		 switch(Copy_PinsLogic)
		 {
			
		 case DIO_enuLogicHigh:
			ASSIGN_REG(PORTA,0xff);
			break;
		 case DIO_enuLogicLow:
			ASSIGN_REG(PORTA,0x00);
			break;
		 default:
			break;
		}
	break;
		
 case DIO_enuPortB :
		switch(Copy_PinsLogic)
		{
			
		case  DIO_enuLogicHigh:
			ASSIGN_REG(PORTB,0xff);
			break;
		case  DIO_enuLogicLow:
			ASSIGN_REG(PORTB,0x00);
			break;
		default:
			break;
		}
	break;
 case DIO_enuPortC :
		 switch(Copy_PinsLogic)
		{
			
		case DIO_enuLogicHigh:
			ASSIGN_REG(PORTC,0xff);
			break;
		case DIO_enuLogicLow :
			ASSIGN_REG(PORTC,0x00);
			break;
		default:
			break;
		}
	break;
 case DIO_enuPortD :
		switch(Copy_PinsLogic)
		{
			
		case  DIO_enuLogicHigh:
			ASSIGN_REG(PORTD,0xff);
			break;
		case  DIO_enuLogicLow:
			ASSIGN_REG(PORTD,0x00);
			break;
		default:
			break;
		}
	break;
		
default:
		   break;
}
        
}
     return Loc_enuErorState;
}



/*----------------------------------------------------API'S Implementation Section End-----------------------------------------------*/