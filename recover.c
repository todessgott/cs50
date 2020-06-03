#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //open the card.raw file and check for NULL
    FILE *card = fopen(argv[1], "r");

    //read in 512 bytes from card.raw until you reach EOF
    typedef uint8_t BYTE;
    int file_counter = 0;
    FILE *new_jpg;
    BYTE buffer[512];
    while (fread(buffer, 1, 512, card) != 0x00)
    {
        //if we find the header pattern of Bytes
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //found the first jpg
            if (file_counter == 0)
            {
                char filename[8];
                sprintf(filename, "%03i.jpg", file_counter);
                file_counter++;
                 //open new file i.e new_jpg
                new_jpg = fopen(filename, "w");
                //buffer into new_jpg
                fwrite(buffer, 1, 512, new_jpg);
            }
            else
            {
                //close the previous file
                fclose(new_jpg);

                //write in new file
                char filename[8];
                sprintf(filename, "%03i.jpg", file_counter);
                file_counter++;
                //open new file i.e new_jpg
                new_jpg = fopen(filename, "w");
                //buffer into new_jpg
                fwrite(buffer, 1, 512, new_jpg);
            }
        }
        else
        {
            //found the first jpg
            if (file_counter > 0)
            {
                //continue to write on bytes
                fwrite(buffer, 1, 512, new_jpg);
            }
        }
    }
    //close all files and free the memory used
    fclose(new_jpg);
    fclose(card);
}