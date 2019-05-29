PROG = asteroids
CC = g++
CPPFLAGS = -W -Wall -g -I/usr/local/include
LDFLAGS =  -Wl,--copy-dt-needed-entries -lSDL2 -lSDL2_image -L/usr/local/lib
OBJS = main.o InputManager.o Renderer.o Ship.o Bullet.o Asteroid.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(LDFLAGS)
main.o :
	$(CC) $(CPPFLAGS) -c main.cpp
InputManager.o : InputManager.h
	$(CC) $(CPPFLAGS) -c InputManager.cpp
Renderer.o : Renderer.h
	$(CC) $(CPPFLAGS) -c Renderer.cpp
Ship.o : Ship.h
	$(CC) $(CPPFLAGS) -c Ship.cpp
Bullet.o : Bullet.h
	$(CC) $(CPPFLAGS) -c Bullet.cpp
Asteroid.o : Asteroid.h
	$(CC) $(CPPFLAGS) -c Asteroid.cpp

clean:
	rm -f core $(PROG) $(OBJS)
