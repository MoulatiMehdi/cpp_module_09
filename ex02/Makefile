CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g

CXX = c++ $(CXXFLAGS)
RM  = rm -rf


NAME = PmergeMe
DEPS = PmergeMe.hpp 
SRCS = PmergeMe.cpp main.cpp  

OBJS = $(SRCS:.cpp=.o) 

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

.PHONY : all re fclean clean
.SECONDARY : $(OBJS)




