#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

int		found_new_line(char *buffer);
size_t	ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*get_new_line(char *buffer);
char	*get_new_buffer(char *buffer);
char	*get_next_line(int fd);

#endif
