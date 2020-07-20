/*
käytettyjä lähteitä:
https://www.tutorialspoint.com/c_standard_library/c_function_fgetc.htm
https://www.tutorialspoint.com/c_standard_library/c_function_fwrite.htm
https://stackoverflow.com/questions/9180006/how-to-use-fread-and-fwrite-functions-to-read-and-write-binary-files
https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm
*/

#include "stdlib.h"
#include "stdio.h"

int main(int argc, char const *argv[])
{
    //tarkastettaan onko käyttäjä syöttänyt argumenteja
    if (argc < 2)
    {
        fprintf(stderr, "wunzip: file1a [file2 ...]\n");
        exit(1);
    }
    //alustettaan muuttujia
    FILE *tiedosto;
    int count, character;
    //mennään kaikki tiedostot joita argumentissa on annettu läpi
    for (size_t i = 1; i < argc; i++)
    {
        //yritettään avata tiedostoa
        tiedosto = fopen(argv[1], "rb");
        if (tiedosto == NULL)
        {
            fprintf(stderr, "wunzip: cannot open file\n");
            exit(1);
        }
        //aletaan lukemaan tiedostoa luku sitten kirjain tyylillä
        while (fread(&count, sizeof(int), 1, tiedosto) != 0)
        {
            if ((fread(&character, sizeof(char), 1, tiedosto)) == 0) //sanity check
            {
                fprintf(stderr, "wunzip: error reading file\n");
                exit(1);
            }
            for (size_t i = 0; i < count; i++) //toistettaan luettu kirjain luvun verran
            {
                printf("%c", character);
            }
        }
        fclose(tiedosto);
    }
    printf("\n");

    return 0;
}
