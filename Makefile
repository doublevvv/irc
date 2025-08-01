# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: doublevv <vv>                              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/03 10:45:18 by doublevv          #+#    #+#              #
#    Updated: 2025/07/15 11:51:21 by doublevv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

SOURCES = srcs/main.cpp srcs/Client.cpp srcs/Server.cpp

# SRCS = $(SOURCES)

SRCS = $(addprefix $(OBJ_DIR)/, $(SOURCES))

OBJ_DIR = objs

OBJS = $(SRCS:.cpp=.o)

CXX = c++

CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -MMD

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.cpp
		@mkdir -p $(@D)
		$(CXX) $(CXXFLAGS) -c $< -o $@

DEP =	$(SRCS:.cpp=.d)

clean:
	$(RM) $(OBJS) $(DEP)

fclean: clean
	$(RM) $(NAME) $(OBJ_DIR)

re: fclean
	make all

.PHONY: all clean fclean re

-include $(DEP)
