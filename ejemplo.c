#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int aflag = 0;
	char* name = NULL;
	int rut, edad;

	int option = 0;

	while ((option = getopt(argc, argv, "an:r:e:")) != -1) {
		switch (option) {
			 case 'a' : aflag = 1;
			 	 break;
			 case 'n' : name = optarg;
			 	 break;
             case 'r' : rut = atoi(optarg); 
                 break;
             case 'e' : edad = atoi(optarg);
                 break;
             default: 
                 exit(EXIT_FAILURE);
        }
    }

    if (aflag != 0)	printf("El nombre del estudiante es: %s, cuyo rut es %d, con %d años de edad.\n", name, rut, edad);

    return 0;
}