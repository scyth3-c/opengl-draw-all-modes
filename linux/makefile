EJECUTABLE = ejecutable
OBJETOS = core.o


CPPFLAGS = -lm -lglut -lGL -lGLU
CC = g++


$(EJECUTABLE) : $(OBJETOS)
	@$(CC) $(OBJETOS)  $(CPPFLAGS) -o $(EJECUTABLE)


%.o : %.cpp
	@$(CC) -c $(CPPFLAGS) $< -o $@
