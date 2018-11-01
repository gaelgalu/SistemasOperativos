#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    // printf("the counter is %d\n", atoi(argv[1]));
    printf(">> pid: %d, y he recibido esta llamada %d veces.\n", getppid(), atoi(argv[1]));
    return 0;
}
