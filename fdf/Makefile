# COMMANDS #
CC			= clang
CFLAGS		= -Wall -Wextra -Werror -g -fsanitize=address
RM			= rm -f
RM_DIR		= rm -rf

# DIRECTORIES #
SRC_DIR		= src
OBJ_DIR		= objects
INC_DIR		= includes
LIB_DIR		= libft
MLX_DIR		= MLX42
BUILD_DIR	= build

# LIBRARIES #
LIBFT		= libft.a
MLX			= libmlx42.a
GLFW		= glfw

# NAME #
NAME		= fdf
CAP_NAME	= $(shell echo $(NAME) | awk '{print toupper(substr($$0, 1, 1)) substr($$0, 2)}')

# NORMAL #
SRC_NAME	= fdf.c init.c image.c draw.c color.c coordinates.c error.c
OBJ_NAME	= $(notdir $(SRC_NAME:.c=.o))
SRCS		= $(addprefix $(SRC_DIR)/,$(SRC_NAME))
OBJS		= $(addprefix $(OBJ_DIR)/,$(OBJ_NAME))

# BONUS #
BONUS_SRC_NAME	= fdf_bonus.c init_bonus.c image_bonus.c draw_bonus.c color_bonus.c coordinates_bonus.c error_bonus.c
BONUS_OBJ_NAME	= $(notdir $(BONUS_SRC_NAME:.c=.o))
BONUS_SRCS		= $(addprefix $(SRC_DIR)/,$(BONUS_SRC_NAME))
BONUS_OBJS		= $(addprefix $(OBJ_DIR)/,$(BONUS_OBJ_NAME))

# COLORS #
C_GREEN		= \033[0;32m
C_RED		= \033[0;31m
C_BLUE		= \033[0;34m
C_DEF		= \033[0m


###############################################################################
# ====================== # Makefile done by mzurera- # ====================== #
###############################################################################


all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(SRC_DIR)
	@mkdir -p $(INC_DIR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -I $(MLX_DIR)/include -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(NAME): $(OBJS)
	@echo "$(C_BLUE)Builing $(NAME)...$(C_DEF)"
	@echo "$(C_BLUE)Compiling $(MLX_DIR)$(C_DEF)"
	@cmake -S $(MLX_DIR) -B build
	@make -s -C $(MLX_DIR)/$(BUILD_DIR) -j4
	@echo "$(C_GREEN)$(MLX_DIR) compiled!$(C_DEF)"
	@make all -s -C ./$(LIB_DIR)/
	@$(CC) $(CFLAGS) $(OBJS) -L./$(LIB_DIR) ./$(LIB_DIR)/$(LIBFT) -L./$(MLX_DIR)/$(BUILD_DIR) ./$(MLX_DIR)/$(BUILD_DIR)/$(MLX) -ldl -l$(GLFW) -pthread -lm -o $(NAME)
	@echo "$(C_GREEN)$(CAP_NAME) built and ready to go!$(C_DEF)"

clean:
	@$(RM_DIR) $(OBJ_DIR)
	@$(RM_DIR) $(BUILD_DIR)
	@make fclean -s -C $(LIB_DIR)
	@make -s -C $(MLX_DIR)/build clean
	@echo "$(C_RED)Cleaned objects folder!$(C_DEF)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@echo "$(C_RED)Cleaned $(NAME) program!$(C_DEF)"

re: fclean all

bonus: $(BONUS_OBJS)
	@echo "$(C_BLUE)Builing $(NAME)...$(C_DEF)"
	@echo "$(C_BLUE)Compiling $(MLX_DIR)$(C_DEF)"
	@cmake -S $(MLX_DIR) -B build
	@make -s -C $(MLX_DIR)/$(BUILD_DIR) -j4
	@echo "$(C_GREEN)$(MLX_DIR) compiled!$(C_DEF)"
	@make all -s -C ./$(LIB_DIR)/
	@$(CC) $(CFLAGS) $(BONUS_OBJS) -L./$(LIB_DIR) ./$(LIB_DIR)/$(LIBFT) -L./$(MLX_DIR)/$(BUILD_DIR) ./$(MLX_DIR)/$(BUILD_DIR)/$(MLX) -ldl -l$(GLFW) -pthread -lm -o $(NAME)
	@echo "$(C_GREEN)$(CAP_NAME) built and ready to go!$(C_DEF)"

.PHONY: all bonus clean fclean re .c.o
