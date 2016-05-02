# Arduino Cor

Este programa utiliza o sensor de cor TCS230 ligado a um arduino para ler as informações RGB de cor apresentadas ao sensor 
as transforma em HSL (http://en.wikipedia.org/wiki/HSL_color_space).
Nesse formato é possível detectar as cores procurando manter independência do nível de luminosidade
do ambiente. Foi utilizado um arduino pro mini mas funciona em qualquer modelo.

O progrma utiliza um botão para realizar a calibração do branco.
A calibração serve para ajustar o ganho de cada cor do sendor. A calibração de cor
é guardada na memória interna do arduino então não se perde ao desligar e ligar.
A calibração de branco é necessário pois ao mudar a luminosidade ambiente muda-se 
a quantidade de luz que chega ao sensor.

O programa permite a ligação de um led RGB quereproduz até
6 cores que são: vermelho, verde, azul, ciano, magenta e amarelo, além do branco.

O programa possui uma saída para ligar ao módulo de controle da PETE (http://loja.pete.com.br/)
permitindo que ele funcione como o sensor de cor fabricado por eles.

O programa mostra todas as informações no console serial. para acomodar bem a saída de dados a velocidade foi ajustada
para 57600 bps.


## Creditos

Este código foi bastante inspirado no artigo publicado em 
http://www.arduinoecia.com.br/2014/02/sensor-de-reconhecimento-de-cor-tcs230.html
