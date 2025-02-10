#include "./includes/ms.h"

int	std_save(t_data *data)
{
	data->std[0] = dup(STDIN_FILENO);
	data->std[1] = dup(STDOUT_FILENO);
	if (data->std[0] == -1 || data->std[1] == -1)
	{
	//	ms->abort = 1;
		return (0);
	}
	return (1);
}

int	std_reset(t_data *data)
{
	if (dup2(data->std[0], 0) < 0 || dup2(data->std[1], 1) < 0)
	{
//		ms->abort = 1;
		return (0);
	}
	close(data->std[0]);
	close(data->std[1]);
	data->std[0] = -1;
	data->std[1] = -1;
	return (1);
}
