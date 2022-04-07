#include "../includes/philo_one.h"

unsigned int	ft_atoi(const char *str)
{
	long			negative;
	long			result;
	unsigned int	i;

	negative = 1;
	result = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
			str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return ((int)(result * negative));
}

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	upgrade_usleep(double msec)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < msec)
		usleep(100);
}

void	print_logs(char *str, t_philo *ph)
{
	pthread_mutex_lock(&ph->m[ph->print_mutext]);
	if (!g_death_flag)
		printf("[%lu] phil number %d %s\n", get_time() - ph->start_time,
			ph->n + 1, str);
	pthread_mutex_unlock(&ph->m[ph->print_mutext]);
}

void	my_free(t_philo *ph)
{
	if (ph)
	{
		if (ph->m)
			free(ph->m);
		if (ph->t)
			free(ph->t);
		free(ph);
	}
}
