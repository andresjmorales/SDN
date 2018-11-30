#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <bool.h>
/*
firewall.c

Function will accept the key passed through the socket from the SDN Controller and check if it is an authorized or unauthorized value.
If it is authorized, it will return true.
If it is unauthorized, it will return false.

Parameters:

key -> the random key generated in the application layer

limit -> a defined value in the controller passed as a parameter. 
It is generic so that it can change accordingly without affecting the code.



*/
bool firewall(void *key, int limit){

  int castedKey = (int)key;  //cast void pointer as a key.
  if(castedKey < floor(limit/2)){
    printf("Firewall detected an authorized value.\n");
    return true;
  }
  else{
    printf("Firewall detected an unauthorized value.\n");
    return false;
  }

}
