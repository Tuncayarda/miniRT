NAME			= miniRT

PATH_SRC		= src
PATH_OBJ		= obj

SUBDIRS			=  _gc vector parser entities util debug mlx_interface render color

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


SRCS			= $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

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

CFLAGS		= -Wall -Wextra -O3 -ffast-math -flto -fno-math-errno -march=native -mtune=native #Werror

MLX			= $(PATH_MLX)/libmlx.a

all: $(NAME)

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