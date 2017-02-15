#include <philosopher.h>

void	print_state(t_philo *philo)
{
	printf("philo: %d is %c with %d lives\n", philo->index, philo->state, philo->lives);
}

int	routine_eat(t_philo *philo)
{
	int	lock;

	if (pthread_mutex_trylock(&philo->mutex))
		return (0);
	if ((lock = pthread_mutex_trylock(&philo->next->mutex)) &&
			pthread_mutex_trylock(&philo->prev->mutex))
	{
		if (!lock)
			pthread_mutex_unlock(&philo->next->mutex);
		else
			pthread_mutex_unlock(&philo->prev->mutex);
		return (0);
	}
	philo->state = 'E';
	sleep(EAT_T);
	philo->lives = MAX_LIFE;
	if (!lock)
		pthread_mutex_unlock(&philo->next->mutex);
	else
		pthread_mutex_unlock(&philo->prev->mutex);
	pthread_mutex_unlock(&philo->mutex);
	return (1);
}

int	routine_think(t_philo *philo)
{
	if (pthread_mutex_trylock(&philo->mutex))
		return (0);
	philo->state = 'T';
	pthread_mutex_unlock(&philo->mutex);
	sleep(THINK_T);
	return (1);
}

int	routine_sleep(t_philo *philo)
{
	philo->state = 'S';
	sleep(REST_T);
	return (1);
}
