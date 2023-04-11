#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // 非2个参数 报错
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        // 在此处终止程序 ->> return 1;
        return 1;
    }

    // 非26个字符 报错
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // 遍历26个字符是否为字母
    string key = argv[1];
    for (int i = 0; i < strlen(key); i++)
    {
        //检查是否为字母
        if (!isalpha(key[i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }

    // 检查重复项
    for (int i = 0; i < strlen(key); i++)
    {
        for (int j = i + 1; j < strlen(key); j++)
        {
            if (toupper(key[i]) == toupper(key[j]))
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }

    // 获得明文
    string plaintext = get_string("Plaintext: ");

    // 转换为大写
    for (int i = 0; i < strlen(key); i++)
    {
        if (islower(key[i]))
        {
            key[i] = key[i] - 32;
        }
    }

    // 打印密文
    printf("ciphertext:");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isupper(plaintext[i]))
        {
            int letter = plaintext[i] - 'A'; // 65
            printf("%c", key[letter]);
        }
        else if (islower(plaintext[i]))
        {
            int letter = plaintext[i] - 'a'; // 97
            printf("%c", key[letter] + 32);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}