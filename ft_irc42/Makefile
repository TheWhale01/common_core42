CXX= c++

NAME= ircserv
OBJ_DIR= obj/
DEP_DIR= dep/
SRC_DIR= src/
INCLUDES= includes/

SRCS= $(addprefix $(SRC_DIR), main.cpp Server.cpp Channel.cpp Client.cpp utils.cpp \
	cmd/join.cpp cmd/kick.cpp cmd/notice.cpp cmd/part.cpp cmd/privmsg.cpp cmd/quit.cpp \
	cmd/topic.cpp cmd/pass.cpp cmd/nick.cpp cmd/user.cpp cmd/utils.cpp cmd/mode.cpp \
	cmd/ping.cpp cmd/whois.cpp cmd/who.cpp cmd/invite.cpp cmd/names.cpp cmd/list.cpp \
	cmd/oper.cpp Bot.cpp\
	exceptions/exception.cpp exceptions/UserOnChannelException.cpp \
	exceptions/UnknownModeException.cpp exceptions/InviteOnlyChanException.cpp \
	exceptions/UserDontMatchException.cpp exceptions/UModeUnknowFlagsException.cpp \
	exceptions/NeedMoreParamsException.cpp exceptions/UnknownCommandException.cpp \
	exceptions/NoNickNameGivenException.cpp exceptions/ErroneusNickNameException.cpp \
	exceptions/NickNameInUseException.cpp exceptions/AlreadyRegistredException.cpp \
	exceptions/NoSuchChannelException.cpp exceptions/NoSuchNickException.cpp \
	exceptions/CannotSendToChanException.cpp exceptions/NoRecipientException.cpp \
	exceptions/NoTextToSendException.cpp exceptions/NotOnChannelException.cpp \
	exceptions/ChanoPrivsNeededException.cpp exceptions/UserNotInChannelException.cpp \
	exceptions/NotRegisteredException.cpp)
DEP= $(patsubst $(SRC_DIR)%.cpp, $(DEP_DIR)%.d, $(SRCS))
OBJS= $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRCS))

CXXFLAGS= -Wall -Wextra -Werror -I $(INCLUDES) -g -std=c++98

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@mkdir -p $(subst $(OBJ_DIR), $(DEP_DIR), $(dir $@))
	$(CXX) $(CXXFLAGS) -MMD -MP -MF $(patsubst $(OBJ_DIR)%.o, $(DEP_DIR)%.d, $@) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

sanitize: fclean
sanitize: CXXFLAGS= -Wall -Wextra -Werror -I $(INCLUDES) -g -std=c++98 -fsanitize=address
sanitize: $(NAME)

clean:
	rm -rf $(OBJ_DIR) $(DEP_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re sanitize