import struct

BATCHES = 8

registroCEP = struct.Struct("72s72s72s72s2s8s2s")
cepColumn = 5

def mergeSortedBatches(mergeState):
  print("\nProcessing:")
  print(f"left batch: {mergeState['left']}")
  print(f"right batch: {mergeState['right']}")
  print(f"Pair batches index: {mergeState['pair_idx']}")
  print(f"Batch to be merged: {mergeState['next']}")

  file_a = open(f'batch_{mergeState["left"]}.dat', 'rb')
  file_b = open(f'batch_{mergeState["right"]}.dat', 'rb')
  file_c = open(f'batch_{mergeState["next"]}.dat', 'wb')

  line_a = file_a.read(registroCEP.size)
  line_b = file_b.read(registroCEP.size)
  while(line_a and line_b):
    register_a = registroCEP.unpack(line_a)
    register_b = registroCEP.unpack(line_b)
    if register_a[cepColumn].decode('latin1') <= register_b[cepColumn].decode('latin1'):
      file_c.write(line_a)
      line_a = file_a.read(registroCEP.size)
    else:
      file_c.write(line_b)
      line_b = file_b.read(registroCEP.size)

  while line_a:
    file_c.write(line_a)
    line_a = file_a.read(registroCEP.size)
  
  while line_b:
    file_c.write(line_b)
    line_b = file_b.read(registroCEP.size)

  mergeState['left'] += 2 
  mergeState['right'] += 1 if mergeState['pair_idx'] == (BATCHES - 1) else 2
  mergeState['next'] += 1

  file_a.close()
  file_b.close()
  file_c.close()

def writeSortedBatch(batch_size, batch_idx, file):
  data = file.read(batch_size * registroCEP.size)
  
  addresses = []
  for i in range(batch_size):
    start = i * registroCEP.size
    end = start + registroCEP.size
    address = data[start : end]
    address = registroCEP.unpack_from(address)
    addresses.append(address)

  sorted_addresses = sorted(addresses, key=lambda address: address[cepColumn].decode('latin1'))
  sorted_addresses = list(map(lambda address: b''.join(address), sorted_addresses))
  sorted_addresses = b''.join(sorted_addresses)

  with open(f'batch_{batch_idx}.dat', 'wb') as output:
    output.write(sorted_addresses)

def writeBatches(totalRegisters, file):
  total_written = 0

  for i in range(BATCHES):
    if i == (BATCHES - 1):
      batch_size = totalRegisters - total_written # get remaining data
    else:
      batch_size = totalRegisters // BATCHES
    writeSortedBatch(batch_size, i, file)
    total_written += batch_size

if __name__ == '__main__':
  with open('../datasets/cep.dat', 'rb') as f:
    f.seek(0, 2) # goes to the last byte of the file
    tamanho_bytes = f.tell()
    qtd = tamanho_bytes // registroCEP.size

    f.seek(0, 0) # rewind

    writeBatches(qtd, f)
  print(f"Sorted data written in {BATCHES} batches")

  pair_idx = 1

  mergeState = {
    'left': 0,
    'right': 1,
    'pair_idx': pair_idx,
    'next': BATCHES
  }

  while mergeState['pair_idx'] < BATCHES:
    mergeSortedBatches(mergeState)
    mergeState['pair_idx'] += 1

  print("Sorted data merged")