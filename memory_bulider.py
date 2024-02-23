"""
 This file is part of x86emulator-by-Grasol

 x86emulator-by-Grasol is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 3 of the License, or
 (at your option) any later version.

 x86emulator-by-Grasol is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with x86emulator-by-Grasol.  If not, see <http://www.gnu.org/licenses/>.
"""

import sys
import struct
import os



class MemorySlice:
  def __init__(self, lower_bound, upper_bound, name: str):
    self.lower_bound = lower_bound
    self.upper_bound = None if upper_bound == "auto" else upper_bound 
    if type(self.upper_bound) == str:
      print(f"Error: Upper bound: '{self.upper_bound}' must by hex int or 'auto'")
      exit(2)

    self.name = name
    with open(self.name, "rb") as f:
      self.blob = bytearray(f.read())

    self.blob_size = len(self.blob)
    if self.upper_bound == None:
      self.upper_bound = self.lower_bound + self.blob_size

    if self.lower_bound >= self.upper_bound:
      print(f"Error: lower bound is greater or equal than upper bound in map entry: '{self.lower_bound} {self.upper_bound} {self.name}'")
      exit(2)

    
  def getBlob(self):
    dif = self.upper_bound - self.lower_bound - self.blob_size
    if dif >= 0:
      res_size = self.blob_size + dif
      res_blob = self.blob + bytearray(dif)

    else:
      res_size = self.upper_bound - self.lower_bound
      res_blob = self.blob[0:res_size]

    return res_blob, res_size


class Memory:
  def __init__(self, max_size):
    self.max_size = None if max_size == "auto" else max_size
    if type(self.max_size) == str:
      print(f"max_size: '{self.max_size}' must by hex int or 'auto'")
      exit(2)

    self.slices = []

  def addSlice(self, lower_bound, upper_bound, name: str):
    m_slice = MemorySlice(lower_bound, upper_bound, name)
    self.slices.append(m_slice)

  def bulid(self):
    res = bytearray()
    size = 0
    for s in self.slices:
      if s.lower_bound >= size:
        dif = s.lower_bound - size
        blob, blob_size = s.getBlob()
        res += bytearray(dif) + blob
        size += dif + blob_size

      else:
        print(f"Warning: Entries bounds in map overlap '{s.lower_bound} {s.upper_bound} {s.name}'")

        blob, blob_size = s.getBlob()
        res = res[0:s.lower_bound] + blob + res[s.upper_bound:] 
        dif = s.upper_bound - size
        if dif > 0:
          size += dif

    if self.max_size != None:
      if self.max_size >= size:
        dif = self.max_size - size
        size = self.max_size
        res = res + bytearray(dif)
      else:
        size = self.max_size
        res = res[0:size]

    return bytearray(struct.pack("<q", size)) + res, size


class Parse:
  KEY = "KEY"
  VALUE = "VALUE"
  VALUE_MEMORY_SIZE = "VALUE_MEMORY_SIZE"
  MAP = "MAP"
  MAP_LOWER_BOUND = "MAP_LOWER_BOUND"
  MAP_UPPER_BOUND = "MAP_UPPER_BOUND"
  MAP_FILE_NAME = "MAP_FILE_NAME"


def parseWord(word):
  try:
    res = int(word, 16)

  except:
    res = word

  return res


def parseConfig(data: str):
  words = data.split()

  values = {
    Parse.VALUE_MEMORY_SIZE: None,
  }

  map = []

  parse_state = Parse.KEY
  parse_value = Parse.VALUE
  for w in words:
    match parse_state:
      case Parse.KEY:
        match w:
          case "memory_size":
            parse_state = Parse.VALUE
            parse_value = Parse.VALUE_MEMORY_SIZE

          case "map":
            parse_state = Parse.MAP
            parse_value = Parse.MAP_LOWER_BOUND

          case _:
            print(f"key '{w}' is not recognized")
            exit(2)

      case Parse.VALUE:
        value = parseWord(w)
        values[parse_value] = value
        parse_state = Parse.KEY
        parse_value = Parse.VALUE

      case Parse.MAP:
        match parse_value:
          case Parse.MAP_LOWER_BOUND:
            if (w == "end"):
              parse_state = Parse.KEY
              parse_value = Parse.VALUE

            else:
              value = int(w, 16)
              map.append([value, None, None])
              parse_value = Parse.MAP_UPPER_BOUND

          case Parse.MAP_UPPER_BOUND:
            value = parseWord(w)
            map[-1][1] = value
            parse_value = Parse.MAP_FILE_NAME

          case Parse.MAP_FILE_NAME:
            map[-1][2] = w
            parse_value = Parse.MAP_LOWER_BOUND
  
  map = sorted(map)
  lower_bound1 = None
  lower_bound2 = None
  for m in map:
    if None in m:
      print(f"Error: map entry: '{m}' is invalid")
      exit(2)

    lower_bound2 = lower_bound1
    lower_bound1 = m[0]
    if lower_bound1 == lower_bound2:
      print(f"Error: 2 or more map entry start in same lower bound: '{lower_bound1}'")
      exit(2)

  if (values[Parse.VALUE_MEMORY_SIZE] == None):
    print("Warning: Memory size is not set. Value will set to default: 'auto'")


  return values, map    

def main():
  argv = sys.argv
  argc = len(argv)

  if argc <= 1:
    print("usage: python3 memory_bulider.py <config.txt>")
    exit(1)

  input_file_name = argv[1]
  output_file_name = ''.join((os.path.splitext(input_file_name)[0], '.bin'))


  with open(input_file_name, "r") as f:
    config_data = f.read()

  values, map = parseConfig(config_data)

  memory = Memory(values[Parse.VALUE_MEMORY_SIZE])
  for m in map:
    memory.addSlice(m[0], m[1], m[2])

  data, size = memory.bulid()
  with open(output_file_name, "wb") as f:
    f.write(data)

  print(f"Success. Output file have {size} bytes of memory")



if __name__ == "__main__":
  main()
