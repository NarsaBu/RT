# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_c_project.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/23 23:30:21 by amerlon-          #+#    #+#              #
#    Updated: 2020/05/21 10:56:06 by amerlon-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJDIR 		:=	objs
INCDIR  	:=	includes
OBJ			:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DEP			:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.d))
INC			:=	-I includes
# **************************************************************************** #
OKLOGO		:=	\033[78G\033[32m[Done]\033[0m\n
GREP_ERR	:=	grep 'Error\|Warning' -C1 2> /dev/null || true
PHELP		:=	"\033[36m%-26s\033[0m %s\n"
RM			:=	/bin/rm -f
.SUFFIXES:
# **************************************************************************** #
# Compile custom :
CC			:=	clang
CFLAGS		:=	-Werror -Wall -Wextra -Wstrict-aliasing -pedantic -Wunreachable-code
ifndef VERBOSE
    .SILENT:
endif
.SUFFIXES:
ifeq ($(RUNMODE),dev)
DEV_CFLAGS	:=	-g3 -O0
# DEV_CFLAGS	+=	-fsanitize=thread
DEV_CFLAGS	+=	-fsanitize=address -fsanitize-recover=address
# DEV_CFLAGS	+=	-fstack-protector
DEV_CFLAGS	+=	-fsanitize=undefined
else
DEV_CFLAGS	:= -O3 -march=native -flto -g0
endif
CFLAGS		+= $(DEV_CFLAGS)
# **************************************************************************** #
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -MMD -MP -c -o $@ $< $(INC)
	@printf "\033[1;34m$(NAME)\033[25G\033[33mCompile $< $(OKLOGO)"

usage: ## Print out on how to use this Makefile.
	@printf "\n$(NAME)\n  Usage:\n\tmake <target>\n\n  Targets:\n"
	@fgrep -h " ## " $(MAKEFILE_LIST) \
	| fgrep -v fgrep | awk 'BEGIN {FS = ":.*?## "}; {printf $(PHELP), $$1, $$2}'
	@printf "\n  Scenes:\n"
	@for file in `LS scenes | grep .rt | sort -u | cut -d . -f 1`; \
		do printf "make run $$file \n"; done
.PHONY: usage

clean:  ## Clean of the project directory (.o & .d).
	$(RM) $(OBJ)
	$(RM) $(DEP)
	$(RM) -r $(OBJDIR)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning objs $(OKLOGO)"
.PHONY: clean

re: ## Rebuild the project.
	make fclean
	make all
.PHONY: re
