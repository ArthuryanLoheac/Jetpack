##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile
##

# ============= COLORS =============

GREEN=\033[0;32m
RED=\033[0;31m
YEL=\033[01;33m
BLUE=\e[1;34m
NC=\033[0m

# ============= OBJECT ============= #

OBJ_DIR = obj

OBJ = $(SRC_LIB:.$(EXTENSION)=$(OBJ_DIR)/%.o)

OBJ_SRC_SERVER = $(SRC_SERVER:%.cpp=$(OBJ_DIR)/%.o)

OBJ_SRC_CLIENT = $(SRC_CLIENT:%.cpp=$(OBJ_DIR)/%.o)

OBJ_MAIN_SERVER = $(SRC_MAIN_SERVER:%.cpp=$(OBJ_DIR)/%.o)

OBJ_MAIN_CLIENT = $(SRC_MAIN_CLIENT:%.cpp=$(OBJ_DIR)/%.o)

DEPS = $(OBJ_SRC_SERVER:.o=.d) $(OBJ_MAIN_SERVER:.o=.d) \
		$(OBJ_SRC_CLIENT:.o=.d) $(OBJ_MAIN_CLIENT:.o=.d)

# ============= PARAMETERS ============= #

COMPILER = g++

EXTENSION = cpp

# ============= FLAGS ============= #

FLAGS = -I./include -I./src \
	$(shell find include src -type d -exec echo -I{} \;) \
	-MMD -MP $(FLAGS_LIB) \
	-lsfml-window -lsfml-system -lsfml-audio

FLAGS_CLIENT = $(FLAGS) -lsfml-graphics \
	-lsfml-window -lsfml-system -lsfml-audio

FLAGS_TEST = $(FLAGS) -lcriterion --coverage \

FLAGS_LIB = -std=c++20 -Wall -Wextra -Werror

FLAGS_LINTER =	\
	--repository=. \
	--quiet \
	--output=vs7	\
	--filter=-legal/copyright,-build/c++17,+build/c++20,-runtime/references	\
	--recursive

# ============= NAMES ============= #

NAME_LIB	= \

NAME_CLIENT	=	jetpack_client

NAME_SERVER	=	jetpack_server

# ============= SOURCES ============= #

SRC_LIB	=	\

SRC_MAIN_SERVER	=	main_server.cpp \

SRC_MAIN_CLIENT	=	main_client.cpp \

SRC_SERVER	= 	$(shell find src/server -type f -name "*.cpp" ! \
			 -name "main_server.cpp" ! -name "main_client.cpp") \
			 src/log/Log.cpp \

SRC_CLIENT	= 	$(shell find src/client -type f -name "*.cpp" ! \
			 -name "main_server.cpp" ! -name "main_client.cpp") \
			 src/log/Log.cpp \

SRC_TESTS	= 	\

# ============= RULES ============= #

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): client

$(NAME_SERVER): server

client: $(OBJ_SRC_CLIENT) $(OBJ_MAIN_CLIENT)
	$(COMPILER) -o $(NAME_CLIENT) $(OBJ_SRC_CLIENT) $(OBJ_MAIN_CLIENT) \
	$(FLAGS_CLIENT)

server: $(OBJ_SRC_SERVER) $(OBJ_MAIN_SERVER)
	$(COMPILER) -o $(NAME_SERVER) $(OBJ_SRC_SERVER) $(OBJ_MAIN_SERVER) \
	$(FLAGS)

$(NAME_LIB): $(OBJ)
	ar rc $(NAME_LIB) $(OBJ)

# ============= CLEANS ============= #

clean:
	rm -rf $(OBJ_DIR)
	rm -f *.gcda *.gcno

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER) $(NAME_LIB) unit_tests

# ============= COMPILATION ============= #

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(COMPILER) -c $(FLAGS) $< -o $@

-include $(DEPS)

# ============= OTHERS ============= #

re: fclean all

COMAND_SERVER = ./$(NAME_SERVER) -p 1111 -m ./tests/basic.map

COMMAND_CLIENT = ./$(NAME_CLIENT) -p 1111 -h 127.0.0.1

run: all
	$(COMAND_SERVER)

run_client: all
	$(COMMAND_CLIENT)

run_d: all
	$(COMAND_SERVER) -d

run_client_d: all
	$(COMMAND_CLIENT) -d

# ============= TESTS ============= #

unit_tests:
	@mkdir -p $(OBJ_DIR)
	$(COMPILER) -o $(OBJ_DIR)/unit_tests $(SRC_TESTS) \
		$(SRC_SERVER) $(FLAGS_TEST)
	cp $(OBJ_DIR)/unit_tests unit_tests

tests_run: unit_tests
	./$(OBJ_DIR)/unit_tests --verbose

tests_run_coverage: tests_run
	gcovr -r . -e tests/

tests_clean_run: fclean tests_run

tests_clean_run_coverage: tests_clean_run
	gcovr -r . -e tests/

style_check:
	@cpplint $(FLAGS_LINTER) \
		$(shell find . -type f \( -name '*.cpp' -o -name '*.hpp' \))
