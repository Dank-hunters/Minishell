unsigned long long int	ft_atoi_custom(char *str)
{
    int				i;
    int				sign;
    unsigned long long int	n;

    i = 0;
    sign = 1;
    while (str[i] == ' ')
	i++;
    if (str[i] == '-' && i++)
	sign = -1;
    else if (str[i] == '+')
	i++;
    n = 0;
    while (str[i] > 47 && str[i] < 58)
    {
	n *= 10;
	n += str[i] - 48;
	if (n > 9223372036854775807LL)
	    return (9223372036854775808ULL);
	i++;
    }
    if (str[i])
	    return (9223372036854775808ULL);
    return (n * sign);
}
