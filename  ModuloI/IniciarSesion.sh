BASE_DIR="fedora"
TMP_DIR="/tmp/uml"


if ! [ -d $TMP_DIR ]; then
	mkdir $TMP_DIR
fi

if [ -f "$BASE_DIR/kernel32-3.0.4.gz" ]; then
    gunzip -k "$BASE_DIR/kernel32-3.0.4.gz"
    mv "$BASE_DIR/kernel32-3.0.4" $TMP_DIR
else
		echo "ERROR: Falta el archivo del kernel comprimido en .gz"
		rm -rf $TMP_DIR
		exit 1
fi

if [ -f "$BASE_DIR/Fedora14-x86-root_fs.gz" ]; then
    gunzip -k "$BASE_DIR/Fedora14-x86-root_fs.gz"
    mv "$BASE_DIR/Fedora14-x86-root_fs" $TMP_DIR
else
		echo "ERROR: Falta el archivo de fedora root comprimido en .gz"
		rm -rf $TMP_DIR
		exit 1
fi

cp "$BASE_DIR/kernel32-3.0.rar" $TMP_DIR

chmod u+x $TMP_DIR/kernel32-3.0.4
exec $TMP_DIR/kernel32-3.0.4 ubda=$TMP_DIR/Fedora14-x86-root_fs mem=1024m
