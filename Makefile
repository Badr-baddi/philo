NAME    = philo

CC      = cc -Wall -Wextra #-Werror #-g -fsanitize=address

#CFLAGS  = -I$(HOME)/.local/include

SRCS    = main.c parss.c ft_atoi.c parss_1.c ft_init.c ft_usleep.c ft_strcmp.c ft_think.c ft_eat.c ft_dream.c
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