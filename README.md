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

## Licença

 Copyright © Masaki Kawabata Neto e outros

A permissão é concedida, a título gratuito, para qualquer pessoa que obtenha uma cópia deste software e arquivos de documentação associados (o "Software"), para lidar com o Software sem restrição, incluindo, sem limitação dos direitos de uso, copiar, modificar, mesclar , publicar, distribuir, sublicenciar e / ou vender cópias do Software, e para permitir que as pessoas às quais o Software é fornecido a fazê-lo, mediante as seguintes condições:

O aviso de direito autoral acima e este aviso de permissão devem ser incluídos em todas as cópias ou partes substanciais do Software.

O Software é fornecido "como está", sem qualquer tipo de garantia, expressa ou implícita, incluindo mas não se limitando a garantias de comerciabilidade, adequação a uma finalidade específica e não violação. Em nenhum caso os autores ou os detentores dos direitos autorais {{{1}}} se responsabilizarão por qualquer reclamação, danos ou qualquer outra responsabilidade, seja em razão de contrato, ato ilícito ou de outra forma, resultantes de ou em conexão com o software ou a utilização ou outras negociações no Software.
