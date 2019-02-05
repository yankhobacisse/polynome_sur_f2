CC = gcc
EXEC1 = run
OBJS = f2_poly.o test.o arithm.o

test : $(OBJS)
	$(CC) $(OBJS) -o $@ -lm

f2_poly.o : f2_poly.h f2_polybis.c
	$(CC) -o $@ -c  f2_polybis.c

arithm.o : arithm.h arithm.c
		$(CC) -o $@ -c arithm.c 
test.o : f2_poly.h f2_poly_test.c
	$(CC) -o $@ -c f2_poly_test.c
$(EXEC1):
	./test 
clean:
	find . -name '*.o' -exec rm -f {} ';'
	find . -name '*.a' -exec rm -f {} ';'
	find . -name '*~' -exec rm -f {} ';'
	find . -name '#*#' -exec rm -f {} ';'
	find . -name '.#*' -exec rm -f {} ';'
	find . -name 'core' -exec rm -f {} ';'
	find . -name '*.core' -exec rm -f {} ';'
	-rm -rf $(PRGS)
