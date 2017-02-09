#include <philosopher.h>

t_philo	*create_phiolospher(t_philo *prev)
{
	t_philo	*philo;

	if (!(philo = (t_philo *)malloc(sizeof(t_philo))))
		return (NULL);
	philo->state = 'T';
	philo->mutex = PTHREAD_MUTEX_INITIALIZER;
	philo->prev = prev;
	philo->next = NULL;
	if (prev)
		prev->next = philo;
	return (philo);
}

t_philo	*init(int n_philosophers)
{
	int	i;
	t_philo	*lst_philo;
	t_philo = tmp;
	
	lst_philo = create_phiolospher(NULL);
	tmp = lst_philo;
	while (++i < 7)
		tmp = create_phiolospher(tmp);
	tmp->next = lst_philo;
	lst_philo->prev = tmp;
	return (lst_philo);
};
