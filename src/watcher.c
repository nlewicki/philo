/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:31:13 by nlewicki          #+#    #+#             */
/*   Updated: 2024/08/23 11:56:37 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo(t_philo *philo)
{
	int	result;

	result = 1;
	if (get_current_time() - philo->last_meal >= philo->data->time_to_die)
	{
		print_msg(philo, "\033[31mdied\033[0m");
		pthread_mutex_lock(&philo->data->lock);
		philo->data->alive = 0;
		pthread_mutex_unlock(&philo->data->lock);
		result = 0;
	}
	return (result);
}

void	*watcher_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (check_health(data) == 1)
	{
		if (check_meals(data) == 0 || check_philo(data->philo_list) == 0)
			break ;
	}
	return (NULL);
}
