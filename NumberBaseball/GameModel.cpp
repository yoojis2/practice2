// UART Example

#include "lpc17xx_dac.h"
#include "lpc17xx_uart.h"      
#include "lpc17xx_libcfg.h"
#include "lpc17xx_nvic.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"
#include "stdlib.h"
#include "time.h"

#define TEST_UART UART0  // UART0

#define LED_NUM     			8    // LED �� ����    
#define SEED_VALUE 		40  // srand���� ����� seed��
#define MATCH_VALUE 	20  // Timer������ Match value ��
#define ARRAY_SIZE 			3    // ���� �� �Է¹��� �迭 ������ 

/* ��¹��ڿ� �迭�� */
uint8_t menu1[] = "Hello NXP Semiconductors \n\r";
uint8_t menu2[] = "UART polling mode demo \n\r\t MCU LPC17xx - ARM Cortex-M3 \n\r\t UART0 - 9600bps \n\r";
uint8_t menu3[] = "UART demo terminated!";
uint8_t strStrike[] = " Strike   ";
uint8_t strBall[] = " Ball   ";
uint8_t lineClear[] = "\n\r";    
uint8_t winMsg[] = "You Win!!!!!\n\r";    
uint8_t timeOver[] = "Time Over!!\n\r";    
uint8_t gameOver[] = "Game Over!!\n\r";    
uint8_t roundMsg[] = "Round - ";   

uint8_t hintMsg[] = "HINT -";
uint8_t hintBracket2[] = "  [  ]  [  ]  ";    
uint8_t hintBracket1[] = "  [  ]   ";   
uint8_t blank[] = "  ";   
uint8_t alreadyUseHint[] = " You already used Hint!!!!";   

uint8_t answer[ARRAY_SIZE];  // ������ ����� �迭

uint8_t Round = 1;  // ���� ����

const unsigned long led_mask[] = { 1<<28, 1<<29, 1UL<<31, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6 };

int lightOn[8];

int hintFlag;

uint8_t strike = 0, ball = 0;


/////timer***********************
uint8_t g_ulFlags = 0;

TIM_TIMERCFG_Type TIM_ConfigStruct;
TIM_MATCHCFG_Type TIM_MatchConfigStruct ;

__IO FlagStatus exitflag;


void Delay(unsigned long d_t)
{
	long k;
	for(k=0; k<d_t; k++);
}


void sound(int i, int frequency, int delayValue)
{
	int temp = i;
	while(temp--)
	{
		DAC_UpdateValue(DAC, frequency);
		Delay(delayValue);
		DAC_UpdateValue(DAC, 0);
		Delay(delayValue);
	}
}

void nextLine()
{
	UART_Send(TEST_UART, lineClear, sizeof(lineClear), BLOCKING);
}


void printHint()
{
	int index = rand() % 3;

	UART_Send(TEST_UART, hintMsg, sizeof(hintMsg), BLOCKING);
	if(index == 0)
	{	
		UART_Send(TEST_UART, blank, 1, BLOCKING);
		UART_Send(TEST_UART, blank, 1, BLOCKING);
		UART_Send(TEST_UART, blank, 1, BLOCKING);
		UART_Send(TEST_UART, &answer[0], 1, BLOCKING);
		UART_Send(TEST_UART, hintBracket2, sizeof(hintBracket2), BLOCKING);
	}
	else if(index == 1)
	{	
		UART_Send(TEST_UART, hintBracket1, sizeof(hintBracket1), BLOCKING);
		UART_Send(TEST_UART, &answer[1], 1, BLOCKING);
		UART_Send(TEST_UART, hintBracket1, sizeof(hintBracket1), BLOCKING);
	}
	else
	{	
		UART_Send(TEST_UART, hintBracket2, sizeof(hintBracket2), BLOCKING);
		UART_Send(TEST_UART, &answer[2], 1, BLOCKING);
	}

}
void printGameOver()
{
	int i, delay = 50000;
	UART_Send(TEST_UART, gameOver, sizeof(gameOver), BLOCKING);

	for(i = 0; i < 6; i++)
	{
		// �� ��� ���� 
		GPIO_ClearValue(1, 0xB0000000);
		GPIO_ClearValue(2, 0x0000007C);
		Delay(1500000);
		GPIO_SetValue(1, 0xB0000000);
		GPIO_SetValue(2,  0x0000007C);
		Delay(1500000);
	}
	i = 100;
	while(i--)
	{
		DAC_UpdateValue(DAC, 0x200);
		Delay(delay);
		DAC_UpdateValue(DAC, 0);
		Delay(delay);

		delay += 1000;

	}
	// �� ��� ���� 
	GPIO_ClearValue(1, 0xB0000000);
	GPIO_ClearValue(2, 0x0000007C);
}



void printRound()
{
	UART_Send(TEST_UART, roundMsg, sizeof(roundMsg), BLOCKING);
	Round += 48;
	UART_Send(TEST_UART, &Round, 1, BLOCKING);
	Round -= 48;
	nextLine();
}


void print_menu(void)
{
	UART_Send(TEST_UART, menu1, sizeof(menu1), BLOCKING);
	UART_Send(TEST_UART, menu2, sizeof(menu2), BLOCKING);
}

// �̰����� ����Ǵ� �Լ�
void printWin()
{
	int i, j;
	// �� ��� ���� 
	GPIO_ClearValue(1, 0xB0000000);
	GPIO_ClearValue(2, 0x0000007C);

	// YOU WIN ���
	UART_Send(TEST_UART, winMsg, sizeof(winMsg), BLOCKING);

	for(i = 0; i < 8; i++)
	{
		if(i < 3)
		{
			GPIO_SetValue(1, led_mask[i]);
			Delay(1500000);
			GPIO_ClearValue(1, 0xB0000000);
		}
		else
		{
			GPIO_SetValue(2, led_mask[i]);
			Delay(1500000);
			GPIO_ClearValue(2, 0x0000007C);
		}
	}

	for(i = 7; i >= 0; i--)
	{
		if(i < 3)
		{
			GPIO_SetValue(1, led_mask[i]);
			Delay(1500000);
			GPIO_ClearValue(1, 0xB0000000);
		}
		else
		{
			GPIO_SetValue(2, led_mask[i]);
			Delay(1500000);
			GPIO_ClearValue(2, 0x0000007C);
		}
	}

	for(i = 0; i < 4; i++)
	{
		// �� ��� ���� 
		GPIO_ClearValue(1, 0xB0000000);
		GPIO_ClearValue(2, 0x0000007C);

		// 1 3 5 7 �� Ű��
		GPIO_SetValue(1, led_mask[0]);  GPIO_SetValue(1, led_mask[2]);  GPIO_SetValue(2, led_mask[4]);  GPIO_SetValue(2, led_mask[6]);
		Delay(1500000);
		// �� ��� ���� 
		GPIO_ClearValue(1, 0xB0000000);
		GPIO_ClearValue(2, 0x0000007C);
		Delay(1500000);
		GPIO_SetValue(1, led_mask[1]);  GPIO_SetValue(2, led_mask[3]);  GPIO_SetValue(2, led_mask[5]);  GPIO_SetValue(2, led_mask[7]);
		Delay(1500000);
	}
	// �� ��� ���� 
	GPIO_ClearValue(1, 0xB0000000);
	GPIO_ClearValue(2, 0x0000007C);


	j=3;
	while(j--){
		sound(70, 200, 45000);
		sound(60, 0, 22000);
	}


	sound(70, 200, 35000);
	sound(70, 0, 22000);
	sound(70, 200, 30000);
	sound(70, 200, 35000);
	sound(70, 0, 22000);
	sound(120, 200, 30000);
	sound(140, 200, 35000);
	sound(120, 200, 30000);
	sound(140, 200, 22000);


}

// ��ī��Ʈ ��� �� �׿����� �� ���ִ� �Լ�
void printBallCount()
{
	int i;
	// �� ��� ���� 
	GPIO_ClearValue(1, 0xB0000000);
	GPIO_ClearValue(2, 0x0000007C);

	// strike �� Ű��
	for(i = 0; i < strike; i++)
	{
		GPIO_SetValue(1, led_mask[i]);
	}

	// ball �� Ű��
	for(i = 7; i > 7 - ball; i--)
	{
		GPIO_SetValue(2, led_mask[i]);
	}

	strike += 48;
	ball += 48;
	UART_Send(TEST_UART, &strike, 1, BLOCKING);
	UART_Send(TEST_UART, strStrike, sizeof(strStrike), BLOCKING);

	UART_Send(TEST_UART, &ball, 1, BLOCKING);
	UART_Send(TEST_UART, strBall, sizeof(strBall), BLOCKING);
	nextLine();

}

// ���ھ߱� �¾Ҵ��� �Ǻ��ϴ� �Լ�
int isCorrect(uint8_t* input)
{
	int i, j;
	strike = 0, ball = 0;

	for(i = 0; i < ARRAY_SIZE; i++)
	{
		for(j = 0; j < ARRAY_SIZE; j++)
		{
			if(answer[i] == input[j])
			{
				if(i == j)
				{
					strike++;
					break;
				}
				else
				{
					ball++;
					break;
				}
			}
		}
	}

	// Win
	if(strike == 3)
		return 1;

	// Out
	if(strike == 0 && ball == 0)
		return 0;

	return -1;
}


// INTERRUPT HANDLER
void EINT0_IRQHandler(void)
{   				 	
	SC->EXTINT = 0x01;   // ���ͷ�Ʈ 0���� �ʱ�ȭ
	TIM_ResetCounter(TIM0);

	if(hintFlag == 0)
	{	
		printHint();
		nextLine();
		hintFlag = 1;  // ��Ʈ ���
	}
	else
	{
		UART_Send(TEST_UART, alreadyUseHint, sizeof(alreadyUseHint), BLOCKING);
		nextLine();
	}

}

// TIMER HANDLER
void TIMER0_IRQHandler(void)
{
	/* �������� */
	TIM_ClearIntPending(TIM0, 0);

	UART_Send(TEST_UART, timeOver, sizeof(timeOver), BLOCKING);

	exitflag = SET;

}

int main(void)
{

	int winFlag = 0;
	uint8_t randomNumber[ARRAY_SIZE];

	//sound
	PINSEL_CFG_Type DACPinCfg;

	// INT pinCfg
	PINSEL_CFG_Type INTPinCfg;
	int i;
	UART_CFG_Type UARTConfigStruct;
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;

	PINSEL_CFG_Type PinCfg;

	uint8_t idx, len;
	uint8_t input[ARRAY_SIZE];
	uint8_t temp;


	// ����ü�� ����
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_TICKVAL;
	TIM_ConfigStruct.PrescaleValue = 5000000;

	TIM_MatchConfigStruct.MatchChannel = 0;
	TIM_MatchConfigStruct.IntOnMatch = ENABLE;
	TIM_MatchConfigStruct.StopOnMatch = DISABLE;
	TIM_MatchConfigStruct.ResetOnMatch = ENABLE;
	TIM_MatchConfigStruct.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	TIM_MatchConfigStruct.MatchValue = MATCH_VALUE;


	TIM_Init(TIM0, TIM_TIMER_MODE, &TIM_ConfigStruct);
	TIM_ConfigMatch(TIM0, &TIM_MatchConfigStruct);

	NVIC_EnableIRQ(TIMER0_IRQn);  // �ܺ����ͷ�Ʈ Ÿ�̸ӷ� ����



	SystemInit();

	// seed�� �ʱ�ȭ
	srand(SEED_VALUE);

	// �����ѹ�����
	randomNumber[0] = rand() % 10;

	// �ι�° ���� �������� ���� ù��° ���ڿ� ���ٸ� �ٸ������� �ٽ� ��������
	randomNumber[1] = rand() % 10;
	while (randomNumber[0] == randomNumber[1])
		randomNumber[1] = rand() % 10;

	// ���������� ������ ���ڵ� ù��°�� �ι�°���ڿ� ���� �ٸ������� �ٽ� ����.
	randomNumber[2] = rand() % 10;
	while (randomNumber[0] == randomNumber[2] || randomNumber[1] == randomNumber[2])
		randomNumber[2] = rand() % 10;


	for(i = 0; i < ARRAY_SIZE; i++)
	{
		randomNumber[i] += 48;
		answer[i] = randomNumber[i];
	}


	// init System Control
	SC->EXTINT = 0x0;
	SC->EXTMODE = 0x0;
	SC->EXTPOLAR =0x0;

	// set System control
	SC->EXTMODE = 1;  // ����
	SC->EXTPOLAR = 0;  // �ϰ�

	// set pin config
	INTPinCfg.Portnum = 2;  
	INTPinCfg.Pinnum = 10;
	INTPinCfg.Funcnum = 1;
	INTPinCfg.Pinmode = 0;
	INTPinCfg.OpenDrain = 0;

	PINSEL_ConfigPin(&INTPinCfg);

	NVIC_EnableIRQ(EINT0_IRQn);

	//DAC pincfg
	DACPinCfg.Funcnum = 2;
	DACPinCfg.OpenDrain = 0;
	DACPinCfg.Pinmode = 0;
	DACPinCfg.Pinnum = 26;
	DACPinCfg.Portnum = 0;

	PINSEL_ConfigPin(&DACPinCfg);

	DAC_Init(DAC);


	/* LED �ʱ�ȭ */
	GPIO_SetDir(1, 0xB0000000, 1);
	GPIO_SetDir(2, 0x0000007C, 1);
	GPIO_ClearValue(1, 0xB0000000);
	GPIO_ClearValue(2, 0x0000007C);

	PinCfg.Funcnum = 1;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Pinnum = 2;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);

	PinCfg.Pinnum = 3;
	PINSEL_ConfigPin(&PinCfg);

	UART_ConfigStructInit(&UARTConfigStruct);// Init�� ���൵ �Լ����ο��� ���� �� ����

	UART_Init(TEST_UART, &UARTConfigStruct);

	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);  // Init�� ���൵ �Լ����ο��� ���� �� ����

	UART_FIFOConfig(TEST_UART, &UARTFIFOConfigStruct);

	UART_TxCmd(TEST_UART, ENABLE);


	print_menu();

	exitflag = RESET;

	for(i = 0; i < 8; i++)
	{    lightOn[i] = 0; }

	idx = 0;

	//Ÿ�̸Ӱ���
	TIM_Cmd(TIM0, ENABLE);

	printRound();

	sound(70, 200, 45000);
	sound(70, 200, 35000);
	sound(70, 200, 30000);
	sound(140, 200, 22000);
	sound(70, 0, 22000);
	sound(60, 200, 30000);
	sound(140, 200, 22000);

	while (exitflag == RESET)
	{


		len = 0;
		while (len == 0 && exitflag == RESET)
		{

			len = UART_Receive(TEST_UART, &temp, sizeof(temp), NONE_BLOCKING);

		}


		if (temp == 27)
		{
			// ����
			UART_Send(TEST_UART, menu3, sizeof(menu3), BLOCKING);
			exitflag = SET;
		}

		else
		{

			UART_Send(TEST_UART, &temp, 1, BLOCKING);

			input[idx] = temp;
			idx++;
		}

		if(idx ==  ARRAY_SIZE && exitflag == RESET)
		{   

			isCorrect(input);

			TIM_ResetCounter(TIM0);
			nextLine();
			printBallCount();  // ��ī��Ʈ ��� �� LED ����


			if( isCorrect(input) ==1)
			{
				// �̰�����
				GPIO_SetValue(1, led_mask[0]);
				printWin();  // WIn ��� �� LED ��������
				winFlag = 1;
				exitflag = SET;

			}

			if(Round == 9)
			{
				exitflag = SET;
				break;
			}

			if( isCorrect(input) !=1)  // Ʋ������
			{ 
				Round++;
				printRound();
			}

			idx = 0;

		}
	}

	if(winFlag == 0)
	{ 
		printGameOver();  // ������ ����ϰ� �� ���
	}
	while (UART_CheckBusy(TEST_UART) == SET);

	UART_DeInit(TEST_UART);

	while(1);
	return 1;
}