#include <philosopher.h>

static t_philo	*create_phiolospher(t_philo *prev, int i)
{
	t_philo	*philo;

	if (!(philo = (t_philo *)malloc(sizeof(t_philo))))
	{
		puts("failed malloc");
		return (NULL);
	}
	philo->state = 'T';
	philo->lives = MAX_LIFE;
	philo->index = i;
	philo->timeout = 0;
	philo->to_sleep = 0;
	pthread_mutex_init(&philo->mutex, NULL);
	philo->prev = prev;
	philo->next = NULL;
	if (prev)
		prev->next = philo;
	puts("end philo");
	return (philo);
}

t_philo	*init_quorum(int n_philosophers)
{
	int	i;
	t_philo	*lst_philo;
	t_philo *tmp;
	
	puts(__func__);
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
	while (philo->lives > 0)
	{
		//if (philo->timeout > 0)
		//	continue ;
		if (philo->to_sleep)
			routine_sleep(philo);
		if (routine_eat(philo) || routine_think(philo))
			continue ;
		// routine_sleep(philo);
		// print_state(philo);
	}
	printf("%p is die\n", philo);
	philo->state = 'D';
	return (NULL);
}

void	init_meeting(void)
{
	int				ret;
	t_philo			*lst_philo;
	t_philo 		*tmp;
	unsigned int	timer;

	lst_philo = init_quorum(7);
	tmp = lst_philo->next;
	ret = pthread_create(&lst_philo->thread, NULL, philo_routine, lst_philo);
	if (ret)
		return ;
	while (tmp != lst_philo)
	{
		if (pthread_create(&tmp->thread, NULL, philo_routine, tmp))
			return ;
		tmp = tmp->next;
	}
	timer = -1;
	while (++timer < TIMEOUT)
	{
		printf("time: %u\n", timer);
		tmp = lst_philo->next;
		print_state(lst_philo);
		--lst_philo->lives;
		--lst_philo->timeout;
		while (tmp != lst_philo)
		{
			--tmp->lives;
			--lst_philo->timeout;
			print_state(tmp);
			tmp = tmp->next;
		}
		sleep(1);
	}
}
