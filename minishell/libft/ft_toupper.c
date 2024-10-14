int	ft_toupper(int x)
{
	if (x <= 'z' && x >= 'a')
		return (x -= 32);
	return (x);
}
