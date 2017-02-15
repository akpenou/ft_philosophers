#ifndef PHILOSOPHER
# define PHILOSOPHER

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define MAX_LIFE 10//Le nombre de points de vie maximum des philosophes.
# define EAT_T 5// Le nombre de SECONDES que met un philosophe à manger.
# define REST_T 9// Le nombre de SECONDES pendant lesquels un philosophe se repose.
# define THINK_T  2// Le nombre de SECONDES pendant lesquels un philosophe réfléchit.
# define TIMEOUT  30// Le temps en SECONDES après lesquels la simulation s’interrompt

typedef struct		s_philo
{
	char		state;
	unsigned int	lives;
	int				index;
	
	pthread_t	thread;
	pthread_attr_t	attr;
	pthread_mutex_t mutex;

	struct s_philo	*prev;
	struct s_philo	*next;
}			t_philo;

t_philo	*init(int n_philosophers);
void	init_meeting(void);
void	print_state(t_philo *philo);
int		routine_sleep(t_philo *philo);
int		routine_think(t_philo *philo);
int		routine_eat(t_philo *philo);

#endif
