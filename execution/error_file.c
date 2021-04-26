#include "../headers/minishell.h"

void	error_red_app(t_var *var, t_files *files)
{
	struct stat	buffer;

	if (var->fd[1] < 0 && !(stat(files->file_name, &buffer)))
	{
		if (buffer.st_mode & S_IFMT & S_IFDIR)
			no_file(var, files->file_name, "", ": Is a directory\n");
		else if (!(buffer.st_mode & W_OK))
			no_file(var, files->file_name, "", ": Permission denied\n");
		var->error = 1;
	}
}

void	error_open_file(t_var *var, t_files *files)
{
	struct stat	buff;

	if (!(stat(files->file_name, &buff)))
	{
		if (buff.st_mode & S_IFMT & S_IFDIR)
			no_file(var, files->file_name, "", ": Is a directory\n");
		else if (!(buff.st_mode & W_OK))
			no_file(var, files->file_name, "", ": Permission denied\n");
	}
	else
		no_file(var, files->file_name, "", ": No such file or directory\n");
	var->error = 1;
}
