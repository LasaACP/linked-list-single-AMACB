make:
	g++ main.cpp -o airports

exec:
	make
	./airports	

clean:
	rm airports