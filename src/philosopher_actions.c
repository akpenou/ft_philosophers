#include <philosopher.h>

int	routine_eat(t_philo *philo)
{
	if (pthread_mutex_trylock(&philo->mutex))
		return (0);
	if (pthread_mutex_trylock(&philo->next->mutex) && pthread_mutex_trylock(&philo->prev->mutex))
	{
		pthread_mutex_unlock(&philo->mutex);
		return (0);
	}
	printf("philo: %p is %s\n", philo, "eating");
	sleep(EAT_T);
	pthread_mutex_unlock(&philo->mutex);
}

int	routine_think(t_philo *philo)
{
	if (pthread_mutex_trylock(&philo->mutex))
		return (0);
	printf("philo: %p is %s\n", philo, "thinking");
	sleep(THINK_T);
}

int	routine_sleep(t_philo *philo)
{
	printf("philo: %p is %s\n", philo, "sleeping");
	sleep(REST_T);
}
