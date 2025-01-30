#include "./includes/ms.h"

void	free_char_double_ptr(char ***ptr)
{
	int	i;

	if (ptr == NULL || *ptr == NULL)
		return ;
	i = 0;
	while ((*ptr)[i] != NULL)
	{
		free((*ptr)[i]);
		(*ptr)[i] = NULL;
		i++;
    }
	free(*ptr);
	*ptr = NULL;
}

void	ms_free(t_data *data)
{
	if (data->prompt)
		free(data->prompt);
	if (data->cwd)
		free(data->cwd);
	if (data->input_user)
		free(data->input_user);
	if (data->envp)
		free_char_double_ptr(&data->envp);
	if (data->envp_path)
		free_char_double_ptr(&data->envp_path);
	if (data->pid)
		free(data->pid);
//	if (data->fd)
//		free(data->fd);
}
/*
void	ms_reset(t_data *data)
{
	data->prompt = NULL;
	data->cwd = NULL;
	data->input_user = NULL;
	data->envp = NULL;
	data->envp_path = NULL;
	data->total_cmds = 0;
	data->total_process = 0;
	data->pid = NULL;
	data->fd = NULL;
}*/
