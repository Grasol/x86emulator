import os
import struct
import sys

NULL_ARG = 0xff

MNEMONIC = 0
MAP = 1
PFX = 2
OPCODE = 3
MOD = 4
NNN = 5
RM = 6
SPECIAL = 7
OPCBITS = 8


class InstrOne:
  BYTES = 8
  def __init__(self):
    self.map = NULL_ARG
    self.pfx = NULL_ARG
    self.opcode = NULL_ARG
    self.mod = NULL_ARG
    self.nnn = NULL_ARG
    self.rm = NULL_ARG
    self.special = NULL_ARG
    self.opcbits = NULL_ARG


class InstrList:
  def __init__(self):
    self.ilist = [];

  def add(self, line: list):
    instr = InstrOne()
    self.ilist.append(instr)

    instr.map = int(line[MAP])

    match line[PFX]:
      case "np": 
        instr.pfx = 0
      case "66":
        instr.pfx = 1
      case "f3":
        instr.pfx = 2
      case "f2":
        instr.pfx = 3

    instr.opcode = int(line[OPCODE], 16)

    if (line[MOD] != "-"):
      match line[MOD]:
        case "m":
          instr.mod = ord('m')
        case _:
          instr.mod = int(line[MOD])

    if (line[NNN] != "-"):
      instr.nnn = int(line[NNN])

    if (line[RM] != "-"):
      instr.rm = int(line[RM])

    if (line[SPECIAL] != "-"):
      instr.special = int(line[SPECIAL], 16)

    if (line[OPCBITS] != "-"):
      instr.opcbits = int(line[OPCBITS])

  def print(self):
    for i in self.ilist:
      print(i.map, i.pfx, i.opcode, i.mod, i.nnn, i.rm, i.special, i.opcbits)

    print(f"Printed {len(self.ilist)} lines")

  def bulid(self):
    size = len(self.ilist)
    data = bytearray(struct.pack("<q", size))

    for i in self.ilist:
      byte_line = bytearray(InstrOne.BYTES)
      byte_line[0] = i.map & 0xff
      byte_line[1] = i.pfx & 0xff
      byte_line[2] = i.opcode & 0xff
      byte_line[3] = i.mod & 0xff
      byte_line[4] = i.nnn & 0xff
      byte_line[5] = i.rm & 0xff
      byte_line[6] = i.special & 0xff
      byte_line[7] = i.opcbits & 0xff

      data += byte_line

    return data, size


def main():
  argv = sys.argv
  argc = len(argv)

  if (argc <= 1):
    print("usage: python3 instr_list_bulider.py <list.txt>")
    exit(1)

  input_file_name = argv[1]
  output_file_name = ''.join((os.path.splitext(input_file_name)[0], '.bin'))

  ilist = InstrList()

  with open(input_file_name, "r") as f:
    data = f.read()

  lines = data.splitlines()
  for l in lines:
    l = l.split()
    if (not l):
      continue

    if (l[0][0] == "#"):
      continue

    ilist.add(l)

  data, size = ilist.bulid()
  with open(output_file_name, "wb") as f:
    f.write(data)

  print(f"Bulided {size} instructions")


if __name__ == "__main__":
  main()

