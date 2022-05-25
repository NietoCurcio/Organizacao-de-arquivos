# Cópia de arquivos byte a byte

copia1.c faz a cópia de um arquivo, isso é feito através das funções fgetc e fput, copiando um byte de cada vez.

Ao executar um programa, três arquivos são abertos:

- stdin: entrada padrão
- stdout: saída padrão
- stderr: saída de erro padrão

É possível redirecionar a entrada ou saída desses três arquivos:

```shell
# redirecionando a entrada padrão ('<' ou '0<')

./programa < entrada.txt
```

```shell
# redirecionando a saída padrão ('>' ou '1>')

shell./programa > saida.txt
```

```shell
# redirecionando a saída de erro padrão

shell./programa 2> saida_err.txt
```

O comando "cat" do Linux é uma forma de demonstrar o redirecionamento, exemplo com uso do "grep":

```shell
cat > saída.txt

a
b
c
# hit end of file (CTRL + Z)

cat > saida.txt

cat < saida.txt > saida_2.txt

cat < saida_2.txt | grep 'a\|b\|c'
```
