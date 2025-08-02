NAME    = philo

CC      = cc -Wall -Wextra -Werror -g -fsanitize=thread

#CFLAGS  = -I$(HOME)/.local/include

SRCS    = main.c parss.c ft_atoi.c parss_1.c ft_usleep.c ft_strcmp.c init_tab.c init_tab1.c \
		routine.c create_threads.c mounitor.c clean.c
OBJS    = $(SRCS:.c=.o)

HEADER = minishell.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(READLINE_LINK) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(READLINE_COMPILE) -c $< -o $@ 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all