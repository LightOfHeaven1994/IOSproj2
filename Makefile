# Projekt c.2 IOS
# Shamardin Egor <xshama00>
# -Wall -Wextra -Werror -pedantic
CC=gcc
CLFAGS=-std=gnu99 
PROJ=proj2
OTHERFL = -lpthread -lrt

$(PROJ): $(PROJ).c
	$(CC) $(CLFAGS) $(PROJ).c -o $(PROJ) $(OTHERFL)

clean:
	rm -rf $(PROJ)