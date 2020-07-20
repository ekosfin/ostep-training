/*
käytettyjä lähteitä:
https://man7.org/linux/man-pages/man3/getline.3.html
https://www.tutorialspoint.com/c_standard_library/c_function_strstr.htm
*/

#define _GNU_SOURCE
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char const *argv[])
{
    //Tarkistetaan onko syötetty argumenteja
    if (argc < 2)
    {
        fprintf(stderr, "wgrep: searchterm [file ...]\n");
        exit(1);
    }

    //määritellään tarvittavia muuttujia
    char *rivi = NULL;
    size_t len = 0, pituus;
    ssize_t nread;

    //tarkistetaan onko käyttäjä vain syöttänyt hakusanan
    if (argc == 2)
    {
        //luetaan käyttäjältä syötettä
        nread = getline(&rivi, &len, stdin);
        pituus = strlen(argv[1]); //katsotaan sanan pituus
        //jos luettu syöte on lyhyempi kuin haettu niin se ei voi olla siinä joten lopetetaan.
        if (nread < pituus)
        {
            exit(0);
        }

        if (strstr(rivi, argv[1]) != NULL) //tarkistetaan sisältääkö syöte hakua
        {
            fwrite(rivi, nread, 1, stdout);
        }
    }
    else if (argc > 2)
    {
        FILE *tiedosto;
        for (size_t i = 2; i < argc; i++)
        {
            //yritettään avata tiedostoa
            tiedosto = fopen(argv[i], "r");
            if (tiedosto == NULL)
            {
                fprintf(stderr, "wgrep: cannot open file\n");
                exit(1);
            }
            //luetaan ja tulostetaan tiedosto läpi
            while ((nread = getline(&rivi, &len, tiedosto)) != -1)
            {
                pituus = strlen(argv[1]); //katsotaan sanan pituus
                //jos luettu syöte on lyhyempi kuin haettu niin se ei voi olla siinä joten ei tarvitse etsiä.
                if (nread > pituus)
                {
                    if (strstr(rivi, argv[1]) != NULL) //tarkistetaan sisältääkö syöte hakua
                    {
                        fwrite(rivi, nread, 1, stdout);
                    }
                }
            }
            //vapautetaan mallocit
            free(rivi);
            fclose(tiedosto);
            rivi = NULL;
            len = 0;
        }
    }

    exit(0);
}