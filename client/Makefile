##
## EPITECH PROJECT, 2024
## B-NWP-400-PAR-4-1-myteams-paul.bardeur
## File description:
## Makefile
##

LIB	=	-L../libs/myteams -lmyteams

SRC	=	./src/main.c							\
		./src/print_usage.c						\
		./src/teams_client.c					\
		./src/init_teams_client.c				\
		./src/search_commands.c					\
		./src/my_str_to_word_array.c			\
		./src/catch_sigpipe.c					\
		./src/catch_sigsev.c					\
		./src/catch_sigint.c					\
		./src/send_and_print_server_response.c	\
		./src/arrlen.c							\
		./src/display_prompt.c					\
		./src/commands/help.c					\
		./src/commands/exit_cli.c				\
		./src/commands/login.c					\
		./src/commands/logout.c					\
		./src/commands/clear.c					\
		./src/commands/user.c					\
		./src/commands/users.c					\
		./src/commands/subscribe.c				\
		./src/commands/subscribed.c				\
		./src/commands/unsubscribe.c			\
		./src/commands/create.c					\
		./src/commands/use.c					\
		./src/commands/list.c					\
		./src/commands/info.c					\
		./src/commands/send.c					\
		./src/commands/messages.c				\

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror

CPPFLAGS	=	-iquote ./includes -iquote ../libs/myteams

NAME	=	myteams_cli

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(CPPFLAGS) $(LIB)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)
	$(RM) *.gcno
	$(RM) *.gcda

re:	fclean all

.PHONY: all clean fclean re
