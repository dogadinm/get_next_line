/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:53:09 by mdogadin          #+#    #+#             */
/*   Updated: 2023/11/07 11:33:20 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_copy_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_read_file(int fd, char *str)
{
	char	*temp;
	int		bytes_read;

	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(str, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(temp);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		str = ft_strjoin(str, temp);
	}
	free(temp);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str[fd] = ft_read_file(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = ft_copy_line(str[fd]);
	str[fd] = ft_remove(str[fd]);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int fd;
    char *line;

    if (argc < 2)
    {
        printf("Usage: ./gnl_test <file_path1> <file_path2> ...\n");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        fd = open(argv[i], O_RDONLY);
        if (fd < 0)
        {
            perror("Error opening file");
            continue;
        }

        printf("\nReading from file: %s\n", argv[i]);

        while ((line = get_next_line(fd)) != NULL)
        {
            printf("%s", line);
            free(line);
        }

        close(fd);
    }
    return 0;
}
*/
