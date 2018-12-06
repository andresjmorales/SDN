#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "auth.h"

/*
Numbers will simulate an authenticated user.
It's the thought that counts.
*/

char* auth(int limit, char *autharr){

	srand(time(0)); 
	int auth = rand() % limit; //remember that 0-500 is authorized. 501-999 is unauthorized
	sprintf(autharr, "%d", auth);//convert int to a string
	return autharr;
}
