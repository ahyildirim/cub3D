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


typedef struct s_vectori
{
	int	x;
	int	y;
}				t_vectori;

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

typedef struct s_draw
{
	int			line_height;
	int			color;
	int			wall;
	double 		wall_x;
	double		step;
	double		tex_pos;
	double		perp_wall_dist;
	t_vectori	tex;
	t_vectori	start;
}				t_draw;

typedef struct s_raycast
{
	int			hit;
	int			horizontal;
	t_draw		draw;
	t_vectord	dir;
	t_vectord	pos;
	t_vectord	plane;
	t_vectord	raydir;
	t_vectord	sidedist;
	t_vectord	deltadist;
	t_vectord	step;
	t_vectori	map;
}				t_raycast;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			map_width; //Hiçbir işlevi yok, Silince segfault yiyor wtf amk?
	t_onkey		onkey;
	t_map		*map;
	t_player	*player;
	t_img		*img;
	t_texture	texture;
	t_img		minimap;
}				t_data;

int		create_map(t_data *data, char *map_name);
int		check_map(char **map);
int 	normalize_map(char **map, int width);
int		initialize(t_data *data, char **av);
int		initialize_player(t_data *data);
int		key_up(int keycode, t_data *data);
int		key_down(int keycode, t_data *data);
int		quit_game(t_data *data);
int		create_textures(t_data *data, char *path);
int 	move(t_data *data);

void	draw(t_data *data);
void	fill_texture(t_raycast *ray, t_data *data, int i);

t_raycast	create_ray(t_raycast *ray, t_data *data);
t_raycast	calc_ray_len(t_raycast *ray, t_data *data);
t_raycast	*calc_sidedist(t_raycast *ray);

char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s);
char	*ft_strndup(char *str, size_t n);
char	**ft_split(char *s, char c);

int		ft_strcmp(char *str1, char *str2);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_atoi(char *str);


void	*ft_memmove(void *dest, const void *src, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t n);



#endif