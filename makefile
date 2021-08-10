CC=gcc
ARGS=-Wall -Wextra -Werror -Wpedantic
ARQ=programa.c

all: avl.o ${ARQ}
	${CC} -o codigo $< ${ARQ} ${ARGS}

avl.o: avl.c avl.h
	${CC} -o $@ $< -c ${ARGS}

run: all
	if [ "${ENTRADA}" = "" ];\
	then\
		./codigo;\
	else\
		if [ -f "${ENTRADA}" ];\
		then\
			cat ${ENTRADA} | ./codigo;\
		else\
			echo "Arquivo \"${ENTRADA}\" não existe";\
		fi;\
	fi;

clean:
	rm **.o codigo
