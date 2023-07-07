# Minishell
Bienvenido al repositorio de la Minishell de 42. Esta es una implementación básica de una shell en C. Desarrollado por tvillare y javmarti :)

## Descripción

La Minishell es un proyecto que nos permite comprender cómo funcionan las shells y cómo se interpretan los comandos en un sistema operativo. La shell es una interfaz de línea de comandos que nos permite interactuar con el sistema operativo ejecutando comandos y programas.

En este proyecto, hemos desarrollado una versión simplificada de una shell que es capaz de ejecutar comandos internos (built-in commands) y comandos externos (binarios).

## Características

- **Ejecución de comandos internos:** la shell puede ejecutar comandos internos como `cd`, `echo`, `pwd`, `export`, `unset` y `env`.
- Ejecución de comandos externos: la shell puede ejecutar comandos externos proporcionando la ruta absoluta o relativa del binario.
- **Variables de entorno:** la shell es capaz de gestionar variables de entorno mediante los comandos `export` y `unset`.
- **Redirecciones:** la shell puede redireccionar la entrada y salida de los comandos utilizando los operadores `>` (redirección de salida) y `<` (redirección de entrada).
- **Pipes:** la shell admite la ejecución de comandos en tuberías, utilizando el operador `|` para redirigir la salida de un comando a la entrada de otro.
- **Señales:** la shell maneja las señales del sistema como `Ctrl+C`, `Ctrl+D` y `Ctrl+\` para proporcionar un comportamiento adecuado en estas situaciones.

## Requisitos del sistema

- Sistema operativo compatible con POSIX.
- Compilador de C compatible con el estándar C99.
- Biblioteca estándar de C.

## Instalación

1. Clona el repositorio de la Minishell en tu máquina local:

```
git clone https://github.com/SrTonno/Minishell.git
```

2. Accede al directorio del proyecto:

```
cd minishell
```

3. Compila el programa utilizando el Makefile:

```
make
```

4. Ejecuta la Minishell:

```
./minishell
```

## Uso

Una vez que hayas ejecutado la Minishell, puedes empezar a introducir comandos. La sintaxis es similar a la de otras shells conocidas, como Bash o Zsh.

Aquí hay algunos ejemplos de comandos que puedes probar:

- Ejecutar un comando interno:

```
$ cd directorio
```

```
$ echo Hola, mundo!
```

- Ejecutar un comando externo:

```
$ /bin/ls
```

```
$ ./mi_programa
```

- Redireccionar la salida de un comando a un archivo:

```
$ echo Hola > archivo.txt
```

- Redireccionar la entrada de un comando desde un archivo:

```
$ ./mi_programa < archivo.txt
```

- Utilizar tuberías para combinar comandos:

```
$ ls -la | grep .txt
```

## Autores
 
- SrTonno - [Perfil de GitHub](https://github.com/SrTonno) / tvillare - [Perfil de 42](https://profile.intra.42.fr/users/tvillare)
- Elmerlusa - [Perfil de GitHub](https://github.com/Elmerlusa) / javmarti - [Perfil de 42](https://profile.intra.42.fr/users/javmarti)
