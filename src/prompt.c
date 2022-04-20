#include "coquillette.h"

char	*prompt_builder(t_data *data)
{
	char	*prompt;
	t_env	*env;

	env = find_env_var(data->env, "PWD");
	prompt = ft_calloc(ft_strlen("\e[34mcoquillette:> \e[0m") + ft_strlen(env->value) + 1, 1);
	ft_strcat(prompt, "\e[34mcoquillette: ");
	ft_strcat(prompt, env->value);
	ft_strcat(prompt, ">\e[0m");
	return (prompt);
}
