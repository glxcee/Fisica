# Fisica

**Input**:
- (x0, y0)
- A, B, C, D
- delta t
    - unità di misura di riferimento
    - variabile a runtime
    - nell'ordine di 0.001

**Calcolare a ogni step**: (xi, yi, Hi)

classe **Simulation**: *[GUARDA formule.png]*
- memoria di ogni valore (xi, yi, Hi) accessibili all'utente
- stato rappresentato internamente in termini di (x^rel_i, y^rel_i)
- metodo evolve(): fa progredire la simulazione di 1 step (delta t)


**Comandi**:
- cmake -S . -B build -G"Ninja Multi-Config" 
(crea la cartella build)
- cmake --build build --config Debug
(linka)
