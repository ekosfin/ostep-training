/*käytettyjä lähteitä:
https://man7.org/linux/man-pages/man3/getline.3.html
https://www.tutorialspoint.com/c_standard_libary/c_funtion_strtok.htm
https://stackoverflow.com/questions/13000047/function-to-remove-newline-has-no-effect
*/

#define _GNU_SOURCE
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct l_lista
{
    char *data;
    struct l_lista *pEdellinen;
};
typedef struct l_lista linkitettylista;

void noArguments();
void inputFile(char const *argv[]);
void inputAndOutputFile(char const *argv[]);

int main(int argc, char const *argv[])
{
    //eli tarkista onko argc numero 1,2 vai 3 jos enemmän niin älä hyväksy.
    //idea käytä getlinee koska se ei oleta rivin kokoa
    //eka getline looppi jotta laskee monta rivii
    //sitten aliohjelma looppi joka alkaa tulostaa n, sitten n-1 aina 0 asti
    //ei todellakaan tehokas, koska vaatii todella paljon I/Ota jos iso tiedosto joka on aikaa vievää
    //mutta toimiva ratkaisu

    if (argc > 3) //tarkistaa onko käyttäjä syöttänyt liian monta agrumenttia
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    if (argc == 3 && !strcmp(argv[1], argv[2])) //tarkistaa että käyttäjä ei antanut argumenteissa samaa tiedostoa inputtina ja outputtina
    {
        fprintf(stderr, "Input and output file must differ\n");
        exit(1);
    }

    if (argc == 1)
    {
        noArguments();
        exit(0);
    }

    if (argc == 2)
    {
        inputFile(argv);
        exit(0);
    }

    if (argc == 3)
    {
        inputAndOutputFile(argv);
        exit(0);
    }

    return 0;
}

/*
tää oli siinä tehtävänannossa epäselvin osio sillä ainoa esimerkki 
miten homman pitäisi toimia on että se vaihtaa rivien järjestyksen,
mutta ei antanut mitään esimerkkiä miten se pitäisi toteuttaa tälle 
getline lopettaa nähdessään newlinen joten stdin kautta et saa monia 
rivejä samaan aikaan, mutta koska ideana oli kääntää järjestystä niin
päätin pilkkoa välillä ja kääntää niiden järjestyksen.
*/
/*
tämä funtio skannaa stdin ja palauttaa sen käännettynä stdoutiin jakamalla väleistä käyttäen linkitettyä listaa
*/
void noArguments()
{
    //asetetaan muuttujia
    char *line = NULL, *jako, *temp;
    size_t len = 0;
    ssize_t nread;
    linkitettylista *ptr = NULL, *ptrVanha = NULL;

    printf("type to reverse (reverses words divided by space): ");

    if ((nread = getline(&line, &len, stdin)) == -1) //virheentarkistus jos luku käyttäjältä epäonnistuu
    {
        fprintf(stderr, "reading from stdin failed\n");
        exit(1);
    }
    //poistetaan newline
    if (line[nread - 1] == '\n')
    {
        line[nread - 1] = '\0';
        --nread;
    }

    jako = strtok(line, " ");
    while (jako != NULL)
    {
        //tallenna jakot jotta voit tulostaa listaan toisin päin.
        if ((ptr = (linkitettylista *)malloc(sizeof(linkitettylista))) == NULL) //virheenkäsittelyä tilaa varatessa
        {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        if ((temp = (char *)malloc(nread * sizeof(char))) == NULL) //vähän tilaa hukkaavaa, mutta ei oleta sanojen pituutta
        {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        //tallenetaan data linkiin
        strcpy(temp, jako);
        ptr->data = temp;
        ptr->pEdellinen = ptrVanha;
        //koska haluan mennä lopusta alkuun niin minun ei tarvitse muistaa alkua vain kirjata edellinen linkiin
        ptrVanha = ptr;
        jako = strtok(NULL, " ");
        //jaa luupataan kunnes kaikki käyty.
    }

    //sitten käydään linkitettylista läpi viimeisestä ensimmäiseen.
    printf("now reverced:");
    while (ptr != NULL)
    {
        printf(" %s", ptr->data);
        free(ptr->data); //samalla vapautetaan
        ptr = ptr->pEdellinen;
        free(ptrVanha);
        ptrVanha = ptr;
    }
    free(line);
    printf("\n");
}

/*
tämä funtio skannaa tiedoston ja palauttaa sen käännettynä stdoutiin jakamalla rivin vaihdoista käyttäen linkitettyälistaa
*/
void inputFile(char const *argv[])
{
    //asetetaan muuttujia
    FILE *stream;
    char *line = NULL, *temp;
    size_t len = 0;
    ssize_t nread;
    linkitettylista *ptr = NULL, *ptrVanha = NULL;

    //yritettään avata tiedostoa
    stream = fopen(argv[1], "r");
    if (stream == NULL)
    {
        fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
        exit(1);
    }

    //luetaan tiedosto läpi siirtäen se linkitettyyn listaan.
    //HUOM: isot tiedostot tulee viemään paljon muistia eli ei fiksuin ratkaisu siinä tapaukessa
    while ((nread = getline(&line, &len, stream)) != -1)
    {
        //poistetaan newline
        if (line[nread - 1] == '\n')
        {
            line[nread - 1] = '\0';
            --nread;
        }
        if ((ptr = (linkitettylista *)malloc(sizeof(linkitettylista))) == NULL) //virheenkäsittelyä tilaa varatessa
        {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        if ((temp = (char *)malloc(nread * sizeof(char))) == NULL)
        {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        strcpy(temp, line);
        ptr->data = temp;
        ptr->pEdellinen = ptrVanha;
        ptrVanha = ptr;
    }
    free(line);
    fclose(stream);

    //nyt tulostetaan käyttäjälle mitä luettu
    while (ptr != NULL)
    {
        printf("%s\n", ptr->data);
        free(ptr->data); //samalla vapautetaan
        ptr = ptr->pEdellinen;
        free(ptrVanha);
        ptrVanha = ptr;
    }
}

/*
tämä funtio skannaa tiedoston ja palauttaa sen käännettynä tiedostoon jakamalla rivin vaihdoista käyttäen linkitettyälistaa
*/
void inputAndOutputFile(char const *argv[])
{
    //asetetaan muuttujia
    FILE *streamIN, *streamOUT;
    char *line = NULL, *temp;
    size_t len = 0;
    ssize_t nread;
    linkitettylista *ptr = NULL, *ptrVanha = NULL;

    //yritettään avata tiedostoa
    streamIN = fopen(argv[1], "r");
    if (streamIN == NULL)
    {
        fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
        exit(1);
    }
    streamOUT = fopen(argv[2], "w");
    if (streamOUT == NULL)
    {
        fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
        exit(1);
    }

    //luetaan tiedosto läpi siirtäen se linkitettyyn listaan.
    //HUOM: isot tiedostot tulee viemään paljon muistia eli ei fiksuin ratkaisu siinä tapaukessa
    while ((nread = getline(&line, &len, streamIN)) != -1)
    {
        //poistetaan newline
        if (line[nread - 1] == '\n')
        {
            line[nread - 1] = '\0';
            --nread;
        }
        if ((ptr = (linkitettylista *)malloc(sizeof(linkitettylista))) == NULL) //virheenkäsittelyä tilaa varatessa
        {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        if ((temp = (char *)malloc(nread * sizeof(char))) == NULL)
        {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        strcpy(temp, line);
        ptr->data = temp;
        ptr->pEdellinen = ptrVanha;
        ptrVanha = ptr;
    }
    free(line);
    fclose(streamIN);

    //nyt tulostetaan tiedostoon mitä on luettu
    while (ptr != NULL)
    {
        fprintf(streamOUT, "%s\n", ptr->data);
        free(ptr->data); //samalla vapautetaan
        ptr = ptr->pEdellinen;
        free(ptrVanha);
        ptrVanha = ptr;
    }
    fclose(streamOUT);
}