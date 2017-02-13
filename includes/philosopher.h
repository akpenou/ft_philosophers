#ifndef PHILOSOPHER
# define PHILOSOPHER

# include <pthread.h>
# include <stdlib.h>
# include <time.h>

# define MAX_LIFE //Le nombre de points de vie maximum des philosophes.
# define EAT_T // Le nombre de SECONDES que met un philosophe à manger.
# define REST_T // Le nombre de SECONDES pendant lesquels un philosophe se repose.
# define THINK_T // Le nombre de SECONDES pendant lesquels un philosophe réfléchit.
# define TIMEOUT // Le temps en SECONDES après lesquels la simulation s’interrompt

typedef struct		s_philo
{
	char		state;
	unsigned int	lives;
	
	pthread_t	thread;
	pthread_attr_t	attr;
	pthread_mutex_t mutex;

	struct s_philo	*prev;
	struct s_philo	*next;
}			t_philo;

t_philo	*init(int n_philosophers);

#endif
