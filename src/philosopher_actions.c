#include <philosopher.h>

void	print_state(t_philo *philo)
{
	printf("philo: %d, state: %c, lives: %d, to_sleep: %d\n", philo->index, philo->state, philo->lives, philo->to_sleep);
}

int	routine_eat(t_philo *philo)
{
	if (pthread_mutex_trylock(&philo->mutex))
		return (0);
	if (pthread_mutex_trylock(&philo->next->mutex))
	{
			pthread_mutex_unlock(&philo->mutex);
			return (0);
	}
	philo->state = 'E';
	//philo->timeout = EAT_T;
	sleep(EAT_T);
	// printf("=== philo: %d, start %c\n", philo->index, philo->state);
	philo->lives = MAX_LIFE;
	pthread_mutex_unlock(&philo->next->mutex);
	pthread_mutex_unlock(&philo->mutex);
	philo->to_sleep = 1;
	// printf("=== philo: %d, end %c\n", philo->index, philo->state);
	return (1);
}

int	routine_think(t_philo *philo)
{
	if (pthread_mutex_trylock(&philo->mutex))
		return (0);
	philo->state = 'T';
	// printf("=== philo: %d, start %c\n", philo->index, philo->state);
	// philo->timeout = THINK_T;
	sleep(THINK_T);
	pthread_mutex_unlock(&philo->mutex);
	philo->to_sleep = 1;
	// printf("=== philo: %d, end %c\n", philo->index, philo->state);
	return (1);
}

int	routine_sleep(t_philo *philo)
{
	philo->state = 'S';
	// printf("=== philo: %d, start %c\n", philo->index, philo->state);
	// philo->timeout = REST_T;
	sleep(REST_T);
	philo->to_sleep = 0;
	// printf("=== philo: %d, end %c\n", philo->index, philo->state);
	return (1);
}
