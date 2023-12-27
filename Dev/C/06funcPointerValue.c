#include <stdio.h>

void change_value(int *nb);

int main(int argc, char *argv[])
{
    int nb;

    nb = 42;
    change_value(&nb);
    printf("%d\n", nb);
    
    return 0;
}

void change_value(int *nb){

    *nb = 1337;

}
