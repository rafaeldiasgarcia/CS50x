#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("Could not open file %s.\n", argv[1]);
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE];
    int file_counter = 0;
    FILE *output_jpeg_file = NULL;
    char filename[8];

    while (fread(buffer, 1, BLOCK_SIZE, input_file) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (output_jpeg_file != NULL)
            {
                fclose(output_jpeg_file);
            }

            sprintf(filename, "%03i.jpg", file_counter);
            output_jpeg_file = fopen(filename, "w");
            if (output_jpeg_file == NULL)
            {
                fclose(input_file);
                printf("Could not create output file %s.\n", filename);
                return 1;
            }
            file_counter++;
        }

        if (output_jpeg_file != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, output_jpeg_file);
        }
    }

    if (output_jpeg_file != NULL)
    {
        fclose(output_jpeg_file);
    }
    fclose(input_file);

    return 0;
}
