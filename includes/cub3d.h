# ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

# include "macro.h"
# include "../gnl/get_next_line.h"
# include "../mlx_linux/mlx.h"

typedef struct s_map
{
	char	**map_array;
	size_t	height;
	size_t	width;
}				t_map;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	*map;
}				t_data;

int		ft_strcmp(char *str1, char *str2);
int		ft_strncmp(char *s1, char *s2, size_t n);

char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s);

char	**ft_split(char *s, char c);

#endif