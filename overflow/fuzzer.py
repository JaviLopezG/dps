# fuzzer.py
import sys
import subprocess

# El programa vulnerable espera el argumento 1 (argv[1])
# Este script intentará longitudes crecientes de la cadena.

try:
    longitud = 1
    while longitud < 3000: # Iremos hasta 300 bytes para estar seguros
        # Crea la cadena de prueba: 
        # Rellena con 'A's ('\x41') hasta la longitud actual
        cadena = b'A' * longitud 
        
        # print(f"[+] Intentando longitud: {longitud} bytes")
        
        # Ejecuta el programa vulnerable con la cadena como argumento
        # Nota: 'vulnerable' es el nombre del ejecutable
        # El programa debe estar en el mismo directorio.
        subprocess.check_call(['./vulnerable', cadena])
        
        longitud += 1
        
    print("[!] Fuzzing completado sin crash aparente (o excedió el límite)")

except Exception as e:
    print(f"[!] El programa falló a la longitud {longitud} con el error: {e}")
    sys.exit()
