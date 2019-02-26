
NAME = sdl_test

INCDIR = includes/

SRCS =	main.c

OBJ = $(SRCS:.c=.o)

UNAME_S = $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		SDL_HEADERS = -I ./frameworks/SDL2.framework/Headers \
					-I ./frameworks/SDL2_ttf.framework/Headers \
					-I ./frameworks/SDL2_image.framework/Headers
		SDL_FRAMEWORKS = -rpath @loader_path/frameworks -F./frameworks/ \
						-framework SDL2 -framework SDL2_image \
						-framework SDL2_ttf
	endif
	ifeq ($(UNAME_S),Linux)
		LIB = -lSDL2 -lSDL2_image -lSDL2_ttf
	endif

all:			$(NAME)

$(NAME):		$(OBJ)
	@clang $(OBJ) $(SDL_HEADERS) -I $(INCDIR) $(SDL_FRAMEWORKS) $(LIB) -o $(NAME)

%.o: %.c
	@clang $(SDL_HEADERS) -I $(INCDIR) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean:			clean
	@rm -f $(NAME)

re:				fclean all
