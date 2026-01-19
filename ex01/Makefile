CXXFLAGS = -Wall -Wextra -Werror -std=c++98

CXX = c++ $(CXXFLAGS)
RM  = rm -rf


DEPS = RPN.hpp
SRCS = RPN.cpp  main.cpp 

OBJS = $(SRCS:.cpp=.o)
NAME = RPN 


all : $(NAME)

$(NAME) : $(OBJS) $(DEPS)
	$(CXX) $(OBJS) -o $(NAME)

%.o : %.cpp $(DEPS) 
	$(CXX) $< -c -o $@

clean : 
	$(RM) $(OBJS)

fclean : clean 
	$(RM) $(NAME)

re : fclean all 

.PHONY : re fclean clean all 
.SECONDARY : $(OBJS)
