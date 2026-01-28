NAME			= miniRT

PATH_SRC		= src
PATH_OBJ		= obj

SUBDIRS			=  _gc vector parser entities util mlx_interface render color

PATH_LIBS		= libs

PATH_LIBFT		= $(PATH_LIBS)/libft
PATH_MLX		= $(PATH_LIBS)/mlx
PATH_MLX_METAL	= $(PATH_LIBS)/mlx/minilibx_metal
PATH_MLX_LINUX	= $(PATH_LIBS)/mlx/minilibx_linux
PATH_MLX_OPENGL	= $(PATH_LIBS)/mlx/minilibx_opengl
PATH_GNL		= $(PATH_LIBS)/gnl

LIBFT			= $(PATH_LIBFT)/libft.a
GNL				= $(PATH_GNL)/get_next_line.a

SRC_DIRS		= $(PATH_SRC) $(addprefix $(PATH_SRC)/,$(SUBDIRS))
OBJ_SUBDIRS		= $(addprefix $(PATH_OBJ)/,$(SUBDIRS))

BASE_INC_DIRS	= inc $(PATH_LIBFT) $(PATH_GNL) $(PATH_MLX)
INC_DIRS		= $(addprefix $(PATH_SRC)/,$(SUBDIRS))
PATH_INCLUDE	= $(addprefix -I ,$(BASE_INC_DIRS) $(INC_DIRS))

SRCS			= \
	src/main.c \
	src/_gc/gc.c \
	src/color/color_add.c \
	src/color/color_modul.c \
	src/color/color_scale.c \
	src/entities/add_entity.c \
	src/entities/add_light.c \
	src/entities/generate_entity.c \
	src/mlx_interface/hook_util.c \
	src/mlx_interface/key_hook.c \
	src/mlx_interface/put_pix.c \
	src/mlx_interface/destroy.c \
	src/parser/open_texture.c \
	src/parser/parse_amb_light.c \
	src/parser/parse_cam.c \
	src/parser/parse_cylinder.c \
	src/parser/parse_light.c \
	src/parser/parse_mat.c \
	src/parser/parse_plane.c \
	src/parser/parse_skybox.c \
	src/parser/parse_sphere.c \
	src/parser/parser.c \
	src/render/check_hit.c \
	src/render/compute_checker.c \
	src/render/compute_diffuse.c \
	src/render/compute_specular.c \
	src/render/compute_texture.c \
	src/render/compute_uv.c \
	src/render/define_closest.c \
	src/render/generate_ray.c \
	src/render/get_closest.c \
	src/render/hit_circle.c \
	src/render/hit_cylinder.c \
	src/render/hit_plane.c \
	src/render/hit_sphere.c \
	src/render/is_reacheable.c \
	src/render/render.c \
	src/render/sample_skybox.c \
	src/render/solve_quadratic.c \
	src/render/trace_ray.c \
	src/util/raise_error.c \
	src/vector/vec_add.c \
	src/vector/vec_add3.c \
	src/vector/vec_cross.c \
	src/vector/vec_dot.c \
	src/vector/vec_gen.c \
	src/vector/vec_length.c \
	src/vector/vec_negate.c \
	src/vector/vec_norm.c \
	src/vector/vec_scale.c \
	src/vector/vec_sub.c

OBJS			= $(patsubst $(PATH_SRC)/%, \
					$(PATH_OBJ)/%, \
					$(SRCS:.c=.o))

UNAME_S			= $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	PATH_MLX    := $(PATH_MLX_OPENGL)
	MLX_FLAGS   = -L$(PATH_MLX) -lmlx -framework OpenGL -framework AppKit
	CFLAGS      += -I/opt/X11/include -I/usr/X11/include
else ifeq ($(UNAME_S),Linux)
	PATH_MLX    := $(PATH_MLX_LINUX)
	MLX_FLAGS   = -L$(PATH_MLX) -lmlx -lXext -lX11 -lm -lz
	CFLAGS      += -I/usr/include -I/usr/include/X11
endif

REL_FLAGS  := -O3 -ffast-math -flto -fno-math-errno -march=native -mtune=native
DBG_FLAGS  := -O0 -g3
ASAN_FLAGS := -fsanitize=address -fno-omit-frame-pointer

CFLAGS     = -Wall -Wextra -Werror
LDFLAGS    =

ifeq ($(OPT),1)
	CFLAGS  += $(REL_FLAGS)
	LDFLAGS += -flto
endif

ifeq ($(ASAN),1)
  CFLAGS   = -Wall -Wextra $(DBG_FLAGS) $(ASAN_FLAGS)
  LDFLAGS  = $(ASAN_FLAGS)
endif

MLX			= $(PATH_MLX)/libmlx.a

all: $(NAME)

debug:
	@$(MAKE) clean
	@$(MAKE) ASAN=1

release:
	@$(MAKE) clean
	@$(MAKE) OPT=1

$(LIBFT):
	@echo ">> Building libft"
	@make -s -C $(PATH_LIBFT)

$(GNL):
	@echo ">> Building get_next_line"
	@make -s -C $(PATH_GNL)

$(MLX):
	@echo ">> Building mlx"
	@make -s -C $(PATH_MLX) > /dev/null 2>&1

$(PATH_OBJ):
	@echo ">> Creating object directories"
	@mkdir -p $(PATH_OBJ) $(OBJ_SUBDIRS)

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c | $(PATH_OBJ)
	@echo ">> Compiling $<"
	@$(CC) $(CFLAGS) $(PATH_INCLUDE) -o $@ -c $<

$(NAME): $(LIBFT) $(MLX) $(GNL) $(OBJS)
	@echo ">> Linking executable $(NAME)"
	@$(CC) $(LDFLAGS) $(OBJS) $(LIBFT) $(GNL) $(MLX_FLAGS) -o $(NAME)
	@echo "M I N I - R T"

clean:
	@echo ">> Cleaning object files"
	@make -s -C $(PATH_LIBFT) clean
	@make -s -C $(PATH_GNL) clean
	@make -s -C $(PATH_MLX) clean
	@$(RM) -r $(PATH_OBJ)

fclean: clean
	@echo ">> Performing full clean"
	@make -s -C $(PATH_LIBFT) fclean
	@make -s -C $(PATH_GNL) fclean
	@$(RM) -r $(MLX)
	@$(RM) -r $(NAME)

re: fclean all

update_libs:
	@echo ">> Updating libraries..."
	@rm -rf libs
	@git clone https://github.com/Tuncayarda/Libft.git libs/libft
	@git clone https://github.com/Tuncayarda/minilibx_repo.git libs/mlx
	@git clone https://github.com/Tuncayarda/Get_next_line.git libs/gnl

run_valgrind:
	@echo ">> Running valgrind..."
	@valgrind --leak-check=full \
	         --show-leak-kinds=all \
	         ./$(NAME)

.PHONY: all clean fclean re update_libs run_valgrind