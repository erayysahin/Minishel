int	ft_tolower(int x)
{
	if (x <= 'Z' && x >= 'A')
		return (x += 32);
	return (x);
}
