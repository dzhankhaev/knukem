
#include <stdio.h>
#include <stdlib.h>

unsigned int	*return_fuctorial_hop(void)
{
	unsigned int *ret;
	ret = (unsigned int *)malloc(sizeof(unsigned int) * 5);
	ret[0] = 1;
	ret[1] = 2;
	ret[2] = 145;
	ret[3] = 40585;
	return (ret);
}

void	fill_factorials(unsigned int *factorials)
{
	int		mult;

	factorials[0] = 1;
	for (int i = 1; i < 10; i++)
	{
		mult = 1;
		for (int j = i; j > 1; j--)
			mult *= j; 
		factorials[i] = mult;
	}
}

unsigned int	*return_fuctorial(void)
{
	// const unsigned int	fact[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
	unsigned int	fact[10];
	unsigned int	sum = 0;
	unsigned int	num = 0;
	unsigned int	*ret;
	int				j = 0;

	ret = (unsigned int *)malloc(sizeof(unsigned int) * 4);
	fill_factorials(fact);
	for(unsigned int i = 1; j < 4; i++)
		{
			num = i;
			sum = 0;
			while (num)
			{
				sum += fact[num % 10];
				num /= 10;
			}
			if (sum == i)
			{
				ret[j] = sum;
				j++;
			}
		}
	return (ret);
}


int			main(int argc, char **argv)
{
	unsigned int *ret;

	ret = return_fuctorial();
	for (int i = 0; i <4;i++)
		printf("%i\t", ret[i]);
	free(ret);
	/* code */
	return 0;
}
