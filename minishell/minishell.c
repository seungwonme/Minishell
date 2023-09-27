/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:00:19 by seunan            #+#    #+#             */
/*   Updated: 2023/09/27 14:17:45 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_vars *vars)
{
	char	*str;

	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigquit_handler);
		str = readline("\033[0;36mminishell$\033[0m ");
		if (str == NULL)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		add_history(str);
		if (!quotes_check(str))
			continue ;
		vars->lst = tokenize(str);
		if (syntax_check(vars->lst))
			execute(vars);
		free_str_tok(str, &(vars->lst));
	}
}
