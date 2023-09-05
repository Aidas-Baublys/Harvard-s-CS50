#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./reverse infile outfile\n");
        return 1;
    }

    char *infile = argv[1];
    FILE *in = fopen(infile, "r");
    if (in == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    WAVHEADER header;
    fread(&header, sizeof(header), 1, in);
    if (check_format(header) != 0)
    {
        printf("%s is not a wav file.\n", infile);
        return 3;
    }

    char *outfile = argv[2];
    FILE *out = fopen(outfile, "w");
    if (out == NULL)
    {
        fclose(in);
        printf("Could not create %s.\n", outfile);
        return 4;
    }

    fwrite(&header, sizeof(WAVHEADER), 1, out);
    int block_size = get_block_size(header);

    if (fseek(in, block_size, SEEK_END))
    {
        return 1;
    }

    BYTE buffer[block_size];
    while (ftell(in) - block_size > sizeof(header))
    {
        if (fseek(in, -2 * block_size, SEEK_CUR))
        {
            return 1;
        }
        fread(&buffer, block_size, 1, in);
        fwrite(&buffer, block_size, 1, out);
    }

    fclose(in);
    fclose(out);
}

int check_format(WAVHEADER header)
{
    if (header.format[0] == 'W')
    {
        return 0;
    }
    return 1;
}

int get_block_size(WAVHEADER header)
{
    return header.bitsPerSample * header.numChannels / 8;
}