/*
käytettyjä lähteitä:
https://man7.org/linux/man-pages/man3/getline.3.html
*/ 

#define _GNU_SOURCE
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char const *argv[])
{
    //määritellään tarvittavia muuttujia
    FILE *tiedosto;
    char *rivi = NULL;
    size_t len = 0;
    ssize_t nread;
    

    //Tarkistetaan onko syötetty argumenteja
    if (argc < 2) 
    {
        exit(0);
    }

    //käydään kaikki argumentti tiedostot läpi
    for (size_t i = 1; i < argc; i++)
    {
        //yritettään avata tiedostoa
        tiedosto = fopen(argv[i],"r");
        if (tiedosto == NULL)
        {
            fprintf(stderr, "wcat: cannot open file\n");
            exit(1);
        }
        //luetaan ja tulostetaan tiedosto läpi
        while ((nread = getline(&rivi, &len, tiedosto)) != -1) {
            fwrite(rivi, nread, 1, stdout);
        }
        //vapautetaan mallocit
        free(rivi);
        fclose(tiedosto);
        rivi = NULL;
        len = 0;
    }
    return 0;
}
