##
## EPITECH PROJECT, 2024
## B-NWP-400-PAR-4-1-myteams-paul.bardeur
## File description:
## Makefile
##

CXX			=	gcc
CXXFLAGS	+=	-Wall -Wextra -Werror -luuid
CPPFLAGS	+=	-iquote $(INC_DIR) -iquote ../libs/myteams
TTFLAGS		=	-lcriterion --coverage

SRC_DIR		=	./src
INC_DIR		=	./includes
TEST_DIR	=	./tests

LIB			=	-L../libs/myteams -lmyteams

MAIN		=	$(SRC_DIR)/main.c

SRC			=	$(SRC_DIR)/server.c					\
				$(SRC_DIR)/usage.c					\
				$(SRC_DIR)/get_server.c				\
				$(SRC_DIR)/close_server.c			\
				$(SRC_DIR)/listen_server.c			\
				$(SRC_DIR)/set_clients.c			\
				$(SRC_DIR)/check_connection.c		\
				$(SRC_DIR)/check_command.c			\
				$(SRC_DIR)/save_server.c			\
				$(SRC_DIR)/send_message.c			\
				$(SRC_DIR)/display_message.c		\
				$(SRC_DIR)/get_info.c				\
				$(SRC_DIR)/array.c					\
				$(SRC_DIR)/commands/help.c			\
				$(SRC_DIR)/commands/login.c			\
				$(SRC_DIR)/commands/logout.c		\
				$(SRC_DIR)/commands/users.c			\
				$(SRC_DIR)/commands/user.c			\
				$(SRC_DIR)/commands/send.c			\
				$(SRC_DIR)/commands/messages.c		\
				$(SRC_DIR)/commands/use.c			\
				$(SRC_DIR)/commands/create.c		\
				$(SRC_DIR)/commands/sub_create.c	\
				$(SRC_DIR)/commands/list.c 			\
				$(SRC_DIR)/commands/subscribe.c		\
				$(SRC_DIR)/commands/subscribed.c	\
				$(SRC_DIR)/commands/list.c			\
				$(SRC_DIR)/commands/info.c			\
				$(SRC_DIR)/commands/unsubscribe.c	\

SRC_TEST	=	$(TEST_DIR)/test.c					\

SRC_OBJ		=	$(SRC:.c=.o)						\
				$(MAIN:.c=.o)

BIN_NAME	=	./myteams_server
TEST_NAME	=	./unit_tests

all:	$(BIN_NAME)

$(BIN_NAME): $(SRC_OBJ)
	$(CXX) -o $@ $^ $(CPPFLAGS) $(CXXFLAGS) $(LIB) -g3

tests_run: $(SRC_TEST) $(SRC)
	$(CXX) -o $(TEST_NAME) $(SRC) $(SRC_TEST) $(CPPFLAGS) $(TTFLAGS) $(LIB)
	./unit_tests

coverage: tests_run
	@ gcovr --exclude "tests/*"

clean:
	@ $(RM) $(SRC_OBJ)
	@ $(RM) *.gcda *.gcno
	@ $(RM) vgcore*

fclean: clean
	@ $(RM) $(BIN_NAME)
	@ $(RM) $(TEST_NAME)

re: fclean all

.PHONY: all tests_run coverage clean fclean re
