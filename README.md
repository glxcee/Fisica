# Fisica

**Comandi**:
- cmake -S . -B build -G"Ninja Multi-Config" 
(crea la cartella build, *rm -rf build* la elimina)
- cmake --build build --config Debug
(linka)
- cmake --build build --config Debug --target test
(test)
- build/Debug/project
(run)

- sudo apt-get install libsfml-dev
(installa SFML libreria grafica)

**Input**:
- (x0, y0)
- A, B, C, D
- Numero di passi totali (quante volte passa delta t *[che è nell'ordine di 0.001]*)

**Calcolare a ogni step**: (xi, yi)

classe **Simulation**: *[GUARDA formule.png]*
- memoria di ogni valore (xi, yi, Hi) accessibili all'utente
- stato rappresentato internamente in termini di (x^rel_i, y^rel_i)
- metodo evolve(): fa progredire la simulazione di 1 step (delta t)
