# ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

# include "../gnl/get_next_line.h"

typedef struct s_map
{
	char	**map_array;
	size_t	height;
	size_t	width;
}				t_map;

typedef struct s_data
{
	t_map	*map;

}				t_data;

int		ft_strcmp(char *str1, char *str2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strchr(const char *s, int c);

char	**ft_split(char const *s, char c);

#endif