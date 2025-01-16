#include "./includes/ms.h"

/*void	get_heredoc_lines(t_data *data, t_cmd *cmd)
{
	char	*line;

	line = readline("> ");
	while (line)
	{
		// Exits the loop early if the global code indicates an error.
		//if (ms_get_gcode() != 0)
		//{
		//	free(line);
		//	return;
		//}
		//
		//line = handle_env_variables(data, line); // if needed
		if (ft_strequ(line, cmd->eof))
		{
			free(line);
			return ;
		}
		ft_putendl_fd(line, cmd->tmp_doc[1]);
		free(line);
		line = readline("> ");
	}
}*/

/*int	ms_set_heredoc(t_data *data, t_cmd *cmd, t_token *tmp)
{
	cmd->heredoc = 1;
	cmd->eof = tmp->next->value;
	if (pipe(cmd->tmp_doc) == -1)
		return (ms_error(ERR_PROCESS_PIPE, NULL, 1, FAILURE));
	get_heredoc_lines(data, cmd);
	if (close(cmd->tmp_doc[1]) == -1)
		return (ms_error(ERR_PROCESS_CLOSE, NULL, 1, FAILURE));
	return (SUCCESS);
}*/
