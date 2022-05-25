import struct
import sys

registroCEP = struct.Struct("72s72s72s72s2s8s2s")
siglaColumn = 4

def getStringRecord(record):
    write_str = ''
    for i in range(0,len(record)-1):
        write_str += record[i].decode('latin1')
    write_str += '\n'
    return write_str

UFAtual = None
outputFile = None

with open("../datasets/cep.dat","rb") as f:
    # line = f.read(registroCEP.size)
    line = f.readline()

    while len(line) > 0:
        record = registroCEP.unpack(line)
        UFLida = record[siglaColumn].decode('latin1')

        # write_str = getStringRecord(record)
        # write_str = bytes(write_str, 'latin1')

        if UFLida == UFAtual:
            outputFile.write(line)
            # outputFile.write(write_str)
        else:
            if outputFile:
                outputFile.close()
            outputFile = open(f'cep-{UFLida}.dat',"ab")

            UFAtual = UFLida

            outputFile.write(line)
        line = f.readline()