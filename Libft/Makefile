NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude
SRC_DIR = src
SRC_DIR_B = src_b
OBJ_DIR = obj
OBJ_DIR_B = obj_b
FILES = ft_isdigit.c \
		ft_isalpha.c \
		ft_isprint.c \
		ft_isascii.c \
		ft_isalnum.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strncmp.c \
		ft_memcmp.c \
		ft_atoi.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_split.c \
		ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_memcpy.c \
		ft_bzero.c \
		ft_memset.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_calloc.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_strnstr.c \
		ft_putstr.c \
		ft_convert_hex_ptr.c \
		ft_convert_hex.c \
		ft_printf.c \
		ft_putnbr.c \
		print0.c \
		print1.c \
		printf_is_valid.c \
		get_next_line.c \
		get_next_line_utils.c

BOBO = .bonus
BONUS = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

OBJS = $(addprefix $(OBJ_DIR)/,$(FILES:%.c=%.o))
SRCS = $(addprefix $(SRC_DIR)/, $(FILES))
OBJS_B = $(addprefix $(OBJ_DIR_B)/,$(BONUS:%.c=%.o))

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
		$(CC) $(CFLAGS) -I. -c $< -o $@

$(OBJ_DIR_B)/%.o : $(SRC_DIR_B)/%.c
		@mkdir -p $(OBJ_DIR_B)
		$(CC) $(CFLAGS) -I. -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus : $(BOBO)

$(BOBO) : $(OBJS_B)
	ar rcs $(NAME) $(OBJS_B)
	touch $(BOBO)

clean :
	rm -f -r $(OBJ_DIR) $(OBJ_DIR_B)
	
fclean : clean 
	rm -f $(NAME)

re : clean fclean all
 	
.PHONY : fclean clean re all bonus
 
