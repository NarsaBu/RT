# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_app.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amerlon- <amerlon-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/24 01:23:21 by amerlon-          #+#    #+#              #
#    Updated: 2020/05/21 10:56:06 by amerlon-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# This handle the make app.
# Generate a .app conpatible with OSX.

CONTENT_FILES	:=	./resources/built/Info.plist
RESRCS_FILES	:=	./resources/built/fe_icon.icns
CONTENT_BIN		:=  ./resources/materialList.csv 	\
					./resources/textures
WITH_THE_BIN	:=  ./scenes

aclean: ## Clean the app bundle.
	$(RM) -r built
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning $(NAME).app $(OKLOGO)"
.PHONY: aclean

app: $(NAME)  aclean ## Built the app bundle (Only on mac).
	mkdir -p "./built/$(NAME).app"/Contents/{MacOS,Resources} 2> /dev/null || true
	mkdir "./built/$(NAME).app"/Contents/MacOS/resources 2> /dev/null || true
	cp $(CONTENT_FILES) "./built/$(NAME).app/Contents/"
	cp $(RESRCS_FILES) "./built/$(NAME).app/Contents/Resources"
	cp -r $(CONTENT_BIN) "./built/$(NAME).app/Contents/MacOS/resources"
	cp -r $(WITH_THE_BIN) "./built/$(NAME).app/Contents/MacOS"
	cp ./$(NAME) "./built/$(NAME).app/Contents/MacOS/binary"
	open built/
	@printf "\033[1;34m$(NAME)\033[25G\033[32mBuilt $(NAME).app $(OKLOGO)"
.PHONY: app
