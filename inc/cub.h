/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 09:37:40 by abettach          #+#    #+#             */
/*   Updated: 2020/12/10 11:31:15 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "mlx.h"

# define BUFFER_SIZE 4096
# define NUM_MAX 1.79769e+308
# define TEXTURE_WIDTH 64
# define TEXTURE_HIGHT 64
# define SPRITE_HIEGHT 120.
# define SPRITE_WIDTH 64.
# define MKEY_Z 13
# define MKEY_S 1
# define MKEY_A 0
# define MKEY_D 2
# define MKEY_ESC 53
# define MROTATE_LEFT	123
# define MROTATE_RIGHT  124
# define FOV 1.0471975512
# define M_PI2 1.57079632679
# define M_PI3 4.71238898038
# define DR 0.01745329251
# define ROT_SPEED 0.01745329251
# define WALK_SPEED 4
# define TILE_SIZE 64

typedef struct		s_sprxy
{
	double		x;
	double		y;
}					t_sprxy;

typedef struct		s_sprite
{
	int			nbspr;
	double		*h;
	double		*w;
	int			*order;
	double		*dist;
	double		*ang;
	int			drawstarty;
	int			drawstartx;
}					t_sprite;

typedef struct		s_ray
{
	double		pwalldist;
	double		walllineheight;
	double		walllinewidth;
	int			drawstarty;
	int			drawstartx;
	double		corrdist;
	int			x;
	int			texture;
}					t_ray;

typedef struct		s_player
{
	double		horzwallhitx;
	double		horzwallhity;
	double		xstep;
	double		ystep;
	double		xintercept;
	double		yintercept;
	double		nexthorizontaltouchx;
	double		nexthorizontaltouchy;
	int			foundvertwallhit;
	int			foundhorzwallhit;
	double		vertwallhitx;
	double		vertwallhity;
	double		nextverticaltouchx;
	double		nextverticaltouchy;
	double		washitvertical;
	double		px;
	double		py;
	double		dx;
	double		dy;
	double		ang;
	char		facingup;
	char		facingdown;
	char		facingright;
	char		facingleft;

}					t_player;

typedef struct		s_data
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			forward;
	int			back;
	int			left;
	int			right;
	int			rotate_left;
	int			rotate_right;
	int			width;
	int			height;
}					t_data;

typedef struct		s_texture
{
	int			walloffsetx;
	int			walloffsety;
	int			texcolor;
	int			index;
	int			tindex;
}					t_texture;

typedef struct		s_recup
{
	double		num_rays;
	int			rx;
	int			ry;
	int			i;
	int			f;
	int			c;
	double		*sdist;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*sp;
	int			nblines;
	int			sizeline;
	char		**map;
	char		depart;
	int			dx;
	int			dy;
	double		lx;
	double		ly;
	double		hx;
	double		hy;
	double		vx;
	double		vy;
	int			indicateur2;
	int			save;
	int			erreur;
	int			multijoueurs;
	int			lignevide;
	int			insidemap;
	int			count;
	int			count2;
	int			sum;
	int			sum2;
	int			wrongcharmap;
	t_data		texture[5];
	t_ray		r;
	t_texture	t;
	t_data		d;
	t_player	p;
	t_sprite	s;
	t_sprxy		*sxy;
}					t_recup;

int					get_next_line(int fd, char **line, t_recup *recup);
int					ft_free_buff(char **buff, t_recup *recup);
int					ft_eof(int ret, char **buff, char **line);
int					ft_mf(t_recup *recup);
int					ft_murs(t_recup *recup);
int					ft_copy(char **line, char **buff);
int					ft_check(char *str);
int					ft_strlen(char *str);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_subbuff(char *buff, int start, int len);
void				ft_color_resolution(char **str, t_recup *recup);
void				ft_parsing(char *fichier, t_recup *recup);
int					ft_cub(char *str, t_recup *recup);
void				ft_initialisation(t_recup *recup);
void				ft_init_more(t_recup *recup);
int					ft_nb_virgule(const char *str);
int					ft_atoi2(const char *str, t_recup *recup);
int					ft_check_cols(t_recup *m);
int					ft_charinstr(char *str, char c);
void				ft_texture(char *str, t_recup *recup);
void				ft_map(char *str, t_recup *recup);
int					ft_is_map(char *str, t_recup *recup);
int					ft_depart(char c, t_recup *recup, int i, int j);
int					ft_copy_map(char *str, t_recup *recup);
int					ft_parsing_map(char *fichier, t_recup *recup);
int					ft_lignevide(char *str);
int					ft_check_number(t_recup *recup, char *str);
void				ft_init_sprite(t_recup *recup);
void				ft_verify_errors(t_recup *recup);
int					ft_murs(t_recup *recup);
int					ft_murs_util(char *str);
void				ft_error2(t_recup *recu, char *str);
void				ft_error(t_recup *recup, char *str);
void				ft_init(t_recup *recup);
int					ft_check_rows(t_recup *m);
int					ft_charinstr(char *str, char c);
int					ft_lignevide(char *str);
void				ft_verify_errors(t_recup *recup);
int					ft_atoi(const char *str);
void				ft_get_color_f(char *str, t_recup *recup, int i, int j);
void				ft_get_color_c(char *str, t_recup *recup, int i, int j);
int					ft_mlx(t_recup *recup);
int					ft_raycasting(t_recup *recup);
void				ft_swap(t_recup *recup);
int					ft_key_press(int keycode, t_recup *recup);
int					ft_key_release(int keycode, t_recup *recup);
double				ft_normalize_ang(double ang);
void				ft_forward_back(t_recup *recup);
void				ft_left_right(t_recup *recup);
void				ft_rotate_right_left(t_recup *recup);
void				ft_player_look(t_recup *recup, double ang);
double				ft_get_intersection(t_recup *recup, double ang);
double				ft_horizontale_intersection1(t_recup *recup, double ang);
double				ft_verticale_intersection1(t_recup *recup, double ang);
char				haswallat(t_recup *recup, double x, double y);
char				haswallat(t_recup *recup, double x, double y);
int					ft_exit(t_recup *recup);
void				ft_swap3(t_recup *recup);
void				ft_render3dwalls(t_recup *recup);
void				ft_draw_floor_sky(t_recup *recup);
void				ft_init2(t_recup *recup);
void				ft_get_texture(t_recup *recup);
void				ft_save(t_recup *recup);
int					ft_check_save(char *str);
void				ft_sprite(t_recup *recup, int i);
double				ft_snorm(double ang);
void				ft_s_swap(t_recup *recup, int i);
double				dist(double x1, double y1, double x2, double y2);
int					ft_murs2(t_recup *recup);

#endif
