#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

unsigned long long basecode = 1000000000000000;

/// Max `fastboot oem unlock {code}` command length
#define CMD_MAX_LEN 37
#define LASTCODE_FILE "lastcode"

void
quit()
{
    printf("\n\nLast tried code: %llu\n", basecode);
    FILE* fd = fopen(LASTCODE_FILE, "w");

    if (fd != NULL)
    {
        fprintf(fd, "%llu", basecode);
        fclose(fd);
    } else {
        printf("\x1b[1;91mERROR: Can't write lastcode file!\x1b[0;0m\n");
    }
    exit(1);
}

int
main(void)
{
    printf("Huawei bootloader unlock code bruterforcer\n");

    // Check if "lastcode" file exists and read old unlock code from it
    if (access(LASTCODE_FILE, R_OK) == 0)
    {
        printf("i\n");
        FILE* lastcodefile = fopen(LASTCODE_FILE, "r");
        // If there is a problem, do nothing
        if (lastcodefile != NULL)
        {
            char buf[255];
            if (fgets(buf, 255, lastcodefile) != NULL)
            {
                basecode = atoll(buf);
                fclose(lastcodefile);
            }
        }
    }

    // Write last tried code in `lastcode` file if possible
    signal(SIGINT, quit);
    signal(SIGTERM, quit);

    char cmdwithcode[CMD_MAX_LEN]; // Fastboot command (with code)
    do {
        // Increment basecode and create unlock command
        sprintf(cmdwithcode, "fastboot oem unlock %llu", basecode++);
        printf("\x1b[95mTrying code %llu\x1b[m\n", basecode);
    } while(system(cmdwithcode));

    return 0;
}
