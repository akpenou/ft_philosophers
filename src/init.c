#include <philosopher.h>

static t_philo	*create_phiolospher(t_philo *prev, int i)
{
	t_philo	*philo;

	if (!(philo = (t_philo *)malloc(sizeof(t_philo))))
		return (NULL);
	philo->state = 'T';
	philo->lives = MAX_LIFE;
	philo->index = i;
	pthread_mutex_init(&philo->mutex, NULL);
	philo->prev = prev;
	philo->next = NULL;
	if (prev)
		prev->next = philo;
	return (philo);
}

t_philo	*init_quorum(int n_philosophers)
{
	int	i;
	t_philo	*lst_philo;
	t_philo *tmp;
	
	i = 0;
	lst_philo = create_phiolospher(NULL, i);
	tmp = lst_philo;
	while (++i < 7)
		tmp = create_phiolospher(tmp, i);
	tmp->next = lst_philo;
	lst_philo->prev = tmp;
	return (lst_philo);
};

void	*philo_routine(void *philo_cpy)
{
	t_philo	*philo;

	philo = philo_cpy;
	while (philo->lives)
		if (routine_eat(philo) || routine_think(philo) || routine_sleep(philo))
			continue ;
	return (NULL);
}

void	init_meeting(void)
{
	t_philo			*lst_philo;
	t_philo 		*tmp;
	unsigned int	timer;

	lst_philo = init_quorum(7);
	tmp = lst_philo->next;
	if (pthread_create(&lst_philo->thread, &tmp->attr, philo_routine, lst_philo))
		return ;
	while (tmp != lst_philo)
	{
		if (pthread_create(&tmp->thread, &tmp->attr, philo_routine, tmp))
			return ;
		tmp = tmp->next;
	}
	timer = -1;
	while (++timer < TIMEOUT)
	{
		tmp = lst_philo->next;
		--lst_philo->lives;
		while (tmp != lst_philo)
		{
			--tmp->lives;
			tmp = tmp->next;
		}
		sleep(1);
	}
}
