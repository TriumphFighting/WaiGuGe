#include "delay.h"


void tb_delay_init(void) {

}

void tb_delay(u16 t) {
	while(t--);
	return;
}

void tb_delay_ns(u16 t) {
	while(t--);
	return;
}

void tb_delay_us(u16 t) {  
   while(t--) {
      tb_delay(6);    
   }	
}




void delay_ms(u16 t)//1ms��ʱ
{	 		  	  
	 while(t--)
		 {
      tb_delay_us(1000);    
     }
} 









































