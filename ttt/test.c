#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
int	FindNOD(int a, int b) 
{
	while (a && b) {
		if (a > b)
			a = a % b;
		else
			b = b % a;
	}
	return (a + b);
}

int *continued_fract(double num)
{
	int mem1, mem2;
	int *arr;
	int swap, nod;
	int i;

	arr = (int*)malloc(sizeof(int)*10);
	bzero(arr, sizeof(int) * 10);
	mem1 = 1000000;
	mem2 = (int)(num * mem1);
	// mem1 /=10;
	printf ("%i / %i\n",mem2, mem1);
	for (; i < 10 && mem1 != 0;i++)
	{
		nod = FindNOD(mem2, mem1);
		mem2 /= nod;
		mem1 /= nod;

		arr[i] = mem2 / mem1;
		mem2 = mem2 % mem1;
		swap = mem2;
		mem2 = mem1;
		mem1 = swap;
		printf("%i + %i / %i\n", arr[i], mem1, mem2);
	}
	return(arr);
}

void	suitable_fract(int *arr)
{
	int p[12], q[12];
	bzero(p, sizeof(int) * 12);
	bzero(q, sizeof(int) * 12);
	p[0] = 1;
	p[1] = arr[0];
	q[0] = 0;
	q[1] = 1;

	
	for(int i = 2; i < 10 && arr[i-1] != 0; i++)
	{
		p[i] = arr[i-1] * p[i - 1] + p[i - 2];
		q[i] = arr[i-1] * q[i - 1] + q[i - 2];
		printf("a(%u)\tp(%i)\tq(%i)\n",arr[i-2], p[i], q[i]);
	}
	printf("A -\t\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\n",arr[0],arr[1],arr[2],arr[3],arr[4],arr[5],arr[6],arr[7],arr[8],arr[9]);
	printf("P -\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\n",p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],p[9],p[10],p[11]);
	printf("Q -\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\n",q[0],q[1],q[2],q[3],q[4],q[5],q[6],q[7],q[8],q[9],q[10],q[11]);
}
int main(int argc, char **argv)
{
	int *cnotinued;
	if (argc == 2)
	{
		cnotinued = continued_fract(atof(argv[1]));
		suitable_fract(cnotinued);
		free(cnotinued);
	}
	// bla(4.5984f);
	// if (argc == 3)
	// {
	// 	int nod = FindNOD(atoi(argv[1]), atoi(argv[2]));
	// 	printf("%i /\t\t%i /\tnod - %i\n", atoi(argv[1]),atoi(argv[1])/nod,nod );
	// 	printf("%i\t\t%i\n",atoi(argv[2]),atoi(argv[2])/nod);
	// }
	return(0);
}
	// контики ос
	// lwip
	// ipv6