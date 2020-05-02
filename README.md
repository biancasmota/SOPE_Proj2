#SOPE PROJ 2

##2º proj SOPE -Bianca Mota, Carolina Rosemback e Iohan Sardinha

O projeto foi criado seguindo as regras do enunciado. Decidimos seguir essas etapas para que tivessemos uma melhor percepção do funcionamento do programa.

###Cliente U:
* Precessar os argumentos

* Loop de nsecs
	* Criar nova [Thread U]
	* aguardar X milisegundos
* Fechar FIFOs privadas que ainda estejam abertos

#####[Thread U]:
* Criar tempo de utilzação = Random
* Avisar que foi criada no FIFO
* Criar um FIFO privado 'tmp/...'
* Fazer requisição de entrada
* Loop enquanto a resposta não for negativa
	* Se a resposta for positiva -> aguardar tempo de utilização
		fechar canal privado

###Servidor Q:
* Precessar os args
* Loop de nsecs
	* Verifica o FIFO para ver se há um novo cliente
	* Cria nova [Thread Q]
* Fecha FIFOs privadas que ainda estejam abertos

#####[Thread Q]:
* Acessa o FIFO privado do cliente
* Deixa-o entrar
* Fecha o fifo privado do cliente


Tivemos dúvidas porém na interpretação do enunciado, não percebemos se o tempo nsecs deveria começar a contar a partir do instante em que era chamado ou só a partir do momento em que o programa U se comunicava com o programa Q. Optamos por fazer com o nsecs contando a partir do momento em que é chamado.