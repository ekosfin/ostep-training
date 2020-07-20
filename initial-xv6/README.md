# xv6 added system call

Link to the assingment: https://github.com/remzi-arpacidusseau/ostep-projects/tree/master/initial-xv6
Link to the xv6: https://github.com/mit-pdos/xv6-public

Rest will be in finnish as well as the comments on the code.

## Dokumentaatio

Tämä harjoitustyön dokumentaatio ja kommentin ovat suurimmaksi osaksi tässä README.md tiedostossa.

Kansiosta xv6-public löytyy muokattu [xv6-public](https://github.com/mit-pdos/xv6-public) käyttöjärjestelmä mihin olen lisännyt systeemikutsun nimeltä count sekä tarvittavat muokkaukset saadakseni käskyllä count tulostettua kuinka monta kertaa read systeemikutsua on kutsuttu käynnistymisestä tai viimeisestä resetoinnista asti.

### Oletukset ja virheet

Ohjelmisto on rakennettu make qemu-nux komennolla ja todettu toimivaksi. qemu:n aikana systeemikutsua voi testata käyttämällä **count** tai **count reset** komentoja, **count reset** resetoi laskimen.

### Muokatut tiedostot perus xv6:sta

Eli seuraavaksi listaan tiedosto, joita jouduin muokkaamaan saadakseni systeeemikutsun toimimaan ja näytän mitä olen sinne lisännyt.

**syscall.h**

```c
...
#define SYS_count 22

```

Tiedostoon määritelty systeemikutsulle count numero millä sen voi tunnistaa.

**defs.h**

```c
...
int             count(int);
...
```

Tiedostoon määritelty missä funktio sijaitsee ja mitä arvoja sille pitää antaa ja mitä se palauttaa.

**user.h**

```c
...
int             count(int);
...
```

Tiedostoon määritelty mitä arvoja funtioon pitää antaa ja mitä se palautaa.

**sysproc.c**

```c
...
int
sys_count(void)
{
  int check;
  //checks if there are arguments
  if(argint(0, &check) < 0)
    return -1;

  return count(check);
}
```

Tiedostoon määritelty systeemikutsu sys_count ja siinä otetaan argumentti minkä käyttäjä on antanut ja annetaan se count funktiolle.

**syscall.c**

```c
...
extern int countCalls;
...
[SYS_count]   sys_count,
};

void
syscall(void)
{
  int num;
  struct proc *curproc = myproc();

  num = curproc->tf->eax;
  if(num > 0 && num < NELEM(syscalls) && syscalls[num]) {

    if (num == 5)
    {
      countCalls++;
    }

    curproc->tf->eax = syscalls[num]();
  } else {
    cprintf("%d %s: unknown sys call %d\n",
            curproc->pid, curproc->name, num);
    curproc->tf->eax = -1;
  }
}
```

Tiedostoon lisätty viittaus int:stä joka pitää kirjaa montako kertaa tiettyä systeemikutsua on kutsuttu, sekä ohjelmoitu sen kasvamaan, kun oikea systeemi kutsu numero tulee esille (tässä tapauksessa 5, joka vastaa read kutsua).

**proc.c**

```c
...
int countCalls = 0;
...
int
count(int check)
{
  if (check > 0)
  {
    countCalls = 0;
    cprintf("Laskin resetoitu\n");
    return 22;
  }

  cprintf("Read systeemikutsua on kutsuttu nyt %d kertaa\n", countCalls);
  return 22;
}
```

Tiedostoon alustettu countCalls joka pitää kirjaa montako kertaa read systeemikutsua on kutsuttu. Sen lisäksi funktio count löytyy täältä logiikalla, jolla pystyy resetoimaan laskimen tai kertomaan nykyisen luvun.

**usys.S**

```asm
...
SYSCALL(count)
```

Tiedostoon lisätty ilmoitus count systeemikutsun olemassa olosta.

**count.c**

```c
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main (int argc, char *argv[])
{
    int a = 0;
    if(argc < 2)
    {
        //setting zero to indicate no need to reset counter
        count(a);
        exit();
    }
    else if (argc == 2)
    {
        char *comp = "reset";
        if (!strcmp(argv[1],comp))
        {
            a = 1;
            count(a);
            exit();
        }
        printf(2,"to reset: count reset\n");
        exit();
    }

    printf(2,"usage: count OR count reset\n");
    exit();
}
```

Viimeiseksi tehty itse tiedosto missä on perus c funktio, joka sisältää countin.

### Käytettyjä lähteitä

https://stackoverflow.com/questions/8021774/how-do-i-add-a-system-call-utility-in-xv6
https://zoo.cs.yale.edu/classes/cs422/2010/xv6-book/trap.pdf
https://github.com/remzi-arpacidusseau/ostep-projects/blob/master/initial-xv6/background.md
