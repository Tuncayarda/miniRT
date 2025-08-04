NAME        = miniRT

PATH_SRC    = src
PATH_OBJ    = obj

SUBDIRS     = main.c

PATH_LIBS	= libs

PATH_LIBFT  = $(PATH_LIBS)/libft
PATH_MLX    = $(PATH_LIBS)/mlx
PATH_MLX_METAL   = $(PATH_LIBS)/mlx/minilibx_metal
PATH_MLX_LINUX   = $(PATH_LIBS)/mlx/minilibx_linux
PATH_MLX_OPENGL  = $(PATH_LIBS)/mlx/minilibx_opengl

LIBFT       = $(PATH_LIBFT)/libft.a

SRC_DIRS    = $(PATH_SRC) $(addprefix $(PATH_SRC)/,$(SUBDIRS))
OBJ_SUBDIRS = $(addprefix $(PATH_OBJ)/,$(SUBDIRS))

BASE_INC_DIRS = inc $(PATH_LIBFT) $(PATH_MLX)
INC_DIRS      = $(addprefix $(PATH_SRC)/,$(SUBDIRS))
PATH_INCLUDE  = $(addprefix -I ,$(BASE_INC_DIRS) $(INC_DIRS))

CFLAGS = #-Wall -Wextra -Werror

SRCS = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

OBJS = $(patsubst $(PATH_SRC)/%, \
                  $(PATH_OBJ)/%, \
                  $(SRCS:.c=.o))

UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)

ifeq ($(UNAME_S),Darwin)
	PATH_MLX := $(PATH_MLX_OPENGL)
else ifeq ($(UNAME_S),Linux)
	PATH_MLX := $(PATH_MLX_LINUX)
endif

MLX        = $(PATH_MLX)/libmlx.a
MLX_FLAGS  = -L$(PATH_MLX) -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(LIBFT):
	@make -C $(PATH_LIBFT)

$(MLX):
	@make -C $(PATH_MLX)

$(PATH_OBJ):
	@mkdir -p $(PATH_OBJ) $(OBJ_SUBDIRS)

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c | $(PATH_OBJ)
	@$(CC) $(CFLAGS) $(PATH_INCLUDE) -o $@ -c $<

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

clean:
	@make -s -C $(PATH_LIBFT) clean
	@$(RM) -r $(PATH_OBJ)

fclean: clean
	@make -s -C $(PATH_LIBFT) fclean
	@$(RM) -r $(NAME)

re: fclean all

update_libs:
	@rm -rf lib
	@git clone https://github.com/Tuncayarda/Libft.git $(PATH_LIBFT)
	@git clone https://github.com/Tuncayarda/minilibx_repo.git $(PATH_MLX)

run_valgrind:
	@valgrind --leak-check=full \
	         --show-leak-kinds=all \
	         ./$(NAME)

.PHONY: all clean fclean re update_libs run_valgrind