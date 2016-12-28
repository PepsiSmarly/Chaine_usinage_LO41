# Auteur: Thomas Gredin
# Date: 19 Décembre 2016

SOURCES = main.c
SOURCES += Config.c
SOURCES += Convoyer.c
SOURCES += FactoryTable.c
SOURCES += Piece.c
SOURCES += Robot.c
SOURCES += Supervisor.c
SOURCES += Array.c
SOURCES += ThreadMethods.c
SOURCES += Network.c

CXX = gcc
NAME = usine

out:
	$(CXX) -g -o $(NAME) $(SOURCES) -pthread
