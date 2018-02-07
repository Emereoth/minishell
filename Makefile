# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acottier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/01 13:55:41 by acottier          #+#    #+#              #
#    Updated: 2017/12/12 18:22:02 by acottier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED				=	\033[31m
GREEN			=	\033[32m
YELLOW			=	\033[33m
NC				=	\033[0m

NAME			=	minishell
LIBNAME			=	libft

SRC_PATH		=	sources
OBJ_PATH		=	objects

SRC_NAMES		=	main.c \
					get_next_line.c \
					prompt.c \
					parse.c \
					binary_check.c \
					pathlist.c \
					builtins.c \
					error.c \
					utilities.c \
					utilities2.c \
					utilities3.c \
					syntax.c \
					env_conversion.c \
					env_modify.c \
					replace_env_commands.c \
					shell_terms.c \
					utilities4.c \
					env_advanced.c \
					utilities5.c

OBJ_NAMES 		=	$(SRC_NAMES:.c=.o)

SRC 			=	$(addprefix $(SRC_PATH)/,$(SRC_NAMES))
OBJ				=	$(addprefix $(OBJ_PATH)/,$(OBJ_NAMES))

FLAGS			=	-g3 -Wall -Wextra -Werror
IFLAGS			=	-Iincludes
LDFLAGS			=	-Llibft
LDLIBS			=	-lft

all :
	@time (make $(NAME)) 2> time.txt
	@printf "${GREEN}Minishell project compilation finished, executable minishell ready : ${NC}"
	@printf "${YELLOW}"
	@cat time.txt | head -2 | tail -1
	@printf "${NC}"
	@rm time.txt

$(NAME) : $(OBJ)
	@make chrono -C $(LIBNAME) && make clean -C $(LIBNAME)
	@gcc $(FLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $@

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH) && gcc $(FLAGS) $(IFLAGS) -o $@ -c $<

clean : 
	@rm -rf $(OBJ_PATH)
	@printf "${RED}Minishell's' object files deleted.${NC}\n"

fclean : clean
	@rm -f $(NAME)
	@printf "${RED}Executable minishell deleted.${NC}\n"

re : fclean all

nolib : fclean
	@(time gcc $(FLAGS) $(IFLAGS) -c $(SRC) && mkdir -p $(OBJ_PATH) && mv $(OBJ_NAMES) $(OBJ_PATH) && gcc $(FLAGS) $(LDFLAGS) $(LDLIBS) $(OBJ) -o $(NAME)) 2> time.txt
	@printf "${GREEN}Minishell project compilation finished, executable minishell ready : ${NC}"
	@printf "${YELLOW}"
	@cat time.txt | head -2 | tail -1
	@printf "${NC}"
	@rm time.txt

noerror : fclean
	gcc $(FLAGS) $(IFLAGS) -c $(SRC)
	mkdir -p $(OBJ_PATH)
	mv $(OBJ_NAMES) $(OBJ_PATH)
	gcc $(FLAGS) $(LDFLAGS) $(LDLIBS) $(OBJ) -o $(NAME)

