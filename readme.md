## lexer
El lexer se encarga de dividir la cadena de entrada en "tokens", que son cadenas de caracteres con funciones especificas.

> Ejemplos

>>"ls -al | grep a<input.txt >>hola.txt" se transformaría en
[ "ls", "-al", "|", "grep", "a", "<", "input.txt", ">>", "hola.txt" ]

>>"hola$sque' tal'" se transformaría en
[ "hola", "$sque", "' tal'" ]

>>"hola $s que tal'" se transformaría en
[ "hola ", "$s", " que tal'" ]

>>echo ""hola adios'' "que 'tal" se tranformaría en
[ "echo", """", "hola", "adios", "''" "que 'tal" ]

>> // echo "hola que tal $estas jeje"
	// echo hola "como $ $estas tu" yo estoy ' muy bien jaja :)'

## Parser
El Parser se encarga de unir los tokens que forman un comando mediante un (char**)

> Ejemplos

>>"ls -al | grep a<input.txt >>hola.txt" se transformaría en
[ "ls-al", "|", "grepa", "<", "input.txt", ">>", "hola.txt" ]

>>"hola$sque' tal'" se transformaría en
[ "hola$sque' tal'" ]

>> "echo "Hola" | grep 'H' | wc -c > file.txt" se transformaría en
[echo"Hola", "|", "grep'H', "|", "wc-l", ">", "file.txt"]

>> "<< fin cat -benstuv > file.txt" se transformaría en
["<<", "fin", "cat-benstuv", ">", "file.txt]
