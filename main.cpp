#include <iostream>
#include <chrono>

void print(int (*arr)[4])
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j) 
		{
			std::cout << (*arr)[i * 4 + j] << ' ';
		}
		std::cout << std::endl;
	}
}

void initArrray(int (*array)[4])
{
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			(*array)[i * 4 + j] = i * 4 + j + 1;
		}
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "russian");
	const long int loopCount = 1e+8;


	std::chrono::steady_clock timer;
	long int i = 0;
	auto start = timer.now();
	for (i; i < loopCount; ++i);
	auto end = timer.now();
	std::cout << "¬рем€ пустого цикла: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << '\n';
	i = 0;
	start = timer.now();
	for (i; i < loopCount; ++i)
	{
		__asm
		{
			add eax, ebx
			add eax, ebx
			add eax, ebx
			add eax, ebx
			add eax, ebx
			add eax, ebx
			add eax, ebx
			add eax, ebx
			add eax, ebx
			add eax, ebx
		}
	}
	end = timer.now();
	std::cout << "¬реме€ цикла с регистровой адрессацией: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << '\n';
	i = 0;
	start = timer.now();
	for (i; i < loopCount; ++i)
	{
		__asm
		{
			add eax, [ebx]
			add eax, [ebx]
			add eax, [ebx]
			add eax, [ebx]
			add eax, [ebx]
			add eax, [ebx]
			add eax, [ebx]
			add eax, [ebx]
			add eax, [ebx]
			add eax, [ebx]
		}
	}
	end = timer.now();
	std::cout << "¬реме€ цикла с косвенно-регистровой адрессацией: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << '\n';

	__asm {
		mov esi, 4
	}

	i = 0;
	start = timer.now();
	for (i; i < loopCount; ++i)
	{
		__asm
		{
			add eax, [ebx + 2 * esi + 1]
			add eax, [ebx + 2 * esi + 1]
			add eax, [ebx + 2 * esi + 1]
			add eax, [ebx + 2 * esi + 1]
			add eax, [ebx + 2 * esi + 1]
			add eax, [ebx + 2 * esi + 1]
			add eax, [ebx + 2 * esi + 1]
			add eax, [ebx + 2 * esi + 1]
			add eax, [ebx + 2 * esi + 1]
			add eax, [ebx + 2 * esi + 1]
		}
	}
	end = timer.now();
	std::cout << "¬реме€ цикла с базово-индескной адрессацией со смещением: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << '\n';

	i = 0;
	start = timer.now();
	for (i; i < loopCount; ++i)
	{
		__asm
		{
			add [ebx], eax
			add [ebx], eax
			add [ebx], eax
			add [ebx], eax
			add [ebx], eax
			add [ebx], eax
			add [ebx], eax
			add [ebx], eax
			add [ebx], eax
			add [ebx], eax
		}
	}
	end = timer.now();
	std::cout << "¬реме€ цикла с косвенно-регистровой адрессацией с записью в пам€ть: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << '\n';
	const int arraySide = 4;
	int array[arraySide][arraySide]; // array in stack (arraySide * arraySide * 4 byte in a line)
	initArrray(array);
	__asm
	{
		lea esi, array
		add esi, 16
		mov ecx, 2
		mov eax, 0  // <-- number to fill
		loop_:
			mov edi, 0
			fillLine:
				mov [esi], eax
				add esi, 4
				inc edi
				cmp edi, 4
			jl fillLine

			add esi, 16
		loop loop_
	}
	print(array);
	std::cout << std::endl;
	initArrray(array);
	__asm
	{
		cld
		mov ebx, 2
		lea edi, [array + 16]
		loop2_:
		mov eax, 0
			mov ecx, 4
			rep stosd
			add edi, 16
			dec ebx
			cmp ebx, 0
		jne loop2_
	}

	print(array);
	return 0;
}