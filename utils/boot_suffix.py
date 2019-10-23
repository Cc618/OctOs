# Returns data to put after the boot :
# the number of sectors to read in stdout in a dword format

import sys
import subprocess
import struct

# LOAD_SECTOR #
# Get the size of the file in string
p = subprocess.run("ls -nl " + sys.argv[1] + " | awk '{print $5}'", shell=True, text=True, capture_output=True)

# The kernel size in bytes
kernel_size = int(p.stdout)

sectors = (kernel_size - 1) // 512 + 1

# Write bytes to stdout
sys.stdout.buffer.write(struct.pack("b", sectors))

# MAGIC_NUMBER #
sys.stdout.buffer.write(struct.pack("<H", 0xAA55))

