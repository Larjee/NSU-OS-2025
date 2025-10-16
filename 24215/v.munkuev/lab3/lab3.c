#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

int main(void) {
    uid_t ruid, euid;
    const char *filename = "file";
    FILE *f;

    // Печатаем ruid и euid 
    ruid = getuid();
    euid = geteuid();
    printf("Before setuid:\n");
    printf("    real uid = %u\n", (unsigned)ruid);
    printf("    effective uid = %u\n", (unsigned)euid);


    f = fopen(filename, "r");
    if (f) {
        printf("Opening succeeded (before setuid)\n");
        fclose(f);
    } else {
        printf("Opening failed (before setuid): ");
        perror("");
    }

    // Делаем ruid и euid совпадающими 
    if (setuid(euid) == -1) {
        printf("setuid(%u) failed: ", (unsigned)euid);
        perror("");
    } else {
        printf("setuid(%u) succeeded.\n", (unsigned)euid);
    }


    ruid = getuid();
    euid = geteuid();
    printf("After setuid:\n");
    printf("    real uid = %u\n", (unsigned)ruid);
    printf("    effective uid = %u\n", (unsigned)euid);

    f = fopen(filename, "r");
    if (f) {
        printf("Opening succeeded (after setuid)\n");
        fclose(f);
    } else {
        printf("Opening failed (after setuid): ");
        perror("");
    }

    return 0;
}