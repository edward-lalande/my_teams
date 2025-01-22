##
## EPITECH PROJECT, 2024
## B-NWP-400-PAR-4-1-myteams-paul.bardeur
## File description:
## Makefile
##

all:
	make -C server/
	make -C client/
	mv server/myteams_server .
	mv client/myteams_cli .

clean:
	make clean -C server/
	make clean -C client/

fclean:
	make fclean -C server/
	make fclean -C client/
	rm myteams_server
	rm myteams_cli

re:
	make re -C server/
	make re -C client/
	mv server/myteams_server .
	mv client/myteams_cli .

.PHONY: all clean fclean re
