# TFG Raul Ridaura: Diseño, programación e implementación de robot móvil para análisis acústico

Proyecto desarrollado por Raúl para Trabajo de Fin de Grado (TFG) de la ETSII de València.

## Resumen

La medición de ondas sonoras es una herramienta muy útil en diversos ámbitos, desde la caracterización acústica de habitaciones hasta aplicaciones industriales como la detección temprana de fallos en maquinaria, a través de la identificación de sonidos anómalos. Sin embargo, esta tarea puede resultar laboriosa y poco eficiente cuando se realiza de forma manual, especialmente en espacios amplios que requieren un muestreo exhaustivo.

Con el fin de automatizar este proceso y hacerlo más eficiente, el presente Trabajo de Fin de Grado tiene como objetivo principal el diseño, fabricación e implementación de un prototipo de robot móvil autónomo, capaz de desplazarse por una zona determinada mientras realiza mediciones de ondas sonoras. El sistema está concebido para operar de manera independiente una vez configurado, permitiendo así agilizar significativamente la toma de datos acústicos y reduciendo la necesidad de intervención humana.

El proyecto abarca tanto el desarrollo mecánico y electrónico del robot como la implementación del software de control, diseñado en entorno MATLAB, desde donde se definen los puntos de medición y se gestiona el movimiento del robot. Finalmente, se llevarán a cabo una serie de pruebas experimentales para verificar el correcto funcionamiento del prototipo y evaluar su capacidad para cumplir con los objetivos propuestos.

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

Jose M. Calabuig Rodríguez (jmcalabu)
 
Lluis M. Garcia Raffi (lmgarcia)

Vicent Romero Gaarcia (virogar1)



