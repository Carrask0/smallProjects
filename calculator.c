/*
    JORGE CARRASCO POLLO - 2021
 */
#include <stdio.h>

#define LIM 15 //WHITESPACES IN MARGIN
#define DIM 20 //PROVISIONAL ARRAY DIMENSION

//RETURNS TWO VALUES ASKED
int * get_values(char uno[], char dos[]);

//SPLIT A NUMBER IN DIGITS......ARRAY IS BACKWARDS
int * split(int num);

//RETURNS NUMBER OF DIGITS OF A GIVEN NUMBER
int get_digits(int num);

//PRINTS A LINE
void line(void);

//SAFECODE NEGATIVE INPUT
int min(int num);

//VISUALLY ADDS TWO NUMBERS
void addition(int num1, int num2);

//VISUALLY SUBTRACTS TWO NUMBERS
void subtraction(int num1, int num2);

//VISUALLY MULTIPLIES TWO NUMBERS
void multiplication(int num1, int num2);

//void division(int dividendo, int divisor);

/*-------------------------------------------------------------*/

int main()
{
    int opt;
    int *p;
    do
    {
        printf("----------------------------\n");
        printf("            MENU\n");
        printf("----------------------------\n");
        printf("1.- Add\n");
        printf("2.- Subtract\n");
        printf("3.- Multiply\n");
        //printf("4.- División\n");
        printf("0.- EXIT\n");
        printf("Introduce option: ");
        scanf("%d", &opt);
    }
    while (opt != 0 && opt != 1 && opt != 2 && opt != 3);

    switch(opt)
    {
        case 0:
            printf("EXIT...");
            return 0;
        case 1:
            p = get_values("first addend", "second addend");
            addition(*p, *(p + 1));
            break;
        case 2:
            p = get_values("minuend", "subtrahend");
            subtraction(*p, *(p + 1));
            break;
        case 3:
            p = get_values("multiplicand", "multiplier");
            multiplication(*p, *(p + 1));
            break;
            /*
        case 4:
            p = get_values("dividendo", "divisor");
            division(*p, *(p + 1));
            break
             */
        default:
            break;
    }
}

int get_digits(int num)
{
    if (num < 0)
    {
        num *= -1;
    }
    int digits = 1;
    while (num > 10)
    {
        digits ++;
        num /= 10;
    }
    return digits;
}

int * get_values(char one[], char two[])
{
    static int r[2];
    printf("Introduce the %s: ", one);
    scanf("%d", &r[0]);
    printf("Introduce the %s: ", two);
    scanf("%d", &r[1]);
    return r;
}

int * split(int num)
{
    int digits = get_digits(num);
    static int s[20];
    for (int i = 0; i < digits; i++)
    {
        s[i] = num % 10;
        num /= 10;
    }
    return s;
}

void line(void)
{
    for (int i = 1; i <= LIM; i++)
    {
        printf("-");
    }
    puts("");
}

int min(int num)
{
    int min = 0;
    if (num < 0)
    {
        min = 1;
    }
    return min;
}

void addition(int num1, int num2)
{
    int result;
    int digits [3];

    result = num1 + num2;
    //printf("%d + %d = %d\n", num1, num2, num1 + num2);
    digits[0] = get_digits(num1);
    digits[1] = get_digits(num2);
    digits[2] = get_digits(result);

    //WHITESPACES FIRST ADDEND
    for (int i = 1; i <= LIM - digits[0] - min(num1); i++)
    {
        printf(" ");
    }
    printf("%d\n", num1);

    //WHITESPACES SECOND ADDEND
    for (int i = 1; i <= LIM - digits[1] - 2 - min(num2); i++)
    {
        printf(" ");
    }
    printf("+ %d\n", num2);

    line();

    //WHITESPACES RESULT
    for (int i = 1; i <= LIM - digits[2] - min(result); i++)
    {
        printf(" ");
    }
    printf("%d", result);
}

void subtraction(int num1, int num2)
{
    int result;
    int digits [3];

    result = num1 - num2;
    //printf("%d + %d = %d\n", num1, num2, num1 + num2);
    digits[0] = get_digits(num1);
    digits[1] = get_digits(num2);
    digits[2] = get_digits(result);

    //WHITESPACES MINUEND
    for (int i = 1; i <= LIM - digits[0] - min(num1); i++)
    {
        printf(" ");
    }
    printf("%d\n", num1);

    //WHITESPACES SUBTRAHEND
    for (int i = 1; i <= LIM - digits[1] - 2 - min(num2); i++)
    {
        printf(" ");
    }
    printf("- %d\n", num2);

    line();

    //WHITESPACES RESULT
    for (int i = 1; i <= LIM - digits[2] - min(result); i++)
    {
        printf(" ");
    }

    printf("%d", result);

}

void multiplication(int num1, int num2)
{
    int result;
    int digits [3];
    int *s;
    int figures[DIM];
    int ind_fact;

    result = num1 * num2;

    digits[0] = get_digits(num1);
    digits[1] = get_digits(num2);
    digits[2] = get_digits(result);

    //WHITESPACES FIRST FACTOR
    for (int i = 1; i <= LIM - digits[0] - min(num1); i++)
    {
        printf(" ");
    }
    printf("%d\n", num1);

    //WHITESPACES SECOND FACTOR
    for (int i = 1; i <= LIM - digits[1] - 2 - min(num2); i++)
    {
        printf(" ");
    }
    printf("x %d\n", num2);

    line();

    //DIVIDE MULTIPLIER IN DIGITS
    s = split(num2);
    for (int i = 0; i < digits[1]; i++)
    {
        figures[digits[1] - i - 1] = *(s + i);
    }

    //WHITESPACES ONE-DIGIT FACTORS
    for (int i = 0; i < digits[1]; i++)
    {
        ind_fact = figures[digits[1] - i - 1] * num1;
        for (int j = 0; j <= LIM - get_digits(ind_fact) - min(ind_fact) - i - 1; j++)
        {
            printf(" ");
        }
        printf("%d\n", ind_fact);
    }

    line();

    //WHITESPACES RESULT
    for (int i = 1; i <= LIM - digits[2] - min(result); i++)
    {
        printf(" ");
    }
    printf("%d", result);
}

/*
void division(int dividendo, int divisor)
{
    int cociente = dividendo / divisor;
    int whitespaces = LIM - get_digits(dividendo) - min(dividendo) - get_digits(divisor) - min(divisor) - 2;
    int dividendo_nums [DIM];
    int *s;
    int ind_div, ind_res;

    printf(" %d", dividendo);
    //ESPACIOS CAJA
    for (int i = 0; i < LIM - whitespaces; i++)
    {
        printf(" ");
    }
    printf("| %d\n", divisor);

    //SUELO CAJA
    for (int i = 0; i < 1 + get_digits(dividendo) + (LIM - whitespaces); i++)
    {
        printf(" ");
    }
    printf("+");
    for (int i = 0; i < LIM - whitespaces; i++)
    {
        printf("-");
    }
    puts("");

    //DESCOMPONER EL DIVIDENDO EN CIFRAS
    s = split(dividendo);
    for (int i = 0; i < get_digits(dividendo); i++)
    {
        dividendo_nums[get_digits(dividendo) - i - 1] = *(s + i);
    }
    //PRIMERA LÍNEA


}
*/
