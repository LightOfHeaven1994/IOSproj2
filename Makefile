# Projekt c.2 IOS
# Shamardin Egor <xshama00>
CC=gcc
CLFAGS=-std=gnu99 -Wall -Wextra -Werror -pedantic
PROJ=proj2

$(PROJ): $(PROJ).c
	$(CC) $(CLFAGS) $(PROJ).c -o $(PROJ)

clean:
	rm -rf $(PROJ)