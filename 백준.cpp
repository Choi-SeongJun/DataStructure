#include <stdio.h>

int main(void)
{
    int i; 
    int num[9];
    int max_i, max=0;
    for(i=0; i<9; i++)
    {
        scanf("%d", &num[i]);
    }
    for(i=0; i<9; i++)
    {
        if(num[i]>max)
        {
        	max = num[i];
        	max_i = i;
		}
    }
    printf("%d\n%d", max, max_i+1);
    return 0;
}
