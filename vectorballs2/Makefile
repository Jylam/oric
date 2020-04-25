#NO_LIB=1

SRC=main.c sys.s sprite18.s sprite16.s sprite12.s sprite8.s copy.s sprite18_noalpha.s sprite16_noalpha.s sprite12_noalpha.s sprite8_noalpha.s clear18.s clear16.s clear12.s clear8.s
BIN=vectorballs

OBJ=$(SRC:.c=.o)
OBJ+=$(SRC:.s=.o)

include ../public/rules.mk

all: $(SRC) $(BIN)




