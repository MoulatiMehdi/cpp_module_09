CXXFLAGS =  -Wall -Wextra -Werror -std=c++98 -g 

CXX = c++ $(CXXFLAGS) 
RM  = rm -rf  

SRCS = BitcoinExchange.cpp  main.cpp  
DEPS = BitcoinExchange.hpp

OBJS = $(SRCS:.cpp=.o) 
NAME = btc 

all : $(NAME)


$(NAME) : $(OBJS) $(DEPS)
	$(CXX) $(OBJS) -o $@

%.o : %.cpp $(DEPS)
	$(CXX) -c $< -o $@

clean : 
	$(RM) $(OBJS)

fclean : clean 
	$(RM) $(NAME)

re : fclean all 

.PHONY: re clean fclean all
.SECONDARY: $(OBJS)
