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

PATH_SRCS = src
PATH_OBJS = obj
PATH_INCLUDES = includes

## LES CHEMINS DES LIBRAIRIES ##

LIB =	libft/libft.a \

## LES SOURCES, OBJETS et INCLUDES ##

LST_SRCS =	coquillette_utils1.c \
			coquillette.c \
			quote_dollars.c \
			quote_dollars2.c \
			quote_dollars3.c \
			analyse.c \
			analyse2.c \
			analyse_utils.c \
			chevron.c \
			freeeuse.c \
			execpipe.c \
			traitement_signaux.c \
			libft_ajout1.c \
			pipe.c \
			pipe_utils.c
LST_OBJS = ${LST_SRCS:.c=.o}
LST_INCLUDES =	coquillette.h \
				libft.h
SRC = $(addprefix ${PATH_SRCS}/,${LST_SRCS})
OBJS = $(addprefix ${PATH_OBJS}/,${LST_OBJS})
INCLUDES = $(addprefix ${PATH_INCLUDES}/,${LST_INCLUDES})

## CHEMINS NON INCLUS DANS ENV

READLINE_INC	=	-I $(PATH_RL)/include
READLINE_LIB	=	-L $(PATH_RL)/lib

## LES REGLES DE COMPILATION DU PROGRAMME ##

all :				lib_libft ${LIB} ${NAME} Makefile

${NAME} :			${OBJS}
					${CC} ${FLAGS} ${OBJS} $(READLINE_LIB) ${LIB} -lreadline -o $@

${PATH_OBJS}/%.o:	${PATH_SRCS}/%.c ${INCLUDES} ${LIB} Makefile | ${PATH_OBJS}
					${CC} ${FLAGS} $(READLINE_INC) -c $< -o $@ -I ${PATH_INCLUDES}

${PATH_OBJS}:
					mkdir obj

## LES REGLES DE COMPILATION DES LIBRAIRIES ##

${LIB}:				lib_libft

lib_libft:
					make -C ./libft

## LES REGLES DE SUPPRESSION ET RE ##

clean:
					make clean -C ./libft
					rm -rf obj

fclean:				clean
					make fclean -C ./libft
					rm -f ${NAME}

re:					fclean all

## LE TRUC ##

.PHONY: all re clean fclean

## FIN ##