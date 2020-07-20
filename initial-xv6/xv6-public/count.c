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