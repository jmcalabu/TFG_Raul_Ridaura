# TFG_Raul_Ridaura

Proyecto desarrollado por Raúl para Trabajo de Fin de Grado (TFG) de la ETSII de València.

# Proyecto de Control y Estructura con ESP32 y MATLAB

Este proyecto integra el control de un sistema físico mediante un microcontrolador ESP32, código de control en MATLAB, y diseño mecánico en FreeCAD. Está pensado para automatizar un mecanismo o sistema que posiblemente interactúa con agua (por la presencia de una piscina en los planos) y motores.

## Estructura del repositorio

### Controlador
- **Control_esp32.ino**  
  Código en Arduino para el microcontrolador ESP32. Este script maneja la lógica principal de control del hardware conectado.

### Scripts MATLAB
- **codigomovimiento.m**  
  Control de movimiento del sistema. Define trayectorias o comandos específicos.
- **enviarDatosESP32.m**  
  Comunicación entre MATLAB y el ESP32 mediante puerto serie.
- **esperarFinalizacion.m**  
  Rutina de sincronización que espera a que el sistema físico complete una acción.

### Diseño CAD (FreeCAD)
- **Estructura_aluminio.FCStd**  
  Diseño de la estructura principal en aluminio.
- **estructura_motor_completa.FCStd**  
  Ensamblaje completo que incluye el motor.
- **Pieza3dmotores.FCStd**  
  Pieza impresa en 3D para soporte o acople de motores.
- **Plano plaquita de metal.FCStd**  
  Diseño en lámina metálica, probablemente para montaje o soporte.
- **piscina_cotas.FCStd**  
  Diseño con cotas de una piscina, puede ser parte del entorno físico de pruebas o una aplicación hidráulica.

### Documentación
- **README.md**  
  Este archivo, con información general del proyecto.

## Requisitos

- **Software**
  - Arduino IDE
  - MATLAB
  - FreeCAD

- **Hardware**
  - Microcontrolador ESP32
  - Motores
  - Estructura mecánica basada en los planos proporcionados
  - Elementos de conexión (puerto serie, cables, etc.)

## Cómo usar

1. Abrir y cargar `Control_esp32.ino` en el ESP32 desde el Arduino IDE.
2. Ejecutar los scripts MATLAB en el orden necesario para enviar instrucciones al ESP32.
3. Verificar la estructura física en FreeCAD con los archivos `.FCStd` para ensamblaje y diseño.
4. Seguir instrucciones específicas para sincronización y ejecución de movimientos.

## Tutores: Instituto Universitario de Matemática Pura y Aplicada (UPV)

Jose M. Calabuig Rodríguez
Lluis M. Garcia Raffi
Vicent Romero Gaarcia



