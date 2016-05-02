# Arduino Cor

Este programa utiliza o sensor de cor TCS230 para ler as informações RGB de cor apresentadas ao sensor 
as transforma em HSL (http://en.wikipedia.org/wiki/HSL_color_space).
Nesse formato é possível detectar as cores procurando manter independência do nível de luminosidade
do ambiente.

O progrma utiliza um botão para realizar a calibração do branco.
A calibração serve para ajustar o ganho de cada cor do sendor.

O programa permite a ligação de um led RGB que permite reproduzir até
6 cores que são; vermelho, verde, azul, ciano, magenta e amarelo, além do branco.

## Creditos

Este código foi bastante inspirado no artigo publicado em 
http://www.arduinoecia.com.br/2014/02/sensor-de-reconhecimento-de-cor-tcs230.html
