import struct
import sys

if len(sys.argv) != 2:
  print(f"Uso python {sys.argv[0]} [CEP]")
  quit()

registroCEP = struct.Struct("72s72s72s72s2s8s2s")
cepColumn = 5

def buscaBin(inicio, fim, file, cepProcurado):
  count = 0

  while inicio <= fim:
    meio = (inicio + fim) // 2
    file.seek(meio * registroCEP.size, 0)
    line = file.read(registroCEP.size)
    # line = file.readline()
    count += 1

    record = registroCEP.unpack(line)

    cep_just_read = record[cepColumn].decode('latin1')

    if cepProcurado == cep_just_read:
      return file.tell(), count
    elif cepProcurado > cep_just_read:
      inicio = meio + 1
    else:
      fim = meio - 1
  return -1

with open('../datasets/cep_ordenado.dat', 'rb') as f:
  f.seek(0, 2)
  tamanho_bytes = f.tell()
  tamanho_registros = tamanho_bytes // registroCEP.size
  
  inicio = 0
  fim = tamanho_registros - 1

  idx, count = buscaBin(inicio, fim, f, sys.argv[1])

  if idx < 0:
    print("Nao encontrou")
  else:
    # f.seek(-1 * registroCEP.size, 1)
    # a partir da posição atual, volta 1 registro para que a proxima leitura seja o cep certo

    f.seek(idx - (registroCEP.size * 1), 0) 
    # a partir do inicio do arquivo, define a posição como sendo a posição do registro anterior
    print(f.readline().decode('latin1'))

  print(f"Enderecos lidos: {count}");