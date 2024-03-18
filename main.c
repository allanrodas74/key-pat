#include <stdint.h>
#include "stm32l053xx.h"



	int main(void)
	{

		struct Time_t watch;

		watch.segundo_unidad = 0x00;
		watch.segundo_decimal = 0x00;
		watch.minuto_unidad = 0x00;
		watch.minuto_decimal = 0x00;
		watch.hora_decimal = 0x00;

	    int8_t prev_segundo_unidad = watch.segundo_unidad;
	    int8_t prev_segundo_decimal = watch.segundo_decimal;
	    int8_t prev_minuto_unidad = watch.minuto_unidad;
	    int8_t prev_minuto_decimal = watch.minuto_decimal;
	    int8_t prev_hora_decimal = watch.hora_decimal;
	    int8_t prev_hora_unidad = watch.hora_unidad;




		//CONFIGURACION DE LOS PINES DEL PUERTO A

		RCC ->IOPENR |= 1 << 0; //HABILITAR PUERTO A RELOJ



		//CONFIGURACION DE PINES DEL PUERTO B
		RCC -> IOPENR |= 1 << 1; //HABILITAR  PUERTO B RELOJ

		// PINES CONFIGURADOS COMO SALIDA DEL PUERTO B, DISPLAY DE 7 SEGMENTOS MULTIPLEXADO

		GPIOB ->MODER |= 1<<0;  //PIN B0
		GPIOB ->MODER &= ~(1 << 1);

		GPIOB ->MODER |= 1<< 2;	//PIN B1
		GPIOB ->MODER &= ~(1 << 3);

		GPIOB ->MODER |= 1 << 4;	//PIN B2
		GPIOB ->MODER &= ~(1 << 5);

		GPIOB ->MODER |= 1 << 6;	//PIN B3
		GPIOB ->MODER &= ~(1 << 7);

		GPIOB ->MODER |= 1 << 8;	//PIN B4
		GPIOB ->MODER &= ~(1 << 9);

		GPIOB ->MODER |= 1 << 10;	//PIN B5
		GPIOB ->MODER &= ~(1 << 11);

		GPIOB ->MODER |= 1 << 12;	//PIN B6
		GPIOB ->MODER &= ~(1 << 13);

		GPIOB ->MODER |= 1 << 14;	//PIN B7
		GPIOB ->MODER &= ~(1 << 15);

		// PINES CONFIGURADOS COMO ENTRADA DEL PUERTO B DEL KPAD

		GPIOB ->MODER &= ~(1 << 16); // PIN PB8
		GPIOB ->MODER &= ~(1 << 17);

		GPIOB ->PUPDR |= 1<<16; //RESISTENCIA DE PULL-UP PB8
		GPIOB ->PUPDR &= ~(1 << 17);

		GPIOB ->MODER &= ~(1 << 18); //PIN PB9
		GPIOB ->MODER &= ~(1 << 19);

		GPIOB ->PUPDR |= 1<<18; //RESISTENCIA DE PULL-UP PB9
		GPIOB ->PUPDR &= ~(1 << 19);

		GPIOB ->MODER &= ~(1 << 20); //PIN PB10
		GPIOB ->MODER &= ~(1 << 21);

		GPIOB ->PUPDR |= 1<<20; //RESISTENCIA DE PULL-UP PB10
		GPIOB ->PUPDR &= ~(1 << 21);

		GPIOB ->MODER &= ~(1 << 22); // PB11
		GPIOB ->MODER &= ~(1 << 23);

		GPIOB ->PUPDR |= 1<<22; //RESISTENCIA DE PULL-UP PB11
		GPIOB ->PUPDR &= ~(1 << 23);

		// PINES CONFIGURADOS COMO SALIDA DEL PUERTO B DEL KPAD

		GPIOB ->MODER |= 1 << 24;	//PIN B12
		GPIOB ->MODER &= ~(1 << 25);

		GPIOB ->MODER |= 1 << 26;	//PIN B13
		GPIOB ->MODER &= ~(1 << 27);

		GPIOB ->MODER |= 1 << 28;	//PIN B14
		GPIOB ->MODER &= ~(1 << 29);

		GPIOB ->MODER |= 1 << 30;	//PIN B15
		GPIOB ->MODER &= ~(1 << 31);

	   //CONFIGURACIONES PARA EL PUERTO C, CONTROL DE DISPLAY MULTIPLEXADO

		RCC ->IOPENR |= 1 << 2; //HABILITAR PUERTO C RELOJ

		//PINES CONFIGURADOS COMO SALIDA DEL PUERTO C

		// PINES DE CONTROL DEL DISPLAY MULTIPLEXADO

		GPIOC ->MODER |= 1 << 10;  //PIN C5
		GPIOC ->MODER &= ~(1 << 11);

		GPIOC ->MODER |= 1 << 12;  //PIN C6
		GPIOC ->MODER &= ~(1 << 13);

		GPIOC ->MODER |= 1 << 16;  //PIN C8
		GPIOC ->MODER &= ~(1 << 17);

		GPIOC ->MODER |= 1 << 18;  //PIN C9
		GPIOC ->MODER &= ~(1 << 19);

		GPIOC ->MODER |= 1 <<20;//PIN C10
		GPIOC ->MODER &= ~(1 << 21);

		GPIOC ->MODER |= 1 <<22;//PIN C11
		GPIOC ->MODER &= ~(1 << 23);



		while(1)
		{
			//manejo de display
			switch(myfsm)
			{
			case 0:
			{
				//PARA EL DISPLAY 1 UNIDAD SEGUNDOS
				myfsm++;
				GPIOB ->BSRR |= 0XFF << 16; //LIMPIAR DISPLAY
				GPIOC ->BSRR |= 0X01 << 27; // LIMPIAR D5/C11
				GPIOC ->BSRR |= 0X01 << 5; // HABILITA D0/C5
				GPIOB ->BSRR |= decoder(watch.segundo_unidad) << 0; // MANDA A PINTAR DISPLAY 1

				break;

			}
			case 1:{
				//PARA EL DISPLAY 2 DECENA SEGUNDOS
				myfsm++;
				GPIOB ->BSRR |= 0XFF << 16; //LIMPIAR DISPLAY
				GPIOC ->BSRR |= 0X01 << 21; // LIMPIAR D0/C5
				GPIOC ->BSRR |= 0X01 << 6 ; // HABILITA D1/C6
				GPIOB ->BSRR |= decoder(watch.segundo_decimal) << 0; //MANDA A PINTAR DISPLAY 2
				break;

			}
			case 2:{
				//PARA EL DISPLAY 3 UNIDAD MINUTOS
				myfsm++;
				GPIOB ->BSRR |= 0XFF << 16; //LIMPIAR DISPLAY
				GPIOC ->BSRR |= 0X01 << 22; // LIMPIAR D1/C6
				GPIOC ->BSRR |= 0X01 << 8; // HABILITA D2/C8
				GPIOB ->BSRR |= decoder(watch.minuto_unidad) << 0; //MANDA A PINTAR DISPLAY 3

				break;
			}
			case 3:{
				//PARA EL DISPLAY 4 DECENA MINUTOS
				myfsm ++;
				GPIOB ->BSRR |= 0XFF << 16; //LIMPIAR DISPLAY
				GPIOC ->BSRR |= 0X01 << 24; // LIMPIAR D2/C8
				GPIOC ->BSRR |= 0X01 << 9; // HABILITA D3/C9
				GPIOB ->BSRR |= decoder(watch.minuto_decimal) << 0; //MANDA A PINTAR DISPLAY 4
				break;

			}
			case 4:{
				//PARA EL DISPLAY 5 UNIDAD HORAS
				myfsm ++;
				GPIOB ->BSRR |= 0XFF << 16; //LIMPIAR DISPLAY
				GPIOC ->BSRR |= 0X01 << 25; // LIMPIAR D3/C9
				GPIOC ->BSRR |= 0X01 << 10; // HABILITA D4/C10
				GPIOB ->BSRR |= decoder(watch.hora_unidad) << 0; //MANDA A PINTAR DISPLAY 4
				break;

					}

			case 5:{
				//PARA EL DISPLAY 6 DECENA HORAS
				myfsm = 0;
				GPIOB ->BSRR |= 0XFF << 16; //LIMPIAR DISPLAY
				GPIOC ->BSRR |= 0X01 << 26 ; // LIMPIAR D4/C10
				GPIOC ->BSRR |= 0X01 << 11; // HABILITA D5/C11
				GPIOB ->BSRR |= decoder(watch.hora_decimal) << 0; //MANDA A PINTAR DISPLAY 4

				break;

							}

			default:
			{
				//CASO NO TOMA EN CUENTA NINGUNO myfsm POR SEGURIDAD
				myfsm =0 ;
				break;
			}

			}
			//TERMINA MAQUINA DE ESTADOS FINITOS DISPLAY

			switch(myfsm1)
			{
			case 0:{
				//PARA LA COLUMAN 0
				myfsm1++;
				delay_ms(1);
				GPIOB->ODR |= 1<<15; // APAGANDO PB15
				GPIOB->ODR &= ~(1 << 12); //HABILITANDO PB12
				mascara = GPIOB->IDR & 0XF00; //CREA MASCARA DE 1111-0000-0000
				if (mascara == 0xE00){ //1110
					watch.segundo_unidad = 10; //LETRA A
				}
				if (mascara == 0xD00 ){ //1101
					watch.segundo_unidad = 11; //LETRA B
				}
				if (mascara == 0xB00){ //1011
					watch.segundo_unidad = 12; //LETRA C
				}
				if (mascara ==0X700){ //0111
					watch.segundo_unidad =13; //LETRA D
				}




				break;

			}
			case 1:{
				//PARA COLUMNA 1
				myfsm1++;
				GPIOB->ODR |= 1<<12; // APAGANDO PB12
				GPIOB->ODR &= ~(1 << 13); //HABILITANDO PB13
				mascara = GPIOB->IDR & 0XF00; //CREA MASCARA DE 1111-0000-0000
				if (mascara == 0xE00){ //1110
					watch.segundo_unidad = 3; //NUMERO 3
				}
				if (mascara == 0xD00 ){ //1101
					watch.segundo_unidad = 6; //NUMERO 6
				}
				if (mascara == 0xB00){ //1011
					watch.segundo_unidad = 9; // NUMERO 9
				}
				if (mascara ==0X700){ //0111
					watch.segundo_unidad =0; //NUM
				}


				break;
			}
			case 2:{
				//PARA COLUMNA 2
				myfsm1++;
				GPIOB->ODR |= 1<<13; // APAGANDO PB13
				GPIOB->ODR &= ~(1 << 14); //HABILITANDO PB14
				mascara = GPIOB->IDR & 0XF00; //CREA MASCARA DE 1111-0000-0000
				if (mascara == 0xE00){ //1110
					watch.segundo_unidad = 2; //NUMERO 2
				}
				if (mascara == 0xD00 ){ //1101
					watch.segundo_unidad = 5; //NUMERO 5
				}
				if (mascara == 0xB00){ //1011
					watch.segundo_unidad = 8; //NUMERO 8
				}
				if (mascara ==0X700){ //0111
					watch.segundo_unidad =0; //NUMERO 0
				}

				break;
			}

			case 3:{
				//PARA COLUMNA 3
				myfsm1 = 0;

				GPIOB->ODR |= 1<<14; // APAGANDO PB14
				GPIOB->ODR &= ~(1 << 15); //HABILITANDO PB15
				mascara = GPIOB->IDR & 0XF00; //CREA MASCARA DE 1111-0000-0000
				if (mascara == 0xE00){ //1110
					watch.segundo_unidad = 1; //NUMERO 1
				}
				if (mascara == 0xD00 ){ //1101
					watch.segundo_unidad = 4; //NUMERO 4
				}
				if (mascara == 0xB00){ //1011
					watch.segundo_unidad = 7; //NUMERO 7
				}
				if (mascara ==0X700){ //0111
					watch.segundo_unidad =prev_segundo_unidad; //NUMERO *
				}


				break;
			}
			default:{
				myfsm1 = 0;

				break;
			}



			} //TERMINA MAQUINA DE ESTADOS FINITOS KPAD




//TERMINA EL WHILE
}


	}




	void delay_ms(uint16_t n){

		uint16_t i;
		for(; n>0; n--)
			for(i=0; i<140; i++);
	}
	uint8_t decoder(uint8_t value_to_decode)
	{
		switch(value_to_decode)
		{
		case 0:
		{
			return(digit0);

		}
		case 1:{

			return(digit1);
		}
		case 2:{

			return(digit2);
		}
		case 3:{

			return(digit3);
		}
		case 4:{

			return(digit4);
		}
		case 5:{

			return(digit5);
		}

		case 6:{

			return(digit6);
		}

		case 7:{

			return(digit7);
		}

		case 8:{

			return(digit8);
		}
		case 9:{

			return(digit9);
		}
		case 10:{
			return(A);
		}
		case 11:{
			return(B);
		}
		case 12:{
			return(C);
		}
		case 13:{
			return(D);
		}


		default:
		{

		}
		return 0x00;


		}
	}
