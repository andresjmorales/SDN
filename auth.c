#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "auth.h"

/*
Numbers will simulate an authenticated user. It's the thought that counts.
*/

int auth(int limit){
	srand(time(0)); 
	int auth = rand() % limit; //remember that 0-500 is authorized. 501-999 is unauthorized
	return auth;
	
}
