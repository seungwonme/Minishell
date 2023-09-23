#include "../minishell.h"

int	ft_isvalidkey(char *key)
{
	int	i;

	if (!ft_isalpha(*key) && *key != '_')
		return (0);
	i = 0;
	while (key[i] != '=' && key[i] != '\0')
	{
		printf("key[%d] : %c\n", i, key[i]);
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_isspecialtok(char *token)
{
	if (ft_strncmp(token, "|", 2) == 0)
		return (1);
	if (ft_strncmp(token, "<", 2) == 0)
		return (1);
	if (ft_strncmp(token, "<<", 3) == 0)
		return (1);
	if (ft_strncmp(token, ">", 2) == 0)
		return (1);
	if (ft_strncmp(token, ">>", 3) == 0)
		return (1);
	return (0);
}

t_env	*ft_envlast(t_env *env)
{
	if (env == NULL)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	ft_envadd_back(t_env **head, t_env *new)
{
	t_env	*tmp;

	if (new == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	tmp = ft_envlast(tmp);
	tmp->next = new;
}

t_env	*make_env(char *content)
{
	t_env	*env;
	char	*tmp;
	char	*cut;

	tmp = ft_strdup(content);
	env = (t_env *)ft_calloc(1, sizeof(t_env));
	cut = ft_strchr(tmp, '=');
	if (cut == NULL)
	{
		env->key = tmp;
		env->value = NULL;
		return (env);
	}
	env->value = ft_strdup(cut + 1);
	*cut = '\0';
	env->key = ft_strdup(tmp);
	env->next = NULL;
	free(tmp);
	return (env);
}

t_env	*dup_env(char *envp[])
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		ft_envadd_back(&env, make_env(envp[i]));
		++i;
	}
	return (env);
}
