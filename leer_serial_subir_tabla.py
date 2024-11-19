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
    frec = dato[:5]  # Frecuencia (suponiendo que es la primera parte del dato)
    dist = dato[5:]  # Distancia (resto del dato)
    
    # Obtener fecha y hora actuales
    timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    
    # Insertar los datos en la base de datos con fecha y hora
    cursor.execute("INSERT INTO frecuencias(frecuencia, timestamp) VALUES (?, ?)", (frec, timestamp))
    cursor.execute("INSERT INTO distancias(distancia, timestamp) VALUES (?, ?)", (dist, timestamp))
    conn.commit()  # Guarda los cambios en la base de datos
    
    print(f"Datos guardados en la base de datos: Frecuencia={frec}, Distancia={dist}, Timestamp={timestamp}")

# Leer datos del puerto serial y guardarlos en la base de datos
try:
    while True:
        tiempo = time.time()
        while time.time() - tiempo < 5:
            data = ser.readline()  # Lee una línea de datos del pin RX
        if data:
            print(data)
            dato = data.strip()  # Decodifica y quita espacios innecesarios
            # Guardar en la base de datos
            guardar_en_base_de_datos(dato)
except KeyboardInterrupt:
    print("Lectura interrumpida por el usuario")
finally:
    # Cierra el puerto serie y la conexión a la base de datos
    ser.close()
    conn.close()
    print("Conexión cerrada")
