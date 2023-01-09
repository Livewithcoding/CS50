#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while(n < 1 || n > 8);

    // for each row
    for(int i = 0; i < n; i++)
    {
        // 空格数等于行数减去当前行数。k 代表空格
        for(int k = n - i; k > 1;k--)
        {
            printf(" ");
        }

        for(int l = 0; l <= i; l++)
        {
            printf("#");
        }

        // 中间的空格
        printf("  ");

        // 右侧金字塔
        for(int r = 0; r <= i; r++)
        {
            printf("#");
        }
        printf("\n");
    }

}