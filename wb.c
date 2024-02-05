#include <stdio.h>
#include <unistd.h>

int main(void) {
    int	child1 = fork(); // First fork
    int	child2 = fork(); // Second fork
    
    printf("Hello world ID: %d, %d\n", child1, child2);
    return 0;
}
