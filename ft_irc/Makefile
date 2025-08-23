NAME = ircserv

SOURCES = srcs/main.cpp \
		srcs/Parsing.cpp	\
		srcs/Server.cpp	\
		srcs/Client.cpp	\
		srcs/Channel.cpp	\
		srcs/Signal.cpp	\
		srcs/commands/AChannel.cpp	\
		srcs/commands/ACommand.cpp	\
		srcs/commands/Privmsg.cpp \
# 		srcs/commands/Pass.cpp	\
# 		srcs/commands/User.cpp	\
# 		srcs/commands/Nick.cpp	\

SRCS = $(addprefix $(OBJ_DIR)/, $(SOURCES))

OBJ_DIR = objs

OBJS = $(SRCS:.cpp=.o)

DEPS = $(SRCS:.cpp=.d)

COMPILATOR = c++

CCFLAGS = -Wall -Wextra -Werror -std=c++98 -MMD -g3

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(COMPILATOR) $(CCFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.cpp
		@mkdir -p $(@D)
		$(COMPILATOR) $(CCFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME) $(OBJ_DIR)

re: fclean
	make all

-include $(DEPS)

.PHONY: all clean fclean re
