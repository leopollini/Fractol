# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/24 20:15:20 by lpollini          #+#    #+#              #
#    Updated: 2023/07/01 15:40:08 by lpollini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fractol.a
PROGRAM		= fract'ol
SRCSDIR		= src
OBJSDIR		= objs
INCLUDES	= .
MAIN		= main.c

SRCS		= color_manager.c \
input.c \
main_renderer.c \
utils.c \
main.c

OBJS			= $(SRCS:.c=.o)

# Compiler options
CC			= gcc
MINILIBX_FLAGS		=	-Lmlx -lmlx -I/usr/include -Imlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
CFLAGS		= -Wall -Wextra -Werror

###################################################
# The rest is done by the MakeFile automatically, #
# you should not have to modify it				  #
###################################################

OBJS		= $(SRCS:%.c=$(OBJSDIR)/%.o)

all: fclean libmake $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $@"
	@ar rc $(NAME) $(OBJS)
	@echo "Done!"
	@echo "Now building program..."
	@gcc $(CFLAGS) src/$(MAIN) fractol.a mlx/libmlx.a -o "$(PROGRAM)" $(MINILIBX_FLAGS)
	@echo "Done!"

libmake:
	@make -C mlx/

$(OBJS): $(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@


clean:
	rm -rf $(OBJSDIR)

fclean: clean
	rm -rf $(NAME)
	rm -rf "$(PROGRAM)"
	
aclean:
	rm -rf $(NAME)

re: fclean all



test: all
	./"$(PROGRAM)"

.PHONY: all clean fclean re test
