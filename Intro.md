# Compresor 
Dividimos en peque;ias partes

    | c | b | d |
| e | a | x | ...                - que valores seteamos cuando estamos en los extremos por ejemplo?

1) Modo Comun
1.1 MED predictor
    X̂p = {
        min(a,b) if c >= max(a,b)
        max(a,b) if c <= min(a,b)
        a+b-c    if otherwise
    }
1.2 Error
    E = X - X̂p   (X real - X predicta)
1.3 Gradiente
    g1 = (d-b)
    g2 = (b-c)
    g3 = (c-a)
1.4 Regiones
    -4 =        x  <= -21
    -3 = -21 <  x  <= -7
    -2 = -7  <  x  <= -3
    -1 = -1  <  x  <   0
     0 =        x  =   0
     1 =  3  >  x  >   0
     2 =  7  >  x  >=  3
     3 =  21 >  x  >   7
     4 =        x  >=  21

    -gradiente-[g1, g2, g3] --> [q1, q2, q3]-regiones-
        - mantener conteo de vector de regiones (contextos) -(######como mantenemos el track of sign???)
        - si g1 <0 hay que cambiar signo de todos los elementos del vector
        - si [q1, q2, q3] = [0, 0, 0]====> $$ MODO RAFAGA $$
1.5 K (needed for Golomb Codes)
    K = techo( log2( A/N ) )  
        - A: suma acumulada de magnitud de errores (E)
        - N: numero total de context samples (cuantas veces se repitio el mismo [q1, q2, q3])
1.6 Rice Mapping
    M(E) = 2(E) - u(E)
        u(x) = {
            1  if x < 0
            0  otherwise
        }
            
1.7 Golomb
    m = 2^K
    cociente = M(E) mod m ===> encode w/BINARY
       resto = M(E) div m ===> encode w/UNARY
    G(M(E)) ====> encoded(cociente++resto)




2) Modo rafaga
    block-MELCODE --- wat?