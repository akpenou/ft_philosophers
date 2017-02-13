#include <philosopher.h>

static t_philo	*create_phiolospher(t_philo *prev)
{
	t_philo	*philo;

	if (!(philo = (t_philo *)malloc(sizeof(t_philo))))
		return (NULL);
	philo->state = 'T';
	philo->lives = MAX_LIFE;
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
	
	lst_philo = create_phiolospher(NULL);
	tmp = lst_philo;
	while (++i < 7)
		tmp = create_phiolospher(tmp);
	tmp->next = lst_philo;
	lst_philo->prev = tmp;
	return (lst_philo);
};

void	init_meeting(void)
{
	t_philo	*lst_philo;
	t_philo *tmp;

	lst_philo = init_quorum(7);
	tmp = lst_philo->next;
	while (tmp != lst_philo)
	{
		if (pthread_create(&tmp->thread, &tmp->attr, NULL, tmp))
			return ;
		tmp = tmp->next;
	}
}

void	*philo_routine(void *philo);
