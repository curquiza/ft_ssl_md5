#include "ft_ssl.h"

t_ex_ret	read_message_from_fd(int fd, char *filename, t_hash *data)
{
	int		read_ret;
	char	buff[READ_BUFF_LEN];
	t_byte	*tmp;

	while ((read_ret = read(fd, buff, READ_BUFF_LEN)) > 0)
	{
		tmp = data->msg;
		if (!(data->msg = (t_byte *)malloc(data->msg_len + read_ret)))
		{
			free(tmp);
			exit_malloc_err_with_clean(data);
		}
		if (tmp)
			ft_memmove(data->msg, tmp, data->msg_len);
		ft_memmove(data->msg + data->msg_len, buff, read_ret);
		data->msg_len += read_ret;
		free(tmp);
	}
	if (read_ret == -1)
		return ft_ret_err2(filename, strerror(errno));
	return SUCCESS;
}

// static t_ex_ret	read_message_from_file(int fd, char *filename, t_hash *data)
// {
// 	int		i;
// 	int		read_ret;
// 	t_byte	*tmp;
// 	char	buff[READ_BUFF_LEN];

// 	i = 0;
// 	while ((read_ret = read(fd, buff, READ_BUFF_LEN)) != 0)
// 	{
// 		if (read_ret == -1)
// 			return ft_ret_err2(filename, strerror(errno));
// 		tmp = data->msg;
// 		if (!(data->msg = (t_byte *)ft_memalloc(data->msg_len + read_ret)))
// 		{
// 			free(tmp);
// 			exit_malloc_err();
// 		}
// 		if (tmp)
// 			ft_memmove(data->msg, tmp, i);
// 		ft_memmove(data->msg + i, buff, read_ret);
// 		i += read_ret;
// 		free(tmp);
// 		data->msg_len += read_ret;
// 	}
// 	return (SUCCESS);
// }
