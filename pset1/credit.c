#include <cs50.h>
#include <stdio.h>

// ex card: 4003600000000014

int main(void)
{
    // 接收卡号
    long num;
    do
    {
        num = get_long("Card Number: ");
    }
    while( num <= 0);

    // 计算卡号的位数
    int digits = 0;
    long n = num;
    while( n > 0)
    {
        n /= 10;
        digits++;
    }

    int sum = 0;
    int digit;
    int i = 0;
    n = num;


    // 计算总和 by Luhn’s Algorithm
    while( n > 0)
    {
        digit = n % 10;

        if (i % 2 == 0)
        {
            sum += digit;
        }
        else
        {
            int doubled = digit * 2;
            sum += doubled % 10 + doubled /10;
        }
        n /=10;
        i++;
    }


    while (num >= 100)
    {
        num /= 10;
    }


    if (sum % 10 == 0)
    {
        if (digits == 15 && (num == 34 || num == 37))
        {
            printf("AMEX\n");
        }
        else if (digits == 16 && (num >= 51 && num <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if((digits == 16 || digits == 13) && (num >= 40 && num <=49))
        {
            printf("VISA\n");
        }
        // else if(digits == 16 && num == 35 )
        // {
        //     printf("JCB\n");
        // }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }


}

