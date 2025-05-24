#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    char c;
    write(1, "minishell$ ", 11);
    read(0, &c, 1);

    return 0;
}
