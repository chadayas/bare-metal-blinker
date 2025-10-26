
#include <cstdint>
using std::uint32_t;

// GPIOA Registers

#define GPIOA_BASE 0x40020000
#define GPIOA_MODER *((volatile uint32_t*) (GPIOA_BASE + 0x00))  
 
#define GPIOA_ODR *((volatile uint32_t*) (GPIOA_BASE 0x14))  
#define GPIOA_BSRR  *((volatile uint32_t*) (GPIOA_BASE + 0x18))

#define GPIOA_OTYPER *((volatile uint32_t*) (GPIOA_BASE + 0x04))  
#define GPIOA_OSPEEDR *((volatile uint32_t*)( GPIOA_BASE + 0x08))  

#define GPIOA_PUPDR *((volatile uint32_t*) (GPIOA_BASE + 0x0C))  

// RCC for opening the clock gates GPIOA.  

#define RCC 0x40023800 // boundary address
#define RCC_AHB1  *((volatile uint32_t*) (RCC + 0x30))  

// MODER5[1:0] for PA5 remember we look for 2y and 2y+1 which is bit pos 10 and 11.
// y  = 5

void GPIOA_config(){
	
	GPIOA_MODER |= (0 << 11);
	GPIOA_MODER |= (1 << 10);

	GPIOA_OTYPER |= (0 << 5);
	
	GPIOA_OSPEEDR |= (0 << 10);	
	GPIOA_OSPEEDR |= (1 << 11);	
	
	GPIOA_PUPDR &= ~((1 << 10)|(1 << 11));
}

void open_cGates() {
	
	RCC_AHB1 |= (1 << 0);
}

void delay() {

	for (volatile int i =0; i < 5000000; ++i);
}

int main() 
{

	open_cGates();
	GPIOA_config();
	
	while(1){
		
		GPIOA_BSRR = (1 << 5);
		delay();
		GPIOA_BSRR = (1 << 21);
		delay();
	}

}


