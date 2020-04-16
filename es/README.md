# Bluetooth-Pedalboard

MIDI Pedalboard con comunicación Bluetooth. Esencialmente el mismo proyecto que en https://github.com/ignotus666/midi-pedalboard pero con la capacidad de bluetooth agregada y todas los potenciómetros eliminados. Vi que no es práctico tener que agacharse para manipularlos ... El código es casi el mismo, con el código de los potenciómetros eliminado y algo añadido para medir el voltaje de la batería y mostrarlo en la pantalla. No hay necesidad de código específico de bluetooth. La principal diferencia está en el hardware, con la adición de 2 módulos bluetooth y un circuito receptor.

Los módulos bluetooth utilizados son el HC-05; uno para el transmisor y otro para el receptor. En la pedalera, la salida Tx del Arduino se alimenta al pin Rx de un HC-05 (usando un divisor de voltaje para reducir los 5v a alrededor de 3.3v), sin pasar por el circuito MIDI-USB, que ahora se puede omitir o usado para el receptor. El receptor consiste en el circuito MIDI-USB utilizado en el MIDI Pedalboard que recibe los datos seriales que provienen de un segundo módulo HC-05 (módulo Tx -> PIC18F2550 Rx, no se necesita un divisor de voltaje). La pedalera está alimentada por una batería de iones de litio 18650 que tiene un circuito de carga / protección y un módulo de refuerzo DC-DC para emitir 5v constantes para el Arduino. La batería + terminal está conectada a una entrada analógica para leer su voltaje e imprimir el valor en la pantalla, para saber cuándo necesita cargarse. Esta lectura se suaviza utilizando la biblioteca AnalogSmooth ya que de lo contrario es bastante errática.

La ruta de la señal es la siguiente:

Arduino Tx -> Emisor Rx HC-05 (esclavo) -> (((señal BT))) -> Receptor HC-05 (maestro) Tx -> Rx PIC18F2550 (MIDI USB) -> PC

Para que la comunicación MIDI-bluetooth funcione, es necesario realizar una serie de cambios de software en los módulos bluetooth, el firmware PIC y la biblioteca MIDI.

Se incluye una pequeña guía sobre qué cambios deben realizarse en los módulos bluetooth y cómo hacerlos. También se incluye el firmware modificado para el PIC18F2550 en el receptor. Las instrucciones sobre cómo cargar este firmware al PIC si no tiene un programador se incluyen en la carpeta bluetooth_files. El otro cambio necesario es la velocidad en baudios en la biblioteca MIDI. Abra el archivo 'midi_settings.h' (en mi caso está en / home / *username* /Arduino/libraries/arduino_midi_library-master/src/midi_settings.h) y en la línea 73 cambie la velocidad de transmisión a 115200.

Cuando la pedalera está apagada, la línea que va desde la batería + terminal al pin analógico debe cortarse. Utilizo un interruptor 2PDT para apagar y también esta línea.

Las baterías de iones de litio pueden ser peligrosas y deben manejarse con cuidado. No me hago responsable de nada malo que suceda. Una alternativa es usar un pequeño banco de energía para alimentar la pedalera y luego puede omitir todo el código y los circuitos de la batería.

FUNCIONES:

El modo predeterminado al arrancar es 'Modo preestablecido'. Puede elegir entre 6 preajustes usando los interruptores 'keyPressed [0]' a 'keyPressed [5]'. Los interruptores 'keyPressed [6]' (Bank down) y 'keyPressed [7]' (Bank up) se desplazan a través de 5 bancos preestablecidos (se pueden agregar más con relativa facilidad; simplemente no necesito tantos), cada uno con un conjunto de 6 presets. Este modo envía mensajes MIDI de cambio de programa, cada preset con su propia nota (de 0 a 29, canal 1).

En el modo preestablecido, presionando el pedal de expresión + Banco hacia abajo puede desplazarse a través de 3 funciones diferentes para los botones de cambio de banco. En el modo predeterminado, se desplazan por los bancos de la pedalera (no se envía MIDI). La siguiente función los configura para enviar mensajes MIDI para 'Next Bank' y 'Previous Bank'. La última función envía mensajes MIDI para 'Next Preset' y 'Previous Preset'.

El interruptor 'KeyPressed [8]' (Modo Stomp) activa el 'Modo Stomp'. Obtiene 6 pedales que se pueden encender y apagar usando los interruptores 'keyPressed [0]' a 'keyPressed [5]'. Cuando está en 'Modo Stomp', los interruptores 'Bank up' y 'Bank down' pueden usarse para subir y bajar el volumen. Cada interruptor de pedal envía un mensaje CC que alterna entre los valores 127 y 0, para activar y desactivar los pedales.

El interruptor 'KeyPressed [9]' (Modo Loop) activa el 'Modo Loop'. Obtiene 8 funciones de bucle utilizando los interruptores 'keyPressed [0]' a 'keyPressed [5]' y los interruptores 'Bank up' y 'Bank down'. Estas funciones son para operar el software Sooperlooper. Se utilizan mensajes CC.

Al presionar nuevamente el interruptor 'Modo de pisotón' o 'Modo de bucle' vuelve al 'Modo preestablecido'.

Es posible calibrar un pedal de expresión conectado a A0 (cambiar en consecuencia si se usa otra entrada). Al presionar el pedal de expresión y 'presionar la tecla [3]' al mismo tiempo, ingresa al modo de calibración y tiene 5 segundos para mover el pedal en todo su rango. Los niveles mínimo y máximo se almacenan en eeprom, por lo que la calibración solo debe ser necesaria una vez.

Para cambiar los nombres o notas preestablecidos, busque y reemplace en el boceto (todas las pestañas). Para los nombres preestablecidos, asegúrese de reemplazar también el nombre acortado (a veces) que se muestra en la posición relativa a los botones. Los nuevos nombres deben mostrarse en la posición correcta en la pantalla sin la necesidad de ingresar sus coordenadas.

La biblioteca TFT utilizada es ILI9341_due por Marek Buriak. Por alguna razón, el archivo image.h debe copiarse en el directorio raíz de esta biblioteca para que el boceto lo recoja correctamente.

Este video muestra la mayoría de las funciones: https://www.youtube.com/watch?v=eDRC17XOzQg&t=9s. Algunos aspectos de la pantalla han cambiado desde entonces.
