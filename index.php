<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Registro de Alarma y Datos Históricos</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f0f2f5;
            display: flex;
            justify-content: center;
            align-items: center;
            flex-direction: column;
            height: 100vh;
            margin: 0;
            overflow-y: auto; /* Permitir desplazamiento vertical si el contenido total excede la altura de la pantalla */
        }
        .container, .history {
            background-color: #ffffff;
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
            text-align: center;
            width: 80%;
            max-width: 600px;
            margin-bottom: 20px;
        }
        .history {
            max-height: 300px; /* Limitar la altura del historial */
            overflow-y: auto; /* Agregar desplazamiento cuando haya muchos datos */
        }
        .header {
            color: #333;
            font-size: 24px;
            margin-bottom: 20px;
        }
        .data, .table-header {
            font-size: 18px;
            margin: 10px 0;
        }
        .table-header {
            font-weight: bold;
            color: #333;
        }
        .active {
            color: #ff4d4d;
            font-weight: bold;
        }
        .inactive {
            color: #4CAF50;
            font-weight: bold;
        }
        table {
            width: 100%;
            border-collapse: collapse;
            margin-top: 20px;
        }
        th, td {
            padding: 10px;
            border: 1px solid #ddd;
            text-align: center;
        }
        th {
            background-color: #f2f2f2;
        }
        form {
            margin-bottom: 20px;
        }
    </style>
</head>
<body>

<div class="container">
    <div class="header">Estado de la Alarma</div>

    <?php
    try {
        // Conectar a la base de datos SQLite
        $db = new PDO('sqlite:/var/www/html/basedatos_dist_frec.db');

        // Consultar el primer valor de distancia y frecuencia
        $distancia_result = $db->query('SELECT distancia FROM distancias ORDER BY timestamp DESC LIMIT 1');
        $frecuencia_result = $db->query('SELECT frecuencia FROM frecuencias ORDER BY timestamp DESC LIMIT 1');
        
        $distancia_row = $distancia_result->fetch(PDO::FETCH_ASSOC);
        $frecuencia_row = $frecuencia_result->fetch(PDO::FETCH_ASSOC);

        // Verificar que se obtuvo un resultado
        if ($distancia_row && $frecuencia_row) {
            // Convertir los valores a números flotantes
            $distancia = (float)$distancia_row['distancia'];
            $frecuencia = (float)$frecuencia_row['frecuencia'];

            // Mostrar frecuencia y distancia
            echo "<div class='data'>Frecuencia: <span>$frecuencia Hz</span></div>";
            echo "<div class='data'>Distancia: <span>$distancia cm</span></div>";

            // Determinar el estado de la alarma
            $alarma = "inactiva";
            $razon = "";

            if ($frecuencia < 40.00) {
                $alarma = "activa";
                $razon = "frecuencia";
            } elseif ($frecuencia > 60.00) {
                $alarma = "activa";
                $razon = "frecuencia";
            } elseif ($distancia < 30.00) {
                $alarma = "activa";
                $razon = "distancia";
            }

            // Mostrar el estado de la alarma
            if ($alarma == "activa") {
                echo "<div class='data active'>Alarma activa por $razon</div>";
            } else {
                echo "<div class='data inactive'>Alarma inactiva</div>";
            }
        } else {
            echo "<div class='data'>No se encontraron datos en la base de datos.</div>";
        }
    } catch (PDOException $e) {
        echo "<div class='data'>Error: " . $e->getMessage() . "</div>";
    }
    ?>
</div>

<div class="history">
    <form method="GET" action="">
        <label for="date_min">Fecha mínima:</label>
        <input type="date" id="date_min" name="date_min" required>
        <label for="date_max">Fecha máxima:</label>
        <input type="date" id="date_max" name="date_max" required>
        <button type="submit">Consultar</button>
        <button type="button" onclick="location.reload();">Recargar</button>
    </form>

    <?php
    if (isset($_GET['date_min']) && isset($_GET['date_max'])) {
        $date_min = $_GET['date_min'];
        $date_max = $_GET['date_max'];

        try {
            // Consultar los datos en el rango de fechas en ambas tablas
            $query_distancias = $db->prepare('SELECT * FROM distancias WHERE timestamp BETWEEN :date_min AND :date_max');
            $query_frecuencias = $db->prepare('SELECT * FROM frecuencias WHERE timestamp BETWEEN :date_min AND :date_max');
            $query_distancias->bindParam(':date_min', $date_min);
            $query_distancias->bindParam(':date_max', $date_max);
            $query_frecuencias->bindParam(':date_min', $date_min);
            $query_frecuencias->bindParam(':date_max', $date_max);
            $query_distancias->execute();
            $query_frecuencias->execute();
            
            $distancias_records = $query_distancias->fetchAll(PDO::FETCH_ASSOC);
            $frecuencias_records = $query_frecuencias->fetchAll(PDO::FETCH_ASSOC);

            // Mostrar los registros en una tabla
            if ($distancias_records && $frecuencias_records) {
                echo "<div class='table-header'>Historial de Mediciones</div>";
                echo "<table>";
                echo "<tr><th>Fecha</th><th>Frecuencia (Hz)</th><th>Distancia (cm)</th></tr>";
                foreach ($distancias_records as $index => $record) {
                    $frecuencia = $frecuencias_records[$index]['frecuencia'] ?? "N/A";
                    $distancia = $record['distancia'] ?? "N/A";
                    $fecha = htmlspecialchars($record['timestamp']);
                    
                    echo "<tr><td>$fecha</td><td>$frecuencia</td><td>$distancia</td></tr>";
                }
                echo "</table>";
            } else {
                echo "<div class='data'>No se encontraron registros en el rango de fechas seleccionado.</div>";
            }
        } catch (PDOException $e) {
            echo "<div class='data'>Error: " . $e->getMessage() . "</div>";
        }
    }
    ?>
</div>

</body>
</html>
