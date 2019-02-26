# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osloboda <osloboda@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/11 16:04:13 by osloboda          #+#    #+#              #
#    Updated: 2019/02/26 17:10:24 by osloboda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = osloboda.filler

VNAME = visualizer

INCDIR = includes/

SRC = filler.c solver.c additional_f.c

VSRC = main.c

OBJDIR = objects

VOBJDIR =  visual_objects

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

VOBJ = $(addprefix $(VOBJDIR)/, $(VSRC:.c=.o))

LIB = libft/libft.a

FLAGS = -Wall -Werror -Wextra

UNAME_S = $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		SDL_HEADERS = -I ./frameworks/SDL2.framework/Headers \
					-I ./frameworks/SDL2_ttf.framework/Headers \
					-I ./frameworks/SDL2_image.framework/Headers \
					-I $(INCDIR)
		SDL_FRAMEWORKS = -rpath @loader_path/frameworks -F./frameworks/ \
						-framework SDL2 -framework SDL2_image \
						-framework SDL2_ttf
	endif
	ifeq ($(UNAME_S),Linux)
		LIB += -lSDL2 -lSDL2_image -lSDL2_ttf
	endif


.PHONY: all clean fclean re cleanlib fcleanlib relib

all: $(NAME) $(VNAME)

$(NAME): $(OBJ) $(LIB)
	gcc $(FLAGS) $(OBJ) $(LIB) -o $(NAME)
	@echo \\033[32m======[Compiled]===================\\033[0m

$(VNAME): $(VOBJ) $(LIB)
	gcc $(FLAGS) $(VOBJ) $(SDL_HEADERS) $(SDL_FRAMEWORKS) $(LIB) -o $(VNAME)
	@echo \\033[32m======[Compiled visualizer]========\\033[0m

$(LIB):
	make -C libft all
	
$(OBJDIR)/%.o: ./%.c $(INCDIR)/*.h | $(OBJDIR)
	gcc $(FLAGS) -o $@ -c $< -I $(INCDIR)

$(OBJDIR):
	@mkdir $(OBJDIR)

$(VOBJDIR)/%.o: ./%.c $(INCDIR)/*.h | $(VOBJDIR)
	gcc $(FLAGS) $(SDL_HEADERS) -o $@ -c $<

$(VOBJDIR):
	@mkdir $(VOBJDIR)

clean:
	@rm -Rf $(OBJDIR)
	@rm -Rf $(VOBJDIR)
	@echo \\033[34m======[Cleaned]====================\\033[0m

fclean: clean
	@rm -f $(NAME)
	@rm -f visualizer

re: fclean all

cleanlib:
	make -C libft clean

fcleanlib:
	make -C libft fclean

relib:
	make -C libft re
