/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 21:26:06 by yli               #+#    #+#             */
/*   Updated: 2023/04/19 21:26:08 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
#endif

char    ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return i;
}

char *ft_strcpy(char *str, char *s2, int len)
{
    int i;

    i = 0;
    str = malloc(sizeof(char) * (len) + 1);
    if(!str)
        return 0;
    while( i < len)
    {
        str[i] = s2[i];
        i++;
    }
    str[i] = 0;
    return str;
}
char    *strjoin(char *s1, char *s2, int len)
{
    int i;
    int j;
    char *str;

    if (!s2)
        return NULL;
    if (!s1)
    {
        str = NULL;
        return (ft_strcpy(str, s2, len));
    }
    str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
    if (!str)
        return NULL;
    i = 0;
    while(s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    free(s1);
    j = 0;
    while(s2[j] && j < len)
    {
        str[i] = s2[j];
        i++;
        j++;
    }
    str[i] = 0;
    return (str);
}

int ft_checklen(char *str, int c)
{
    int i;
    i = 0;
    while(str[i])
    {
        if (str[i] == c)
            break ;
        i++;
    }
    return i;
}

char*   ft_substr(char *str, int i)
{
    int j;
    char *line;

    if (!str)
        return (0);
    line = malloc(sizeof(char) * (i + 1));
    if (!line)
        return 0;
    line[i] = '\0';
    j = 0;
    while(j < i)
    {
        line[j] = str[j];
        j++;
    }
    return (line);
}

char	*get_next_line(int fd)
{
    char *buffer;
    static char *result;
    int b_read;
    char *line;
    static int i;
    int len;
    static int	flag;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return 0;
    if (flag == 1 && !result)
	return (NULL);       	
    buffer = malloc(sizeof(char) * (BUFFER_SIZE) + 1);
    if(!buffer)
        return (NULL);
    b_read = BUFFER_SIZE;
    if (flag == 0)
    {
	    while(b_read > 0)
	    {
		    b_read = read(fd, buffer, BUFFER_SIZE);
		    buffer[b_read] = 0;
		    result = strjoin(result,buffer,b_read);
            if (b_read < 0)
	        {
                free(buffer);
                buffer = NULL;
                return NULL;
	        }
	    }
	    flag = 1;
    }
    free(buffer);
    buffer = NULL;
    len = ft_checklen(&result[i], '\n');
    line = ft_substr(&result[i], len + 1);
    if (flag == 1 && result[i] == '\0')
    {
    	free(result);
        result = NULL;
    }
    i = i + len + 1;
    return (line);
}

int main()
{
	int fd = open("test.txt", O_RDONLY);
	char *line;
   /* get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);*/
    printf("%s", line = get_next_line(fd));
    free(line);
    printf("%s", line = get_next_line(fd));
    free(line);
    printf("%s", line = get_next_line(fd));
    free(line);
    printf("%s", line = get_next_line(fd));
    free(line);
    printf("%s", line = get_next_line(fd));
    free(line);
    printf("%s", line = get_next_line(fd));
    free(line);
	close(fd);
	return (0);
}
