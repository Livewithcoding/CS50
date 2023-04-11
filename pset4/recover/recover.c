#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "Invalid file\n");
        return 1;
    }

    int jpg_counter = 0;
    BYTE buffer[512];
    char filename[8];
    FILE *img;

    while (fread(&buffer, sizeof(buffer), 1, file))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (jpg_counter == 0)
            {
                sprintf(filename, "%03i.jpg", jpg_counter);
                img = fopen(filename, "w");
                fwrite(&buffer, sizeof(buffer), 1, img);

                jpg_counter++;
            }

            else if (jpg_counter > 0)
            {
                fclose(img);

                sprintf(filename, "%03i.jpg", jpg_counter);
                img = fopen(filename, "w");
                fwrite(&buffer, sizeof(buffer), 1, img);

                jpg_counter++;
            }
        }
        else if (jpg_counter > 0)
        {
            fwrite(&buffer, sizeof(buffer), 1, img);
        }
    }

    fclose(file);
    fclose(img);
}