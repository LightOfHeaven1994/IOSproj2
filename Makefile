# Projekt c.2 IOS
# Shamardin Egor <xshama00>
# -Wall -Wextra -Werror -pedantic
CC=gcc
CLFAGS=-std=gnu99 
PROJ=proj2
SYM_PROC=sym_process
OTHERFL = -lpthread -lrt

$(PROJ): $(PROJ).c
	$(CC) $(CLFAGS) $(PROJ).c $(SYM_PROC).c -o $(PROJ) $(OTHERFL)

clean:
	rm -rf $(PROJ)