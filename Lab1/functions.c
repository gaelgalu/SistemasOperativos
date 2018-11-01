#include "functions.h"

int counter;
int interruptCounter;
int fatherPid;

void interruptSignalController(int value) {
    interruptCounter++;

    if (interruptCounter == 2){
        exit(1);
    } else if (getpid() != fatherPid) {
        printf(">> Soy el hijo con pid: %d, y estoy vivo aún. No me mates papá.\n", getpid());
    }
}

void counterSignalController(int value) {
    char counter_str[5];
    sprintf(counter_str, "%d", counter);

    counter ++;
    int pid = fork();    
    if (pid == 0) {
        char str[12];
        sprintf(str, "%d", counter);
        // execlp("gcc", "gcc", "-o", "contador.o", "contador.c", NULL); //Usar esta función para compilar. Cuidado con el cambio de contexto.
        execl("./contador.o", "contador.o", str, NULL);

    }
    else {
        waitpid(pid, NULL, 0);
    }

    // printf(">> pid: %d, y he recibido esta llamada %d veces.\n", getpid(), counter);
}

void killSignalController(int value) {
    printf("Soy el hijo con pid: %d y mi papá me quiere matar\n", getpid());
    exit(1);
}

void forkSignalController(int value) {
    fork();
}

char convertSignal(int number) {
    if (number == 15) {
        return 'A';
    }
    else if (number == 16) {
        return 'B';
    }

    return 'C';
}

void init(int children, int mflag) {

    int x = 0;
    int y = 0;
    fatherPid = getpid();
    int* pids = (int*)malloc(children * sizeof(int));

    signal(SIGINT, interruptSignalController);
    signal(SIGUSR1, counterSignalController);
    signal(SIGUSR2, forkSignalController);
    signal(SIGTERM, killSignalController);

    for (int i = 0; i < children; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            break;
        }
    }

    if (getpid() == fatherPid) {
        if (mflag) {
            printf("Mostrando la información por pantalla:\n");
            for (int i = 0; i < children; i++) {
                printf("Numero %d, pid: %d\n", i+1, pids[i]);
            }
        }

        char z;
        while(1) {
            printf(">> Ingresar número de hijo y señal a enviar (X - Y):\n");
            printf(">> ");
            scanf("%d - %d", &x, &y);
            printf(">> La señal %d será enviada al hijo %d de pid %d,\n", y, x, pids[x-1]);

            z = convertSignal(y);

            switch (z) {
                case 'A':
                    kill(pids[x-1], SIGTERM);
                    sleep(1);
                    break;
                case 'B':
                    kill(pids[x-1], SIGUSR1);
                    sleep(1);
                    break;
                case 'C':
                    kill(pids[x-1], SIGUSR2);
                    sleep(1);
                    break;
            }
        }
    }
    else {
        counter = 0;
        while (1) {
            /* children will be waiting for a signal until the father dies*/
        }
    }

    free(pids);
}
