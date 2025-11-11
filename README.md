# Laberintos y fantasmas 👻🎮

Laberintos y fantasmas es un juego programado en C. 

El objetivo del juego es llevar al jugador desde la entrada del laberinto hacia su salida, evitando en el trayecto a los fantasmas enemigos y recogiendo vidas y puntos.

## Instalación ⚙

Para instalar jugar a laberintos y Fantasmas, deberá descargar este proyecto y a continuación compilar los proyectos "laberintos-fantasmas.cbp" y opcionalmente "servidor-db.cbp" (Este último en el caso de que desee registrar sus records).

Si quiere jugar de manera "offline" deberá ejecutar unicamente el archivo "laberintos-fantasmas.exe", en el caso de jugar en el servidor, primero deberá ejecutar "servidor-db.exe" y luego el archivo "laberintos-fantasmas.exe".

## Instrucciones 📕
Usted deberá mover al jugador ('J') desde la entrada ('E') hasta la salida ('S') del laberinto. Debiendo evitar a los fantasmas enemigos ('F'). 
Durante el viaje, el jugador recogerá vidas ('V') y puntos ('P') que lo posicionarán mejor en el ranking.

El jugador se mueve con las teclas W (arriba), A (izquierda), S (abajo), D (derecha) y solo podrá caminar por los caminos del laberinto ('.') y no podrá en ninguna circunstancia saltar sus muros ('#'). 
Cada vez que el jugador es atacado por un fantasma, el fantasma desaparecerá del laberinto (para facilitar al jugador) y como penalización, el jugador volverá a la entrada del laberinto perdiendo una vida teniendo que empezar su recorrido desde 0. 

El juego finalizará cuando el jugador llegue a la salida con vidas (ganada) o cuando el jugador se quede sin vidas (perdida).