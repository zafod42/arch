#include <iostream>
#include <bitset>


const long long OP = 0xDEADC0DEBADDC0DE;
long long RES = 0;

void long_neg(long long, long long&)
{
	/***************************************
	* ebp + 16	| адресс результата		|
	* ebp + 12	| первые старшие 32 bit	|
	* ebp + 8	| первые младшие 32 bit	|
	* ebp + 4	| регистр CS выз. прог.	|
	* ebp		| регистр IP выз. прог.	|
	****************************************/

	__asm
	{
		mov edi, [ebp + 12]
		mov edx, [ebp + 8]
		mov ebx, [ebp + 16]

		not edi
		not edx
		add edx, 1
		adc edi, 0

		mov [ebx], edx
		mov [ebx + 4], edi
	}

}

void long_reg_neg()
{
	/***************************************
	* esi - адресс операнда
	* ebx - адресс результата
	****************************************/

	_asm
	{
		mov edi, [esi + 4]	// <-- страршие разряды
		mov edx, [esi]		// <-- младшие разряды


		not edi
		not edx
		add edx, 1
		adc edi, 0
			
		mov [ebx], edx
		mov [ebx + 4], edi
	}
}

void long_global_neg()
{
	_asm
	{
		lea esi, OP
		lea ebx, RES

		mov edi, [esi + 4]
		mov edx, [esi]

		not edi
		not edx
		add edx, 1
		adc edi, 0

		mov[ebx], edx
		mov[ebx + 4], edi
	}
}

int main()
{
	setlocale(LC_ALL, "rus");

	long long c = 0xAAAAAAAAAAAAAAAA;
	printf("Stack\nДо смены знака: %lld\n", c);
	long_neg(c, c);
	printf("После смены знака: %lld\n", c);


	c = 0xBBBBBBBBBBBBBBBB;


	printf("\nRegister\nДо смены знака: %lld\n", c);
	_asm
	{
		lea esi, c
		lea ebx, c
	}
	long_reg_neg();
	printf("После смены знака: %lld\n", c);

	printf("\nGlobal\nДо смены знака: %lld\n", OP);
	long_global_neg();
	printf("После смены знака: %lld\n", RES);


	c = 0x8000000000000000;

	printf("\nStack\nДо смены знака: %lld\n", c);
	long_neg(c, c);
	printf("После смены знака: %lld\n", c);

	return 0;
}