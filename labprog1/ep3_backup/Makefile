
CFLAGS = -Wall -ansi -pedantic -lm `allegro-config --libs`
OBJECTS = Config.o Desenho.o Entity.o Estat.o Fisica.o Lista.o Naufrago.o Passageiro.o
OBJECTS_TV = Config.o Desenho.o Entity.o Estat.o Fisica.o Lista.o Naufrago_teste.o Passageiro.o

CC = gcc

Naufrago: $(OBJECTS)
	gcc $(CFLAGS) $(OBJECTS) -o Naufrago

Config.o: Config.c Config.h
Desenho.o: Desenho.c Desenho.h Fisica.h Entity.h Lista.h
Entity.o: Entity.c Lista.h Entity.h Fisica.h
Estat.o: Estat.c Estat.h
Fisica.o: Fisica.c Entity.h Lista.h Fisica.h Estat.h Desenho.h
Lista.o: Lista.c Lista.h
Naufrago.o: Naufrago.c Entity.h Lista.h Fisica.h Desenho.h Config.h \
  Passageiro.h Estat.h
Naufrago_teste.o: Naufrago_teste.c Entity.h Lista.h Fisica.h Desenho.h \
  Config.h Passageiro.h Estat.h
Naufrago_teste_velo.o: Naufrago_teste_velo.c Entity.h Lista.h Fisica.h \
  Desenho.h Config.h Passageiro.h Estat.h
Passageiro.o: Passageiro.c Lista.h Entity.h Fisica.h Desenho.h Estat.h \
  Passageiro.h

.PHONY: clean
clean:
	rm *.o *~

.PHONY: teste
teste: $(OBJECTS_TV)
	gcc $(CFLAGS) $(OBJECTS_TV) -o Naufrago_teste
