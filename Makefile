all:
	g++ historico.cpp paciente.cpp fila.cpp lista.cpp testes.cpp -o testes

run:
	./testes

clean:
	rm testes