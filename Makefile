NAME = ft_ssl

FLAG = -Wall -Wextra -Werror
CC = gcc $(FLAG)

SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/, \
		md5_cst_functions.c \
		md5_fill_cst.c \
		md5_padding.c \
		md5_algo.c \
		sha256_224_padding.c \
		sha256_224_algo_main.c \
		sha256_224_algo_run.c \
		sha256_224_algo_tasks.c \
		sha512_384_padding.c \
		sha512_384_algo_main.c \
		sha512_384_algo_run.c \
		sha512_384_algo_tasks.c \
		sha1_cst_functions.c \
		sha1_padding.c \
		sha1_fill_cst.c \
		sha1_algo_main.c \
		sha1_algo_tasks.c \
		conversion.c \
		usage.c \
		utils_options.c \
		utils_display_hex.c \
		utils_malloc.c \
		utils_algo.c \
		utils_memcpy_back.c \
		display_digest.c \
		first_init.c \
		get_hash_algo.c \
		apply_file.c \
		apply_option.c \
		apply_stdin.c \
		apply_algo_for_arg.c \
		run_ft_ssl.c \
		maths.c \
		clean.c \
		main.c)

OBJ_DIR = objs
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_H = $(LIBFT_DIR)/include

H_DIR = include
INCL = -I$(H_DIR) -I$(LIBFT_H)


################################################################################
#################################### RULES #####################################
################################################################################

all : $(NAME)

$(LIBFT) :
	@make -C $(LIBFT_DIR)
	@printf "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

$(NAME) : $(LIBFT) $(OBJ)
	@$(CC) $(OBJ) -o $@ $(LIBFT)
	@printf "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(H_DIR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INCL) -c $< -o $@
	@printf "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

clean :
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -f $(NAME)

fclean_lib :
	@make fclean -C $(LIBFT_DIR)

run_all_tests: run_basic_tests run_main_tests

run_basic_tests:
	@sh tests/basic_tests.sh

run_main_tests:
	@python3 tests/main_tests.py

fclean_all : fclean_lib fclean

re : fclean all

re_with_lib: fclean_all all
