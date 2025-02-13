# ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
#include <stdbool.h>
# include <X11/keysym.h>

# include "macro.h"
# include "../gnl/get_next_line.h"
# include "../mlx_linux/mlx.h"

typedef struct s_vectord
{
	double	x;
	double	y;
}				t_vectord;

typedef struct s_player
{
	t_vectord	pos;
	t_vectord	dir;
	t_vectord	plane;
	float		angle;
	int			l_rotate;
	int			r_rotate;
}				t_player;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_texture
{
	int		top;
	int		bottom;
	t_img	*xpm[4];
}				t_texture;

typedef struct s_onkey
{
	int	key_w;
	int	key_a;
	int	key_s;
	int	key_d;
	int	key_up;
	int	key_down;
	int	key_left;
	int	key_right;
}				t_onkey;

typedef struct s_map
{
	char	**map_array;
	size_t	height;
	size_t	width;
	int		players;
}				t_map;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_onkey		onkey;
	t_map		*map;
	t_player	*player;
	t_img		*img;
	t_texture	texture;
}				t_data;

bool	touch(float px, float py, t_data *data);

int		ft_strcmp(char *str1, char *str2);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_atoi(char *str);
int		create_map(t_data *data, char *map_name);
int		check_map(char **map);
int 	normalize_map(char **map, int width);
int		initialize(t_data *data, char **av);
int		initialize_player(t_data *data);
int		key_up(int keycode, t_data *data);
int		key_down(int keycode, t_data *data);
int		quit_game(t_data *data);
int		create_textures(t_data *data, char *path);

float	fixed_dist(float x1, float y1, float x2, float y2, t_data *data);

char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s);
char	*ft_strndup(char *str, size_t n);

char	**ft_split(char *s, char c);

void	*ft_memmove(void *dest, const void *src, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	move_player(t_data *data);
void	clear_img(t_data *data);
void	draw_square(int x, int y, int size, int color, t_data *data);
void	draw_line(t_player *player, t_data *data, float start_x, int i);
void    put_pixel(int x, int y, int color, t_data *data);
int		render_frame(t_data *data);

//debug
void    draw_map(t_data *data);
void	draw_square(int x, int y, int size, int color, t_data *data);


#endif