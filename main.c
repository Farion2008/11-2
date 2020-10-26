//Дан массив строк. Удалить из массива первую и последнюю строку по алфавиту.
//Полученный массив уплотнить.Память под массив строк отводить динамически.Использовать указатели на функции.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
char** massiv(int n, int m)//функция для динамического выделения памяти под массив строк
{
	char** text;
	text = (char**)calloc(n, sizeof(char*));
	if (NULL == text)
	{
		printf("Не удалось выделить память\n");
		exit(1);
	}
	for (int i = 0; i < n; i++)
	{
		text[i] = (char*)calloc(m, sizeof(char));
		if (NULL == text[i])
		{
			printf("Не удалось выделить память\n");
			exit(1);
		}
	}
	for (int i = 0; i < n; i++)
	{
		printf("Введите %d строку\n", i + 1);
		fgets(text[i], m, stdin);
		for (int j = 0; text[i][j] != '\0'; j++)//сразу удалим из строк '\n' для красоты вывода
		{
			if (text[i][j] == '\n')
			{
				text[i][j] = '\0';
			}
		}
	}
	return text;
}
void free_m(char** text, int n)//функция освобождения выделенной памяти
{
	for (int i = 0; i < n; i++)
	{
		free(text[i]);
	}
	free(text);
}
int perv_alf(char** text, int n, int m)//удаляем первую по алфавиту строку и уплотняем массив
{
	int i, i1=0;
	char* perv=text[0];
	for (i = 1; i < n; i++)
	{
		if (strcmp(perv, text[i]) > 0)
		{
			perv = text[i];
			i1 = i;
		}
	}
	for (i = i1; i < n - 1; i++)
	{
		strcpy_s(text[i], m, text[i + 1]);
	}
	free(text[i]);
	n--;
	return n;
}
int posl_alf(char** text, int n, int m)//удаляем последнюю по алфавиту строку и уплотняем массив
{
	int i, i1=0;
	char* posl = text[0];
	for (i = 1; i < n; i++)
	{
		if (strcmp(posl, text[i]) < 0)
		{
			posl = text[i];
			i1 = i;
		}
	}
	for (i = i1; i < n - 1; i++)
	{
		strcpy_s(text[i], m, text[i + 1]);
	}
	free(text[i]);
	n--;
	return n;
}
void vivod(char** text, int n)//функция вывода на консоль полученного массива
{
	printf("Полученный массив из %d строк.\n", n);
	for (int i = 0; i < n; i++)
	{
		puts(text[i]);
	}
}
int (*vibor(char** text, int n, int m))(char** text, int n, int m)//функция для выбора что необходимо сделать с текстом удалить первую по алфавиту строку либо последнюю
{
	int vibor;
	int (*deistv_s[])(char** text, int n, int m) = { perv_alf, posl_alf };//создаём массив указателей на функции
	printf("Выберите:\n1(для удаления первой по алфавиту строки)\n2(для удаления последней по алфавиту строки)\n3 для выхода и выведения полученного массива:");
	scanf_s("%d", &vibor);
	if (vibor > 0 && vibor < 3)
	{
		return deistv_s[vibor - 1];
	}
	else
	{
		return NULL;
	}
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n, m;
	printf("Укажите сколько строк вы хотите ввести:");
	scanf_s("%d", &n);
	printf("Укажите сколько символов в каждой строке:");
	scanf_s("%d", &m);
	getchar();
	char** text = massiv(n, m);
	int (*deistv)(char** text, int n, int m);
	while (1)
	{
		deistv = vibor(text, n, m);
		if (deistv == NULL)
		{
			break;
		}
		n = deistv(text, n, m);
	}
	vivod(text, n);
	free_m(text, n);
	return 0;
}