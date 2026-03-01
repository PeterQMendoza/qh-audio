<p align="center">
    <img src="https://github.com/PeterQMendoza/qhawariy/blob/master/qhawariy/static/img/logo_qhawariy_color.svg" width="180px" height="180px">
</p>

# Construir wav
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=C%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=fff)

Programa que construye archivo wav con c++

## Instalación
1. Clona este repositorio:
    ```bash
    git clone https://github.com/PeterQMendoza/qh-audio.git

2. Ve al directorio del proyecto:
    ```bash
    cd nombredelproyecto

3. Crea un directorio build:
    ```bash
    mkdir build

4. Compila con cmake dentro build/:
    ```bash
    cmake ..

5. Compila con Ninja utilizando build.ninja, dentro build/:
    ```bash
    ninja -f build.ninja

6. Ejecuta el programa.exe:
    ```bash
    programa.exe

7. Usa un reproductor de audio para reproducir 'waform.wav':
    audacity

## Convención de nombres de ramas para nueva funcionalidad o ampliación de codigo
### Formato:
`feature/[MODULO]-[DESCRIPCION]-[VERSION|TAG|ID]`

### Reglas:
- Usa el prefijo `feature/` para indicar nuevos módulos.
- Describe brevemente el módulo y la funcionalidad que estás añadiendo.
- Usa guiones para separar palabras.
- Opcional: Agrega identificadores de versiones o números de tickets.

### Ejemplos:
- `feature/auth-login` - Nuevo módulo de inicio de sesión.
- `feature/cart-management` - Funcionalidad para la gestión del carrito de compras.
- `feature/reporting-tool-v1` - Módulo de generación de reportes, versión inicial.

## Convención de nombres de ramas para corrección de errores
Para la corrección de errores, sigue este esquema de nomenclatura:
- **Prefijo**: Usa `fix/` para indicar que la rama corrige un error.
- **Formato**: `[fix/]-[TIPO]-[MODULO]-[SEVERIDAD]-[ID]`

### Desglose:
- **TIPO**:
    -`BUG`: Error en el funcionamiento del sistema.
    -`UI`: Problemas relacionados con la interfaz de usuario.
    -`API`: Problema con la comunicación o respuesta de la API.
    -`DB`: Problema en la Base de Datos.
    -`SEC`: Problema de seguridad.
- **MODULO**: Nombre abreviado, en 4 letras, del módulo afectado (por ejemplo: AUTH para la autenticacion, etc)
- **SEVERIDAD**:
    -`CRIT`: Critico, necesita solución inmediata.
    -`HIGH`: Alta prioridad, solución prioritaria.
    -`MED`: Media prioridad, puede esterar un poco más.
    -`LOW`: Baja prioridad, mejoras menores.
- **ID**: Identificador incremental único (001, 002, ...).

### Ejemplos:
- `fix/BUG-AUTH-HIGH-003`: Error de inicio de sesión con prioridad alta.
- `fix/UI-VIAJ-MED-001`: Problema con prioridad media en la interfaz de viaje

### Gestión
1. El equipo de testing debe registrar los errores utilizando esta convención.
2. Los desarrolladores deben referirse a este código en los commits relacionados.
3. El equipo debe usar el código en sus herramientas de seguimiento como Jira, Trello, o GitHub Issues.

### Convención de COMMITS en código de error:
- Código: 
    ```bash
    git commit -m "Corrige BUG-AUTH-HIGH-003: Error de autenticación con credenciales válidas"

## License
Qhawariy software con licencia open-sourced software bajo la [BSD 3-Clause License].(https://opensource.org/licenses/BSD-3-Clause)
