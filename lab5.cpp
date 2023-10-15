#include <iostream>
#include <bitset>


const long long OP = 0xDEADC0DEBADDC0DE;
long long RES = 0;

void long_neg(long long, long long&)
{
	/***************************************
	* ebp + 16	| ������ ����������		|
	* ebp + 12	| ������ ������� 32 bit	|
	* ebp + 8	| ������ ������� 32 bit	|
	* ebp + 4	| ������� CS ���. ����.	|
	* ebp		| ������� IP ���. ����.	|
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
	* esi - ������ ��������
	* ebx - ������ ����������
	****************************************/

	_asm
	{
		mov edi, [esi + 4]	// <-- �������� �������
		mov edx, [esi]		// <-- ������� �������


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
	printf("Stack\n�� ����� �����: %lld\n", c);
	long_neg(c, c);
	printf("����� ����� �����: %lld\n", c);


	c = 0xBBBBBBBBBBBBBBBB;


	printf("\nRegister\n�� ����� �����: %lld\n", c);
	_asm
	{
		lea esi, c
		lea ebx, c
	}
	long_reg_neg();
	printf("����� ����� �����: %lld\n", c);

	printf("\nGlobal\n�� ����� �����: %lld\n", OP);
	long_global_neg();
	printf("����� ����� �����: %lld\n", RES);


	c = 0x8000000000000000;

	printf("\nStack\n�� ����� �����: %lld\n", c);
	long_neg(c, c);
	printf("����� ����� �����: %lld\n", c);

	return 0;
}