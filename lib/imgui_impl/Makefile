# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/27 19:33:22 by amerlon-          #+#    #+#              #
#    Updated: 2020/05/21 20:43:21 by amerlon-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libimgui_impl.a
# RUNMODE		?=	dev
SRC			:=	imgui_impl_opengl2.cpp \
				imgui_impl_sdl.cpp
# directories :
SRCDIR  	:=	.
OBJDIR 		:=	objs
INCDIR  	:=	includes
# SDL
LSDL_LIB	:=	$(shell sdl2-config --libs) -lSDL2_Image
LSDL_INC	:=	$(shell sdl2-config --cflags)
# IMGUI
LIMGUI_INC  :=	-I ../cimgui/imgui
# **************************************************************************** #
# make specs :
CC			:=	clang
CFLAGS		:=	-Werror -Wall -Wextra -Wstrict-aliasing -pedantic
CFLAGS		+=	-Wunreachable-code -O2 -march=native -flto
ifndef VERBOSE
.SILENT:
endif
RM			:=	/bin/rm -f
.SUFFIXES:
# **************************************************************************** #
# Automatic variable :
OBJ			:=	$(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))
DEP			:=	$(addprefix $(OBJDIR)/, $(SRC:.cpp=.d))
LIB			:=	$(LSDL_LIB)
INC			:=	-I $(INCDIR) $(LSDL_INC) $(LIMGUI_INC)
# **************************************************************************** #
OKLOGO		:=	\033[80G\033[32m[OK]\033[0m\n
GREP_ERR	:=	grep 'Error\|Warning' -C1 2> /dev/null || true
# **************************************************************************** #
# Rules :
all: $(NAME)
.PHONY: all
$(NAME): $(OBJ)
	ar rc $@ $(OBJ) && ranlib $@
	@printf "\033[1;34m$@\033[25G\033[32mBuilt $@ $(OKLOGO)\n"
-include $(DEP)
$(LFT_RULE):
	make -C $(LFT_PATH)/
$(OBJDIR)/%.o: %.cpp
	mkdir $(OBJDIR) 2> /dev/null || true
	$(CC) $(CFLAGS) -MMD -MP -c -o $@ $< $(INC)
	@printf "\033[1;34m$(NAME)\033[25G\033[33mCompile $< $(OKLOGO)"
clean:
	$(RM) $(OBJ)
	$(RM) $(DEP)
	$(MAKE) -C ../cimgui clean
	rmdir $(OBJDIR) 2> /dev/null || true
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning objs $(OKLOGO)"
.PHONY: clean
fclean: clean
	$(RM) $(NAME)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning $(NAME) $(OKLOGO)"
.PHONY: fclean
re: fclean all
.PHONY: re
