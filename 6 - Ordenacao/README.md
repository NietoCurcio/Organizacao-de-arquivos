# Ordenação de arquivos:

## Quick sort

### Complexidade de tempo

- Melhor caso e em média: O(nlog(n))

- Pior caso: O(n^2)

### Demonstração da complexidade por relação de recorrência

```
T(N) = 2T(N/2) + N

T(N/2) = 2T(N/4) + N/2

T(N/4) = 2T(N/8) + N/4

T(N) = 2T(2T(2T(N/8) + N/4) + N/2) + N
T(N) = 2T(4T(N/8) + N/2 + N/2) + N
T(N) = 8T(N/8) + 3N

T(N) = 2^3T(N/2^3) + 3N
```

Generalizando:

```
T(N) = 2^kT(N/2^k) + kN
```

Seja N = 2^k, aplicando log dos dois lados da equação:

```
log(N) = k

T(N) = NT(N / N) + log(N)N
T(N) = NT(1) + Nlog(N)
```

Visto que se sabe o resultado de T(1):

```
T(N) = N*log(N) para a média dos casos
```

Caso a escolha do pivô seja o pior caso possível, o particionamento resulta na seguinte relação de recorrência:

T(N) = T(N - 1) + N
