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

NAME		:=	RT
RUNMODE		?=	release
# RUNMODE		?=	dev
# VERBOSE	:= TRUE

INTERFACE	:=	delete_obj.c screen_manager.c ui_lists.c ui_menu.c			   \
				ui_objects.c ui_scene_editor.c ui_tools.c ui_csg.c			   \
				interface.c new_object_tools.c new_object.c object_tools.c	   \
				ui_edit_win.c ui_file_win.c ui_render.c anim_tools.c		   \
				ui_selector.c ui_render_settings.c ui_anim_toolbox.c		   \
				anim_toolbox.c ui_anim.c animate.c anim_set.c ui_camera_tab.c  \
				anim_reset.c ui_anim_selector.c new_cluster.c ui_cluster.c	   \
				ui_selector_obj.c ui_anim_toolbox2.c ui_cube.c ui_tore.c	   \
				ui_apply_rotation.c
PARSER		:=	export_csg.c export_shape.c export_toolbox.c export.c		   \
				obj_data.c  obj_name.c parse_csg.c parse_shape.c parser.c	   \
				parse_txt.c parse_utils.c parse_toolbox.c read.c setter.c	   \
				export_anim.c export_anim_tools.c parse_anim_tools.c		   \
				parse_anim.c parse_cmp.c set_shape.c
RENDER		:=	camera.c cast.c filters.c light.c normal_mapping.c			   \
				perturbation.c post_process.c render.c texture_loader.c		   \
				texture_toolbox.c perlin.c perlin_texture.c skybox.c		   \
				pre_render.c light_utils.c
RENDER_U	:=	init_sdl.c error_sdl.c exit_sdl.c loop_sdl.c render_time.c	   \
				init_mthr_sdl.c render_mthr_sdl.c save_screenshot.c
TOOLS		:=	free_scene.c free.c utils.c get_scenes.c update.c reload.c	   \
				load_tools.c hook.c free2.c list_toolbox.c
SRC			:=	 $(INTERFACE) $(PARSER) $(RENDER) $(RENDER_U) $(TOOLS)
SRC			+=	 main.c  key_mapping.c
SRC_UNUSED	:=	 test.c render_pool.c render_sdl.c
# directories :
VPATH		:=	./srcs ./srcs/parser ./srcs/render ./srcs/tools	\
				./srcs/interface ./srcs/render_utils

LIB_DEP		=	lib/libft/libft.a				\
				lib/librt/librt.a				\
				lib/cimgui/libcimgui.a			\
				lib/imgui_impl/libimgui_impl.a

RESDIR		=	./resources
# **************************************************************************** #
# Makefile dependency :
include lib/libft/mk_c_project.mk
include lib/libft/mk_lib_dep.mk
include mk_run.mk
include mk_app.mk
# **************************************************************************** #
# Additionnal linkers :
# SDL2
LIB_LINK	+=	$(shell sdl2-config --libs)  -lSDL2_Image
INC			+=	$(shell sdl2-config --cflags)
# Imgui
LIB_LINK	+=	-lstdc++ -framework OpenGl
BANNER		:=	$(shell cat resources/script/banner.txt)
# **************************************************************************** #
# Target rules :
.DEFAULT_GOAL := all
all: $(LIB_BUILT) $(NAME) ## Built the project.
.PHONY: all

$(RESDIR):
	cp -r /sgoinfre/goinfre/Perso/amerlon-/resources $(RESDIR)

$(NAME): $(LIB_DEP) $(OBJ) | $(RESDIR)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(INC) $(LIB_LINK)
	@printf "\033[1;34m$(NAME)\033[25G\033[32mBuilt $@ $(OKLOGO)\n"
	@printf "$(BANNER)"
-include $(DEP)

fclean: $(LIB_DEP_CLEAN) clean dclean aclean ## Full clean of the project & the libs.
	$(RM) imgui.ini
	$(RM) $(NAME)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning $(NAME) $(OKLOGO)"
.PHONY: fclean

test: all ## This check the parsing on maps in the scenes dir.
	@for file in `LS scenes | grep .rt | sort -u`; \
		do echo $$file && ./RT scenes/$$file -t; done
.PHONY: test

doc: ## Generate documentation using doxygen.
	doxygen Doxyfile
	open docs/html/index.html
	@printf "\033[1;34m$(NAME)\033[25G\033[31mDocumentation $(OKLOGO)"
.PHONY: doc

dclean: ## Clean the documentation.
	$(RM) -r docs/html
	$(RM) -r docs/latex
	@printf "\033[1;34m$(NAME)\033[25G\033[31mDocumentation removed $(OKLOGO)"
.PHONY: dclean

norme: ## Check the norme of the project and the libraries.
	$(MAKE) -C lib/libft norme
	$(MAKE) -C lib/librt norme
	norminette srcs includes | $(GREP_ERR)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mNorminette $(OKLOGO)"
.PHONY: norme
