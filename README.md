# p2_FSE
Trabalho 2 de FSE

digite make run (Na pasta distribuido, ira rodar o servidor distribuido, na pasta central, o central) no input do terminal para compilar o programa;

Para iniciar o programa, primeiro inicie o servidor distribuido, depois inicie o servidor central, espere 1 segundo para iniciar os valores utilize os comandos abaixo para controlar o programa;

O cursor do ncurses está bugado mas o input permanece o mesmo do scanf.


Digite "OA1" para ligar a lampada 1, e "OA0" para desliga-la;
Digite "OB1" para ligar a lampada 2, e "OB0" para desliga-la;
Digite "OC1" para ligar a lampada 3, e "OC0" para desliga-la;
Digite "OD1" para ligar a lampada 4, e "OD0" para desliga-la;
Digite "OE1" para ligar o ar condicionado 1, e "OE0" para desliga-lo;
Digite "OF1" para ligar o ar condicionado 1, e "OF0" para desliga-lo;
Digite "OG1" para ligar o alarme, e "OG0" para desliga-lo;

Caso o alarme seja acionado, será mostrado na tela a frase "ALARME ACIONADO", caso ele seja desativado posteriormente, sera mostrado na tela "ALARME DESATIVADO";

O alarme aciona apenas quando o estado dos sensores muda. EX: "LLLLLLLL" alarme desligado, liga alarme, muda para "DLLLLLLL", alarme acionado; 

O estado dos sensores e das lampadas é mostrado utilzando as letras 'L', para ligado, e 'D', para desligado;

Para encerrar utilize ctrl+C ou ctrl+z

Encerre primeiro o Servidor Central, depois o Distribuido.