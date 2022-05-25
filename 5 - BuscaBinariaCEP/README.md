# Busca Binaria:

### Complexidade de tempo

- Melhor caso: O(1)

- Pior caso e em média: O(log(n))

### Demonstração da complexidade por relação de recorrência

```
T(N) = T(N/2) + 1

T(N/2) = T(N/4) + 1

T(N/4) = T(N/8) + 1

T(N) = T(N/8) + 1 + 1 + 1
T(N) = T(N/8) + 3

T(N) = T(N/2^3) + 3N
```

Generalizando:

```
T(N) = T(N/2^k) + k
```

Se N = 2^k, então N/2^k = 1:

```
N = 2^k

k = log(N)
```

Como são necessários k passos para N = 2^k:

```
T(N) = T(1) + log(N)
```
