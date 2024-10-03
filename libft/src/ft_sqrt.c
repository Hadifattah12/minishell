
int	ft_sqrt(int nb)
{
	int	i;

	i = 0;
	if (nb * nb <= 2147483647)
	{
		while (i * i < nb)
		{
			i++;
			if (i * i > nb)
				return (i - 1);
		}
	}
	return (i);
}
