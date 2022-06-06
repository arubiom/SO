var=0
basura=0

for ((i=0 ; i<$1 ; i++)); do
	basura=$(( 3/2 ))
	var=$(( $var+1 ))
done

printf "El resultado es: $var\n"
