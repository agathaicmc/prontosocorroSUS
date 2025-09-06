all:
	g++ historico.cpp paciente.cpp fila.cpp lista.cpp prontosocorro.cpp -o prontosocorro

run:
	./prontosocorro

clean:
	rm prontosocorro