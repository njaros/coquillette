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
			traitement_signaux.c \
			libft_ajout1.c
LST_OBJS = ${LST_SRCS:.c=.o}
LST_INCLUDES =	coquillette.h \
				libft.h
SRC = $(addprefix ${PATH_SRCS}/,${LST_SRCS})
OBJS = $(addprefix ${PATH_OBJS}/,${LST_OBJS})
INCLUDES = $(addprefix ${PATH_INCLUDES}/,${LST_INCLUDES})

## LES REGLES DE COMPILATION DU PROGRAMME ##

all :				lib_libft ${LIB} ${NAME} Makefile

${NAME} :			${OBJS}
					${CC} ${FLAGS} ${OBJS} ${LIB} -lreadline -o $@

${PATH_OBJS}/%.o:	${PATH_SRCS}/%.c ${INCLUDES} ${LIB} Makefile | ${PATH_OBJS}
					${CC} ${FLAGS} -c $< -o $@ -I ${PATH_INCLUDES}

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
					rm ${NAME}

re:					fclean all

## LE TRUC ##

.PHONY: all re clean fclean

## FIN ##