# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cado-car <cado-car@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 21:45:32 by cado-car          #+#    #+#              #
#    Updated: 2023/03/24 12:38:18 by cado-car         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo

#compilation
CC 				= cc
CF 				= -g -Wall -Wextra -Werror

SRC_PATH 		= ./
OBJ_PATH		= ./obj/

SRC				= main.c\
				check_args.c\
				set_table.c\
				start_dinner.c\
				clean_table.c\
				create_philo.c\
				dine.c\
				dine_fts.c\
				reap.c\
				print_log.c\
				utils.c

OBJ				= $(addprefix $(OBJ_PATH), $(notdir $(SRC:.c=.o)))

#rules
$(OBJ_PATH)%.o: %.c
				mkdir -p $(OBJ_PATH)
				$(CC) $(CF) -c $< -o $@

$(NAME):		$(OBJ)
				@printf "$(GR)Objects ready!$(RC)\n"
				@printf "\n$(CY)Generating philosophers executable...$(RC)\n"
				$(CC) $(CF) -o $(NAME) $(OBJ) 
				@printf "$(GR)Done!$(RC)\n\n"

all:			$(NAME)

re:				fclean all

clean:			
				rm -rf $(OBJ) $(OBJ_PATH)
				@printf "$(RE)minishell objects removed!$(RC)\n\n"

fclean:			clean
				rm -rf $(notdir $(NAME))
				@printf "$(RE)Executable removed!$(RC)\n\n"

leak:			all
				valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) 4 510 200 100 5

.PHONY:			all clean fclean re

# Colors
GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m