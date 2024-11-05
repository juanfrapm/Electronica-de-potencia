import serial
import sqlite3
from datetime import datetime
import time

# Configura el puerto serie
ser = serial.Serial(
    port='/dev/serial0',  # Cambiar si estás usando otro puerto
    baudrate=9600,
    timeout=1
)

# Conectar o crear la base de datos SQLite
conn = sqlite3.connect('/var/www/html/basedatos_dist_frec.db')
cursor = conn.cursor()

# Asegúrate de que el puerto esté abierto
if ser.is_open:
    print("Puerto serie abierto correctamente y esperando datos en RX")

# Función para insertar datos en la base de datos
def guardar_en_base_de_datos(dato):
    dato = dato.strip()
    frec = dato[:5]
    dist = dato[5:]
    cursor.execute("INSERT INTO frecuencias(frecuencia) VALUES (?)", (frec,))
    conn.commit()  # Guarda los cambios en la base de datos
    cursor.execute("INSERT INTO distancias(distancia) VALUES (?)", (dist,))
    conn.commit()  # Guarda los cambios en la base de datos
    print(f"Datos guardados en la base de datos: {frec}")
    print(f"Datos guardados en la base de datos: {dist}")

# Leer datos del puerto serial y guardarlos en la base de datos
try:
    while True:
        time.sleep(5)
        data = ser.readline()  # Lee una línea de datos del pin RX
        if data:
            print(data)
            dato = data
            # Guardar en la base de datos
            guardar_en_base_de_datos(dato)
except KeyboardInterrupt:
    print("Lectura interrumpida por el usuario")
finally:
    # Cierra el puerto serie y la conexión a la base de datos
    ser.close()
    conn.close()
    print("Conexión cerrada")