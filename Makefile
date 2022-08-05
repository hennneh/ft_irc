# Output Name:
NAME:=			ircserv

# Folders:
BUILD:=			./build
SOURCE:=		./source
TESTS:=			./tests

# Other Variables:
COMPILER:=		c++
COMPFLAGS:=		-Wall -Werror -Wextra -g -std=c++98

# Source Files:
SRCFILES:=\
		  main.cpp\
		  utils.cpp\
		  irc.cpp\
		  client/client.cpp\
		  message/message.cpp\
		  channel/channel.cpp\
		  commands/channel/invite.cpp\
		  commands/channel/join.cpp\
		  commands/channel/mode.cpp\
		  commands/channel/modeusr.cpp\
		  commands/channel/names.cpp\
		  commands/channel/part.cpp\
		  commands/channel/topic.cpp\
		  commands/connection/away.cpp\
		  commands/connection/nick.cpp\
		  commands/connection/oper.cpp\
		  commands/connection/pass.cpp\
		  commands/connection/quit.cpp\
		  commands/connection/user.cpp\
		  commands/connection/welcome.cpp\
		  commands/connection/motd.cpp\
		  commands/message/notice.cpp\
		  commands/message/ping.cpp\
		  commands/message/privmsg.cpp\
		  commands/queries/who.cpp\
		  commands/queries/time.cpp\
		  commands/queries/version.cpp\
		  commands/optional/ison.cpp\
		  commands/optional/dummy.cpp\
		  commands/server/admin.cpp\

# ------------------------------------------
# Do not change anything beyond this point!
# ------------------------------------------

# Process Variables
CXX:=		$(COMPILER)
CXXFLAGS:=	$(COMPFLAGS)
SRCS:=		$(addprefix $(SOURCE)/,$(SRCFILES))
OBJS:=		$(SRCS:$(SOURCE)/%.cpp=$(BUILD)/%.o)
NAME:=		./$(NAME)
OS:=		$(shell uname -s)

.PHONY: all clean fclean re test run

# Catch Rules
all:
	make -j $(nproc) $(NAME)

# Compile .cpp files to .o Files
$(OBJS): $(BUILD)%.o : $(SOURCE)%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Main Build Rule
$(NAME): $(OBJS)
	@echo "--> Compiling Executable"
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

# Clean up Objects
clean:
	$(RM) -r $(BUILD)

# Clean up Executables and static libraries
fclean: clean
	$(RM) -r $(NAME)

# Clean the re-compile
re: fclean all

# Run the test script
test: re
ifeq ($(wildcard $(TESTS)/test.sh),)
	$(error "Test Script test.sh not found in $(TESTS)")
endif
	@./tests/test.sh

#Run the executable
run: re
	@echo "--------------------------------"
ifeq ($(OS),Linux)
	valgrind -q --leak-check=full --errors-for-leak-kinds=all $(NAME) 6669 ""
else ifeq ($(OS),Darwin)
	leaks -q --atExit -- $(NAME) 6669 "h"
else
	$(NAME) 6669 ""
endif


