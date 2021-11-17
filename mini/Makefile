SRCS =	./Sources/builtin_bis.c\
		./Sources/builtin_ter.c \
		./Sources/builtin.c \
		./Sources/check_error.c \
		./Sources/edit_tab_arg.c \
		./Sources/env_bis.c \
		./Sources/env.c \
		./Sources/free.c \
		./Sources/ft_redirection.c \
		./Sources/ft_redirections_bis.c \
		./Sources/ft_split_pipe.c \
		./Sources/init_count.c \
		./Sources/parse_redir.c \
		./Sources/path.c \
		./Sources/quotes.c \
		./Sources/signals.c \
		./Sources/unsplit.c \
		./Sources/utils.c \
		./utils/ft_atoi.c \
		./utils/ft_bzero.c \
		./utils/ft_count.c \
		./utils/ft_delchar.c \
		./utils/ft_find_char.c \
		./utils/ft_is_alpha.c \
		./utils/ft_is_fill.c \
		./utils/ft_isdigit.c \
		./utils/ft_itoa.c \
		./utils/ft_putendl.c \
		./utils/ft_putstr_fd.c \
		./utils/ft_split_custom.c \
		./utils/ft_split.c \
		./utils/ft_strcat_cd.c \
		./utils/ft_strcat.c \
		./utils/ft_strchr.c \
		./utils/ft_strcmp.c \
		./utils/ft_strcpy.c \
		./utils/ft_strdup.c \
		./utils/ft_strjoin.c \
		./utils/ft_strlen.c \
		./utils/ft_strncmp.c \
		./utils/ft_substr.c \
		parsing.c \

OBJS 		= ${SRCS:.c=.o}

CC 			= gcc
CFLAGS		= -Wall -Wextra -Werror 
READFLAGS   = -lreadline -L /Users/dlescart/.brew/opt/readline/lib -I /Users/dlescart/.brew/opt/readline/include
RM			= rm -f
NAME		= minishell

all: 		${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} 

$(NAME): 	$(OBJS)
			${CC}  $(CFLAGS) -o $(NAME) $(OBJS) $(READFLAGS)

clean:
			${RM} ${OBJS}

fclean: 	clean
			${RM} ${NAME}

re: 		fclean all

.PHONY:		all clean fclean re