#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover raw-file");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fclose(file);
        printf("Can't open file");
        return 1;
    }
    FILE *jpg;
    const int BLOCK_SIZE = 512;
    BYTE buffer[BLOCK_SIZE];
    int jpg_count = 0;
    char *filename = malloc(20);
    int start_file = 0;
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (start_file == 1)
            {
                fclose(jpg);
                sprintf(filename, "%03i.jpg", jpg_count);
                jpg = fopen(filename, "w");
                jpg_count++;
            }
            if (start_file == 0)
            {
                sprintf(filename, "%03i.jpg", jpg_count);
                jpg = fopen(filename, "w");
                jpg_count++;
                start_file = 1;
            }
        }
        if (start_file == 1)
        {
            fwrite(buffer, 1, BLOCK_SIZE, jpg);
        }
    }
    fclose(jpg);
    fclose(file);
    free(filename);
}