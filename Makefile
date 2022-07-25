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
all: $(NAME)

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
ifeq ($(UNAME),Linux)
	@valgrind -q --leak-check=full --errors-for-leak-kinds=all $(NAME)
else ifeq ($(UNAME),Darwin)
	@leaks -q --atExit -- $(NAME)
else
	$(NAME)
endif


