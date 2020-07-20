/*
käytettyjä lähteitä:
https://www.tutorialspoint.com/c_standard_library/c_function_fgetc.htm
https://www.tutorialspoint.com/c_standard_library/c_function_fwrite.htm
https://stackoverflow.com/questions/9180006/how-to-use-fread-and-fwrite-functions-to-read-and-write-binary-files
*/
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char const *argv[])
{
    //tarkastettaan onko käyttäjä syöttänyt argumenteja
    if (argc < 2)
    {
        fprintf(stderr, "wzip: file1 [file2 ...]\n");
        exit(1);
    }
    //alustettaan muuttujia
    FILE *tiedosto;
    int current, tracked;
    //mennään kaikki tiedostot joita argumentissa on annettu läpi
    for (size_t i = 1; i < argc; i++)
    {
        //yritettään avata tiedostoa
        tiedosto = fopen(argv[1], "r");
        if (tiedosto == NULL)
        {
            fprintf(stderr, "wzip: cannot open file\n");
            exit(1);
        }
        int count = 0;
        //aletaan lukemaan tiedostoa kirjain kerrallaan
        while ((current = fgetc(tiedosto)) != EOF)
        {
            if (tracked == current) //jos sama tulee uudelleen
            {
                count++; //lisätään monta niitä on
            }
            else if (count == 0) //jos ei seurata mitään kirjaita
            {
                tracked = current; //asetetaan luettu kirjain seurattavaksi
                count++;
            }
            else //jos tänne päädytään niin vaihtui kirjain
            {
                //kirjoitetaan mitä oli ensin 4 bytellä monta sit 1 bytellä mikä
                fwrite(&count, sizeof(int), 1, stdout);
                fwrite(&tracked, sizeof(char), 1, stdout);
                count = 1;
                tracked = current;
            }
        }
        fclose(tiedosto);
    }

    return 0;
}
