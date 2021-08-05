# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nkuipers <nkuipers@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/06/03 13:39:02 by nkuipers      #+#    #+#                  #
#    Updated: 2021/08/05 14:39:32 by nkuipers      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			= philo

SRCS            =   main.c errors_and_messages.c input.c spaghetti.c utils.c
CFILES          =   $(SRCS:%=src/%)
OFILES          =   $(CFILES:.c=.o)
CFLAGS          =   -Wall -Wextra -Werror

# COLORS
ifeq ($(WSL_DISTRO_NAME), Ubuntu)
	WHITE   = \e[37;01m
	CYAN    = \e[36;01m
	PINK    = \e[35;01m
	BLUE    = \e[34;01m
	YELLOW  = \e[33;01m
	GREEN   = \e[32;01m
	RED     = \e[31;01m
	BLACK   = \e[30;01m
	RESET   = \e[0m
else
	WHITE   = \x1b[37;01m
	CYAN    = \x1b[36;01m
	PINK    = \x1b[35;01m
	BLUE    = \x1b[34;01m
	YELLOW  = \x1b[33;01m
	GREEN   = \x1b[32;01m
	RED     = \x1b[31;01m
	BLACK   = \x1b[30;01m
	RESET   = \x1b[0m
endif

all: $(NAME)

$(NAME): $(OFILES)
	@echo "$(WHITE)/-----      Compiling philo    -----\\ $(RESET)"
	@gcc $(CFLAGS) $(OFILES) -o $(NAME) -pthread
	@echo "$(GREEN) Compiling completed. Name of executable is 'philo' $(RESET)"

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@ -g

clean:
	@echo "$(WHITE)/-----      Cleaning up...     -----\\ $(RESET)"
	@rm -f $(OFILES)
	@echo "$(WHITE)               Done"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
