#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 50

void	print_tab(char **area);

void QuickSort_alpha(char *mas[], int left, int right)
{   
        int i, j, p;
        char *tmp[SIZE];
    i=left; 
    j=right;        
    while (i!=j){
        if((strcmp(mas[i],mas[j])>0)!= (i>j))
        {       
            tmp[i]=mas[i];      
            mas[i]=mas[j];
            mas[j]=tmp[i];
            
            p=i;    
            i=j;        
          
            if (p<j)    
                j=p+1;
            else 
                j=p-1;
        }
        else
        {
            if (i<j)
                j--; 
            else
                j++;
        };
    };
    
    if (left<i-1)
        QuickSort_alpha(mas,left,i-1);
    if (i+1<right) 
        QuickSort_alpha(mas,i+1,right);
}

void	print_tab(char **area)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (area[i])
	{
		while (area[i][j])
        {
			write(1, &area[i][j], 1);
            j++;
        }
		j = 0;
		i++;
        write(1, "\n", 1);
	}
}

int main(void)
{
    char *map[] = {
		"aaaabdc",
		"bfgdhs",
		"abs",
		"bcgfhd",
		"Ahgjk"
	};
    print_tab(map);
    QuickSort_alpha(map, 0, 3);
    write(1, "\n", 1);
    write(1, "\n", 1);
    print_tab(map);
    return (0);
}