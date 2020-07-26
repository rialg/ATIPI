# Compresor 
Dividimos en peque;ias partes

    | c | b | d |
| e | a | x | ...                - que valores seteamos cuando estamos en los extremos por ejemplo?
                                        *podemos agregar una fila y columna con los mismos valores que la primer fila/columna?

1) Modo Comun
1.1 MED predictor
    X̂p = {
        min(a,b) if c >= max(a,b)
        max(a,b) if c <= min(a,b)
        a+b-c    if otherwise
    }
1.2 Error
    E = X - X̂p   (X real - X predicta)

1.3, 1.4 NO VAN

1.5 K (needed for Golomb Codes)
    K = techo( log2( A/N ) )  
        - A: suma acumulada de magnitud de errores (E)
        - N: numero total de pixeles en los en los alrededores

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
    NO HAY MODO RAFAGA
