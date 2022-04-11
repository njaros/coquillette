# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: njaros <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 15:17:57 by njaros            #+#    #+#              #
#    Updated: 2022/03/08 17:00:47 by njaros           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

## COMMANDES BASH

PATH_RL = $(shell brew --prefix readline)

## LES INCONTOURNABLES ##

NAME = minishell
CC = gcc
FLAGS = ##-Werror -Wextra -Wall

## LES CHEMINS ##

PATH_SRCS = src/
PATH_OBJS = obj/
PATH_INCLUDES = includes/

## LES CHEMINS DES LIBRAIRIES ##

LIB =	libft/libft.a

## LES SOURCES, OBJETS et INCLUDES ##

LST_SRCS =	coquillette.c	\
			coquillette_utils1.c	\
			traitement_signaux.c \
			parsing/quote_dollars.c	\
			parsing/quote_dollars2.c	\
			parsing/quote_dollars3.c	\
			parsing/analyse.c	\
			parsing/analyse2.c	\
			parsing/quote_doll_handler.c \
			parsing/quote_doll_handler2.c \
			parsing/analyse_utils.c	\
			parsing/chevron.c	\
			parsing/freeteuse.c	\
			execution/execution.c	\
			execution/exec_utils.c	\
			builtins/built_cd.c	\
			builtins/built_echo.c	\
			builtins/built_env.c	\
			builtins/built_exit.c	\
			builtins/built_export.c	\
			builtins/built_pwd.c	\
			builtins/built_unset.c
LST_OBJS = ${LST_SRCS:.c=.o}
LST_INCLUDES =	coquillette.h	\
				libft.h
SRC = $(addprefix ${PATH_SRCS},${LST_SRCS})
OBJS = $(addprefix ${PATH_OBJS},${LST_OBJS})
INCLUDES = $(addprefix ${PATH_INCLUDES},${LST_INCLUDES})
OBJ_DIR = $(sort $(dir $(OBJS)))

## CHEMINS NON INCLUS DANS ENV

READLINE_INC	=	-I $(PATH_RL)/include
READLINE_LIB	=	-L $(PATH_RL)/lib

## LES REGLES DE COMPILATION DU PROGRAMME ##

all :				lib_libft ${LIB} ${NAME} Makefile

${NAME} :			${OBJS}
					${CC} ${FLAGS} ${OBJS} $(READLINE_LIB) ${LIB} -lreadline -o $@

${PATH_OBJS}%.o:	${PATH_SRCS}%.c ${INCLUDES} ${LIB} Makefile
					${CC} ${FLAGS} $(READLINE_INC) -c $< -o $@ -I ${PATH_INCLUDES}

${OBJS}:	| ${OBJ_DIR}

${OBJ_DIR}:
			mkdir -p $@

## LES REGLES DE COMPILATION DES LIBRAIRIES ##

${LIB}:				lib_libft

lib_libft:
					$(MAKE) -C libft/

## LES REGLES DE SUPPRESSION ET RE ##

clean:
					rm -rf ${PATH_OBJS}
					$(MAKE) clean -C libft/

fclean:				clean
					rm -f ${NAME}
					$(MAKE) fclean -C libft/

re:					fclean all

## LE TRUC ##

.PHONY: all lib_libft clean fclean re

## FIN ##