NAME = pipex

#########
RM = rm -f
CC = cc
CFLAGS = -Werror -Wextra -Wall #-g -fsanitize=address
#########

#########
FILES = main init dups exit
FILES_BONUS = main_bonus init_bonus dups_bonus exit_bonus get_next_line_bonus get_next_line_utils_bonus

SRC = $(addsuffix .c, $(FILES))
SRC_BONUS = $(addsuffix .c, $(FILES_BONUS))

vpath %.c srcs srcs_bonus
#########

#########
OBJ_DIR = objs
OBJ_DIR_BONUS = objs_bonus
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEP = $(addsuffix .d, $(basename $(OBJ)))
OBJ_BONUS = $(addprefix $(OBJ_DIR_BONUS)/, $(SRC_BONUS:.c=.o))
DEP_BONUS = $(addsuffix .d, $(basename $(OBJ_BONUS)))
#########

########
LIBFT_DIR = inc/libft
LIBFT_FLAGS = -L$(LIBFT_DIR)
########


#########
$(OBJ_DIR)/%.o: %.c	
	@mkdir -p $(@D)
	${CC} $(CFLAGS) -Ilibft -MMD -c $< -o $@

$(OBJ_DIR_BONUS)/%.o: %.c	
	@mkdir -p $(@D)
	${CC} $(CFLAGS) -Ilibft -MMD -c $< -o $@

all:
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	$(MAKE) $(NAME) --no-print-directory

bonus:
	$(MAKE) BONUS=1 all

ifndef BONUS

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) inc/libft/libft.a -o $(NAME)
	@echo "EVERYTHING DONE  "

else

$(NAME): $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT_FLAGS) inc/libft/libft.a -o $(NAME)
	@echo "EVERYTHING DONE (BONUS)  "

endif

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(OBJ) $(DEP) $(OBJ_BONUS) $(DEP_BONUS) 
	$(RM) -r $(OBJ_DIR) $(OBJ_DIR_BONUS) 
	@echo "OBJECTS REMOVED   "

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)	
	$(RM) $(NAME) 
	@echo "EVERYTHING REMOVED   "

re:	fclean all

.PHONY: all clean fclean re bonus

-include $(DEP)
-include $(DEP_BONUS)

#########
