# SOPE PROJ 2

## 2º proj SOPE -Bianca Mota, Carolina Rosemback e Iohan Sardinha


O enunciado não deixava claro se o tempo de execução aproximado dos programas passado por *nsecs* é contato a partir do momento que há comuniação entre cliente e servidor ou se desde o momento que o código é executado.


Optamos por fazer com que este tempo seja contado desde o momento que o programa é executado, assim quando um dos programas é chamado ele aguarda a comunicação com o outro, se esta comunicação não acontecer dentro de *nsces* o programa fecha. 


Consideramos que o quarto de banho abre quando o programa Q é chamado, e fecha depois de *nsecs* segundos para entrada de novos clientes.


Os clientes vão tentar entrar a partir do monto da execução do programa, ou se quando o programa começar o quarto de banho estiver fechado, no momento que abrir. E ficará fazendo novos pedidos a cada 10 milisegundos a partir de então, até que ou o banheiro feche ou o tempo *nsecs*, que se conta desde o momento do inicio da execução, acabe;

* U


	A **main** processa os argumentos da linha de comando através de **processArgs**, começa contar o tempo e chamar uma nova thread da função **pedidos** que tratará dos pedidos para entrar no quarto de banho, a comunicação com o servidor.
	
* Q

	A **main** processa os argumentos da linha de comando através de **processArgs**, começa a contar o tempo e chama **look_for_clients** para ficar olhando o fifo verificando o canal público de comunicação com o cliente, tarefa que é feita em uma thread separada, para não impedir a contagem do tempo enquanto se aguarda a conexão do cliente.
	
	Quando **look_for_clients** detecta uma comunicação do cliente chama **process_client** que tratará o pedido do cliente, e comunicará com o cliente
