/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbiot <rbarbiot@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:36:50 by rbarbiot          #+#    #+#             */
/*   Updated: 2023/10/06 16:36:50 by rbarbiot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_env(char **envp)
{
	int	i;

ft_printf("hihihiha\n");
	i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], 1);
        // prendre en compte les erreurs potentiels avec write
		i++;
	}
    return (1);
}
