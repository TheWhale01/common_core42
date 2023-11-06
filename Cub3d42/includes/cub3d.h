/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:46:45 by jrossett          #+#    #+#             */
/*   Updated: 2022/10/26 10:55:23 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>

# define L 1200
# define H 800
# define ROT_SPEED 0.05
# define MOVE_SPEED 0.05
# define ERR_DIR "This is a directory."
# define ERR_MAP "Invalid map in the file."
# define ERR_FILE "This is not a valid file."
# define ERR_MLX "Failure while creating mlx."
# define ERR_IMG "Failure while creating image."
# define ERR_ELEM "Invalid element in the file."
# define ERR_WIN "Failure while creating mlx_window."
# define ERR_ARGS "The program takes only one argument."
# define ERR_MALLOC "Failure while allocating the heap."
# define ERR_ADDR "Failure while creating images address."
# define ERR_NAME "Invalid name: map shoud be a \"*.cub\" format."

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_elem
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	**f;
	char	**c;
	int		fr;
	int		fg;
	int		fb;
	int		cr;
	int		cg;
	int		cb;
	int		nb_elem;
	int		fcolor;
	int		ccolor;
}	t_elem;

typedef struct s_img
{
	int		len;
	int		bpp;
	int		endian;
	char	*addr;
	void	*img;
	t_pos	pos;
	double	step;
	double	tex_pos;
}	t_img;

typedef struct s_player
{
	int			stepx;
	int			stepy;
	char		player;
	float		speed;
	t_pos		*pos;
}	t_player;

typedef struct s_map
{
	int			nb_player;
	char		**map;
	t_elem		*elem;
}	t_map;

typedef struct s_ray
{
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	int		mapx;
	int		mapy;
}	t_ray;

typedef struct s_renderer
{
	int		side;
	int		drawend;
	int		drawstart;
	int		lineheight;
	double	wallx;
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
}	t_renderer;

typedef struct s_game
{
	int			s;
	int			fd;
	int			size;
	int			left;
	int			right;
	int			t_left;
	int			t_right;
	int			forward;
	int			backward;
	void		*mlx;
	void		*mlx_win;
	t_map		*map;
	t_img		**img;
	t_ray		*ray;
	t_player	*player;
	t_renderer	*renderer;
}	t_game;

int			ft_mid_map(t_game *game);
int			exit_game_v(t_game *game);
int			ft_atoi_2(const char *nptr);
int			ft_verif_elem(t_elem *elem);
int			get_func(t_pos p1, t_pos p2);
int			ft_color2(int r, int g, int b);
int			ft_verif_name(int ac, char **av);
int			ft_parse_elem(int fd, t_elem *elem);
int			do_event(int keycode, t_game *game);
int			stop_event(int keycode, t_game *game);
int			exit_game(t_game *game, char *error, int var);

char		*ft_strdup_2(char *src, char c);
char		**ft_parse_map(int fd, t_map *map, t_player *player);

void		cub3d(t_game *game);
void		get_dist(t_game *game);
void		draw_ray(t_game *game);
void		ft_color(t_elem *elem);
void		ft_perror(char *error);
void		clear_ray(t_game *game);
void		ft_free_tab(char **tab);
void		turn_left(t_game *game);
void		turn_right(t_game *game);
void		launch_ray(t_game *game);
void		init_window(t_game *game);
void		init_player(t_game *game);
void		ft_init_map(t_game *game);
void		move_forward(t_game *game);
void		move_backward(t_game *game);
void		move_sideward(t_game *game);
void		ft_create_img(t_game *game);
void		init_renderer(t_game *game);
void		move_rightward(t_game *game);
void		get_wall_height(t_game *game);
void		ft_ver_img(int i, t_game *game);
void		set_renderer(int column, t_game *game);
void		destroy_mlx(void *mlx, void *ptr, int mode);
void		mlx_put_pixel(t_game *game, int x, int y, int color);
void		display_player(t_game *game, int x, int y, int color);
void		display_square(t_game *game, int x, int y, int color);
void		draw_line(t_game *game, t_pos p1, t_pos p2, int color);
void		exit_msg(t_map *map, t_game *game, int exit_code, char *msg);
void		draw_rectangle(t_game *game, t_pos pos, t_pos dims, int color);

void		*ft_free_map(t_map *map);
void		ft_free_game_2(t_game *game);
void		*ft_free_game(t_game *game, int var);

t_img		*init_img(void);

t_game		*ft_parsing(int ac, char **av);

#endif
