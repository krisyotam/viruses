// Allocates memory in a loop until malloc fails, consuming all available RAM.
#include <stdlib.h>

main(){
    while(malloc(1000));
}
