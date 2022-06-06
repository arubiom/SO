# Ejercicios prácticas Sistemas Operativos

Alejandro Rubio Martínez

## Módulo I

### Sesión 1

###### Actividad 1.1

El script para ejecuatr el UML suponiendo que los archivos necesarios se encuentran en una carpeta llamada fedora al mismo nivel que el script (necesaria orden ```gunzip```):

```BASH
BASE_DIR="fedora"
TMP_DIR="/tmp/uml"


if ! [ -d $TMP_DIR ]; then
	mkdir $TMP_DIR
fi

if [ -f "$BASE_DIR/kernel32-3.0.4.gz" ]; then
    gunzip -k "$BASE_DIR/kernel32-3.0.4.gz"
else
		if ! [ -f "$BASE_DIR/kernel32-3.0.4" ]; then
				echo "ERROR: Falta el archivo del kernel"
				rm -rf $TMP_DIR
				exit 1
		fi
fi
mv "$BASE_DIR/kernel32-3.0.4" $TMP_DIR

if [ -f "$BASE_DIR/Fedora14-x86-root_fs.gz" ]; then
    gunzip -k "$BASE_DIR/Fedora14-x86-root_fs.gz"
else
		if ! [ -f "$BASE_DIR/Fedora14-x86-root_fs" ]; then
        echo "ERROR: Falta el archivo de fedora root"
        rm -rf $TMP_DIR
        exit 1
		fi
fi
mv "$BASE_DIR/Fedora14-x86-root_fs" $TMP_DIR

cp "$BASE_DIR/kernel32-3.0.rar" $TMP_DIR

chmod u+x $TMP_DIR/kernel32-3.0.4
exec $TMP_DIR/kernel32-3.0.4 ubda=$TMP_DIR/Fedora14-x86-root_fs mem=1024m
```

###### Actividad 1.2

El contenido de /etc/default/useradd es:

```bash
# useradd defaults file
GROUP=500
HOME=/home
INACTIVE=-1
EXPIRE=
SHELL=/bin/bash
SKEL=/etc/skel
CREATE_MAIL_SPOOL=yes
```

El contenido de /etc/login.defs (uncommented) es:

```bash
#QMAIL_DIR	Maildir
MAIL_DIR	/var/spool/mail
#MAIL_FILE	.mail

PASS_MAX_DAYS	99999
PASS_MIN_DAYS	0
PASS_MIN_LEN	5
PASS_WARN_AGE	7

UID_MIN			  500
UID_MAX			60000

GID_MIN			  500
GID_MAX			60000

#USERDEL_CMD	/usr/sbin/userdel_local

CREATE_HOME	yes

UMASK           077

USERGROUPS_ENAB yes

ENCRYPT_METHOD SHA512 
```

Para crear un nuevo usuario utilizamos el comando ```useradd <nombre>```. Vemos entonces que en el fichero /etc/passwd ha aparecido la línea ```pepe:x:500:500::/home/pepe:/bin/bash```, y en el fichero /etc/group la línea ```pepe:x:500:```. Ahora veamos el /home:

![Captura de pantalla 2021-09-20 a las 13.28.50](/Users/alejandrorubiomartinez/Library/Application Support/typora-user-images/Captura de pantalla 2021-09-20 a las 13.28.50.png)

Podemos observar como todo ha salido según lo esperado.

###### Actividad 1.3

 1. Se crean tres usuarios, el primero se le borrará su cuenta en un día (cambiar la línea ```PASS_MAX_DAYS```en /etc/login.defs), el segundo no dispondrá de ```/home``` (cambiar la línea `CREATE_HOME` esta vez) y el tercero con los parámetros estándares.

 2. Se utiliza el comando `userdel` para borrar los dos primeros y podemos observar como el primero sólo deja su directorio `/home`, mientras que el del segundo se especificó que no se creara.

 3. Accedemos al tercer usuario y utilizamos `ls -a /home` para ver lo siguiente:

    ​	![Captura de pantalla 2021-09-21 a las 19.10.04](/Users/alejandrorubiomartinez/Library/Application Support/typora-user-images/Captura de pantalla 2021-09-21 a las 19.10.04.png)

    ​	Podemos ver como los únicos archivos que existen se encuentran ocultos y son los archivos básicos para la configuración del 	bash.

###### Actividad 1.4

Por orden veremos el nombre de usuario, una x que marca que la contraseña se encuentra en /etc/passwd, el UID ( ID del usuario), el GID (ID del grupo), información del ID del usuario, la ruta del directorio de inicio y la ruta de un comando o shell asociado.

###### Actividad 1.5

El archivo /etc/shadow contiene información sobre la contraseñas de los usuarios, por lo que solo tendrá permiso para verlo el root, por lo que entonces al intentar visualizarlo con otro usuario da error de permisos.

###### Actividad 1.6

1. Voy a empezar creando tres usuarios distintos pepe, paco, manolo (`useradd <nombre>`), y dos grupos (`groupadd <nombre>`) llamados informáticos y matemáticos.

   Ahora utilizamos la orden `gpasswd -a <usuario> <grupo>` para añadir pepe y paco a informaticos y manolo a matemáticos. Con la orden `groups <usuarios>` podemos ver a que grupo pertenecen:

   ![Captura de pantalla 2021-09-21 a las 13.53.42](/Users/alejandrorubiomartinez/Library/Application Support/typora-user-images/Captura de pantalla 2021-09-21 a las 13.53.42.png)

2. Veamos lo que ocurre:

   ![Captura de pantalla 2021-09-21 a las 13.56.43](/Users/alejandrorubiomartinez/Desktop/Captura de pantalla 2021-09-21 a las 13.56.43.png)

   Podemos observar que primero nos dará el id de usuario ( 0 por ser el root), y luego  todos los grupos a los que perteence.

###### Actividad 1.7

Utilizamos `find / kernel32-3.0.4.gz`

/home/parallels/Desktop/Parallels Shared Folders/Home/Desktop/ugr/So/fedora/kernel32-3.0.4.gz

###### Actividad 1.8

En la carpeta /var/tmp en la que el tiempo que se mantienen los archivos depende de la distro de la que usemos.

###### Actividad 1.9

Visualicemos el archivo /etc/fstab:

```bash

# /etc/fstab
#
LABEL=ROOT					/		auto	noatime 1 1
tmpfs						/dev/shm	tmpfs	defaults 0 0
tmp						/tmp		tmpfs	rw,mode=1777,fscontext=system_u:object_r:tmp_t:s0	0 0
devpts						/dev/pts	devpts	gid=5,mode=620	0 0
sysfs						/sys		sysfs	defaults 0 0
proc						/proc		proc	defaults 0 0
```

Ahora el archivo /etc/mtab:

```bash
LABEL=ROOT / auto rw,noatime 0 0
proc /proc proc rw 0 0
sysfs /sys sysfs rw 0 0
devpts /dev/pts devpts rw,gid=5,mode=620 0 0
tmpfs /dev/shm tmpfs rw 0 0
/tmp /tmp tmpfs rw,mode=1777 0 0
none /proc/sys/fs/binfmt_misc binfmt_misc rw 0 0
```

La única diferencia entre ambos fichero es que fstab muestra los sistemas de archivos que se montarán cuando se arranque el sistema mientras que mtab muestra los montados actualmente.

###### Actividad 1.10

Por orden lo que podemos ver en cada línea es:

El dispositivo en el que se encuentra montado, el punto de montaje, el tipo de sistemas de archivos, las opciones, que son las siguientes:

- **async**: las escrituras al filesystem se demoran, es decir que no se hacen en el momento sino que se hacen varias escrituras juntas. Esto da un mayor rendimiento, aunque si el sistema se cuelga, apaga o el filesystem se desmonta, los datos se pederán si aún no han sido escritos.
- **auto**: el sistema de archivos será montado automáticamente al iniciar el sistema o al ejecutar el comando mount -a.
- **noauto**: debe ser montado explícitamente.
- **defaults**: utiliza las opciones por defecto, que son rw, suid, dev, exec, auto, nouser, async.
- **ro**: monta el filesystem como de sólo lectura.
- **rw**: monta el filesystem como lectura/escritura.
- **user**: permite que cualquier usuario pueda montar el filesystem.
- **nouser**: especifica que el filesystem sólo puede ser montado por el usuario root y no por un usuario común.
- **sync**: todas las escrituras al filesystem se hacen en el momento. Esto da mayor seguridad a los datos pero un menor rendimiento.

Las últimas dos columnas indican si se tiene que hacer backup del sistema (1 si, 0 no) y la última si debe ser checkeado (0 no, 1 sí con prioridad y 2 sí sin prioridad).

###### Actividad 1.11

En la actividad 1.9 ya se ha explicado qué son /etc/fstab y /etc/mtab y sus diferencias.

Ahora veamos que contiene el archivo /proc/filesystems:

```bash
nodev	sysfs
nodev	rootfs
nodev	bdev
nodev	proc
nodev	cgroup
nodev	cpuset
nodev	tmpfs
nodev	devtmpfs
nodev	binfmt_misc
nodev	securityfs
nodev	sockfs
nodev	pipefs
nodev	anon_inodefs
nodev	rpc_pipefs
nodev	configfs
nodev	devpts
	reiserfs
	ext3
	ext2
	ext4
	squashfs
nodev	ramfs
	vfat
	msdos
	iso9660
nodev	ecryptfs
nodev	nfs
nodev	nfs4
nodev	nfsd
nodev	cifs
	ntfs
nodev	autofs
nodev	fuse
	fuseblk
nodev	fusectl
	udf
	nilfs2
nodev	hostfs
	btrfs
	gfs2
	gfs2meta
nodev	mqueue
nodev	selinuxfs
```

Ahora /proc/mounts:

````bash
rootfs / rootfs rw 0 0
/dev/root / ext4 rw,noatime,user_xattr,acl,barrier=1,data=ordered 0 0
none /proc proc rw,nosuid,nodev,noexec,relatime 0 0
none /sys sysfs rw,nosuid,nodev,noexec,relatime 0 0
devpts /dev/pts devpts rw,relatime,gid=5,mode=620 0 0
/tmp /tmp tmpfs rw,relatime 0 0
none /proc/sys/fs/binfmt_misc binfmt_misc rw,relatime 0 0
````

La diferencia entre estos archivos es que /proc/filesystems indica los sistemas de archivos soportados por el kernel que estemos usando mientras que /proc/mounts es una representación en forma de archivo de los dispositivos disponibles por el kernel de Linux. Este archivo es bastante parecido a /etc/mtab, pero incluye otros sistemas de archivos que no tienen nada que ver con discos duros.



### Sesión 2

###### Actividad 2.1

Por limitaciones hardware (no tengo un pen a mano), sólo lo hago usando un archivo especial. Empezamos creando estos archivos especiales con las órdenes:

````bash
mknod /dev/loop0 b 7 0
mknod /dev/loop1 b 7 1
````

Ahora vamos a crear dos archivos, uno de 20MB y otro de 30MB de la siguiente forma:

````bash
dd if=/dev/zero of=/root/archivo_SA20 bs=2k count=10000
dd if=/dev/zero of=/root/archivo_SA30 bs=3k count=10000
````

Ahora ya solo queda utilizar la orden `losetup` para enlazar ambos archivos:

```bash
losetup /dev/loop0 /root/archivo_SA20
losetup /dev/loop1 /root/archivo_SA30
```

Utilizando la orden `fdisk -l /dev/loop0 /dev/loop1` podemos ver como ha quedado:

````bash
Disk /dev/loop0: 20 MB, 20480000 bytes
255 heads, 63 sectors/track, 2 cylinders, total 40000 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk identifier: 0x00000000

Disk /dev/loop0 doesn't contain a valid partition table

Disk /dev/loop1: 30 MB, 30720000 bytes
255 heads, 63 sectors/track, 3 cylinders, total 60000 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk identifier: 0x00000000

Disk /dev/loop1 doesn't contain a valid partition table
````

###### Actividad 2.2

Vamos a utilizar la orden `mkfs.extX` que es lo mismo que hacer `mke2fs -t extX`. Para el primero hacemos:

````bash
mkfs.ext3 -L LABEL_ext3 /dev/loop0
````

Y obtenemos:

````bash
mke2fs 1.41.12 (17-May-2010)
Filesystem label=LABEL_ext3
OS type: Linux
Block size=1024 (log=0)
Fragment size=1024 (log=0)
Stride=0 blocks, Stripe width=0 blocks
5016 inodes, 20000 blocks
1000 blocks (5.00%) reserved for the super user
First data block=1
Maximum filesystem blocks=20709376
3 block groups
8192 blocks per group, 8192 fragments per group
1672 inodes per group
Superblock backups stored on blocks: 
	8193

Writing inode tables: done                            
Creating journal (1024 blocks): done
Writing superblocks and filesystem accounting information: done

This filesystem will be automatically checked every 23 mounts or
180 days, whichever comes first.  Use tune2fs -c or -i to override.
````

Para el segundo alternativamente hacemos:

````bash
mkfs.ext3 -L LABEL_ext3 /dev/loop0
````

Y obtenemos:

````bash
mke2fs 1.41.12 (17-May-2010)
Filesystem label=LABEL_ext4
OS type: Linux
Block size=1024 (log=0)
Fragment size=1024 (log=0)
Stride=0 blocks, Stripe width=0 blocks
7520 inodes, 30000 blocks
1500 blocks (5.00%) reserved for the super user
First data block=1
Maximum filesystem blocks=30932992
4 block groups
8192 blocks per group, 8192 fragments per group
1880 inodes per group
Superblock backups stored on blocks: 
	8193, 24577

Writing inode tables: done                            
Creating journal (1024 blocks): done
Writing superblocks and filesystem accounting information: done

This filesystem will be automatically checked every 31 mounts or
180 days, whichever comes first.  Use tune2fs -c or -i to override.
````

###### Actividad 2.3

1. Para ellos vamos a engañar al sistema diciendo que ha sobrepasado el límite de tiempo utilizando:

   ````bash
   tune2fs -i 0
   ````

2. Supongamos que queremos reservar un número X de bloques para un usuario username:

   ````bash
   tune2fs -r X -u username
   ````

###### Actividad 2.4

Primero creamos los directorios donde quermos montarlos con la orden `mkdir` :

````bash
mkdir /mnt/SA_ext3
mkdir /mnt/SA_ext4
````

Ahora usamos la orden `mount`con las opciones correctas:

```bash
mount -r -L LABEl_ext3 /mnt/SA_ext3
mount -o sync -L LABEL_ext4 /mnt/SA_ext4
```

-  -r: Esta opción indica que es de sólo lectura.
- -L esta opción seguida de la label de un archivo indica cuál queremos montar.
- -o: Esta opción indica que se van a decir las opciones que necesitamos. En nuestro caso necesitamos sync.

###### Actividad 2.5

Ver la actividad 1.9 para recordar como era el archivo /etc/fstab. Una vez que ya sabemos la sintaxis del archivo es fácil añadir las siguientes líneas:

````bash
LABEL=LABEL_ext3 /mnt/SA_ext3 ext3 r 0 0
LABEL=LABEL_ext4 /mnt/SA_ext4 ext4 sync 0 0
````

###### Actividad 2.6

Hay cientos de sitios especializados en software para Linux, así que yo me voy a centrar en el mejor de todos por su cantidad de repositorios y actualizaciones, el AUR ([https://aur.archlinux.org](https://aur.archlinux.org)).

En este sitio podemos encontrar multitud de repositorios todos ellos con un enlace listo para clonarlos. También tiene apartado de foros, wiki,... Está principalmente pensado para usarse en Arch Linux.

###### Actividad 2.7

No se puede porque está pensado para hacerlo en clase.

###### Actividad 2.8

1. Usamos `rpm -q -a <nombre_pauete>`
2. Ahora simplemente usamos `rpm -q --configfiles <nombre_paquete>`
3. Para un paquete instalado utilizamos `rpm -q --filerequire <nombre_paquete>` y para uno que no esté instalado usamos `rpm -i -q --filerequire <nombre_paquete>`
4. Suponiendo que estuviéramos en el directorio `rpm -i --nodeps quota`
5. Usamos `rpm -e sysstat` (falta mostrar máxima información posible).

###### Actividad 2.9

1. Basta con especificar `usrquota`en las ociones del /etc/fstab. Entonces nos queda la línea:

   ```bash
   LABEL=LABEL_ext3 /mnt/SA_ext3 ext3 r,usrquota 0 0
   ```

2. Ahora usamos la orden que nos dice el enunciado:

   ```bash
   mount -o remount /mnt/SA_ext3 /mnt/SA_ext3
   ```

3. Usamos la orden del enunciado una vez más:

   ````bash
   quotacheck -nm /mnt/SA_ext3
   ````

4. Otra vez:

   ```bash
   quotaon -a
   ```

5. 

### Sesión 3

###### Actividad 3.1

Utilizamos `uptime`:

```bash
08:47:07 up 3:40,  1 user,  load average: 0.34, 0.21, 0.10
```

1. Nos fijamos en lo que viene a continuación de up, que sería 3:40 horas en mi caso.
2. Vemos como pone 1 user.
3. Ahora vemos que hay tres floats tras load average, de los cuáles el último (0.10) se refiere a los últimos 15 minutos.

###### Actividad 3.2

1. ```bash
   var=0
   basura=0
   
   for ((i=0 ; i<$1 ; i++)); do
           basura=$(( 3/2 ))
           var=$(( $var+1 ))
   done
   
   printf "El resultado es: $var\n"
   ```

2. Para ejecutar este script en segundo plano usamos: `./prueba_procesos <argumento> &`. Para que de tiempo a ver la prioridad mientra se están ejecutando se recomienda usar un valor elevado de argumento.

   Cuando usamos la orden anterior el sistema nos devolverá el PID del proceso. Ahora basta usar `ps -l <PID>` para ver su prioridad. Por ejemplo:

   ```bash
   F S   UID     PID    PPID  C PRI  NI ADDR SZ WCHAN  TTY        TIME CMD
   1 R  1000   42148    9032 58  80   0 - 56878 -      pts/1      0:05 bash
   ```

   Aquí podemos ver que su prioridad es 0, información que nos brinda la columna NI. Ahora para aumentarle o disminuirle la prioridad a un proceso en ejecución  a una cantidad X usamos la orden `renice X <PID>`. 

3. Para este apartado he ejecutado todos los programas anteriores con la orden `time ./prueba_procesos <argumento> &`, y esta orden nos indica lo que ha tardado.

###### Actividad 3.3

1. Basta con lanzar algún que otro proceso y usar `ps -p 0` para ver la prioridad del init, del que van a derivar los que hayas lanzados, cuya prioridad vemos con `ps -p <PID>`.

2. Esto significa que este proceso no tiene ninguna consola o terminal asociada.

###### Actividad 3.4

1. Usamos la orden `mpstat 1 1` y nos fijamos en la columna %irq.
2. Volvemos a usar `mpstat 1 1` pero esta vez nos fijamos en %soft.
3. Ahora usamos la orden `free` y en esta ya podemos ver fácilmente la fila swap.

###### Actividad 3.5

La orden free nos muestra una monitorización de la memoria del sistema mientras que la orden watch seguida de otro comando ejecuta este comando repetidas veces y nos va mostrando sus salidad y errores.

###### Actividad 3.6

Utilizamos la orden `vmstat 2 20 >> <Archivo>` y luego hacemos un `cat`sobre archivo y obtendremos algo parecido a esto:

```bash
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 0  0      0 630536 141168 2292936    0    0    30     8  317  510  5  2 92  0  0
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 0  0      0 630692 141192 2292960    0    0    30     8  317  510  5  2 92  0  0
 0  0      0 630136 141192 2292948    0    0     0     0  540  917  2  2 96  0  0
 0  0      0 628156 141200 2292948    0    0     0    20  704 1011  1  4 95  0  0
 0  0      0 629164 141200 2292936    0    0     0     0  420  717  1  2 97  0  0
 0  0      0 629156 141200 2292936    0    0     0     0  490  837  1  2 97  0  0
 0  0      0 629624 141208 2292936    0    0     0    14  425  731  1  2 97  0  0
 0  0      0 630256 141208 2292936    0    0     0     0  449  776  1  2 97  0  0
 2  0      0 630552 141208 2292936    0    0     0     0  310  540  1  1 98  0  0
 1  0      0 629964 141208 2292936    0    0     0     0  373  622  1  2 97  0  0
 0  0      0 629504 141208 2292936    0    0     0     0  363  612  1  2 97  0  0
 3  0      0 630476 141208 2292936    0    0     0     0  346  586  1  1 98  0  0
 0  0      0 629212 141208 2292936    0    0     0     0  393  644  1  1 98  0  0
 0  0      0 629712 141208 2292936    0    0     0     0  335  573  1  2 98  0  0
 0  0      0 630220 141208 2292936    0    0     0     0  380  648  1  1 98  0  0
 0  0      0 629672 141208 2292936    0    0     0    16  316  531  1  1 98  0  0
 1  0      0 629724 141208 2292936    0    0     0     0  404  676  1  2 97  0  0
 2  0      0 629464 141208 2292936    0    0     0     0  328  550  1  1 98  0  0
 0  0      0 630204 141208 2292936    0    0     0     0  375  649  1  2 98  0  0
 0  0      0 629260 141208 2292936    0    0     0     0  380  632  1  1 98  0  0
 0  0      0 630524 141208 2292936    0    0     0     0  355  596  1  2 98  0  0
```

###### Actividad 3.7

Para verlos usamos `ls -a`. Obtenemos en el UML:

```bash
.bash_history  .bash_logout  .bash_profile  .bashrc  .cshrc  .tcshrc
```

Ahora en mi usuario normal:

```bash
.bash_history  .bash_logout  .bash_profile  .bashrc  .lesshst
```

###### Actividad 3.8

Por ejemplo supongamos que queremos listar el directorio DIR:

1. Usamos `ls DIR -l --sort=time --time=access`
2. Ahora usamos `ls DIR -l --sort=time --time=ctime`

En lo anterior `--sort=time` como su nombre indica significa que lo estamos filtrando por tiempo, y `--time=WORD`indica por que tiempo queremos asignarlo, siendo este WORD.

###### Actividad 3.9

1. Para ello usamos `du -h --max-depth=1`. Con -h especificamos que el formato sea legible por humanos y con --max-depth=1 evitamos que se haga de forma recursiva por todo el directorio.

2. Para ver los inodos usados nos fijamos en la tercera columna (IUsed) al usar `df -i`. Ahora si queremos ver cuántos archivos se pueden crear tenemos que mirar la cuarta columna (IFree).

3. El tamaño de /etc es 20 MB y el de /var es 13 MB. Para verlo vasta con usar `du -sbh --max-depth=1 / | grep DIR` donde DIR es el directorio que queremos comprobar. Por otra parte tenemos que /bin tiene 5.2 MB, /usr tiene 276 MB y /lib 22 MB.

   Con esta información podemos apreciar que el fichero /usr contiene multitud más de información que el resto. Por ejemplo este fichero guarda las configuraciones de cada usuario.

4. Para ello basta con especificar la opción --block-size en `du`. Enotnces nos queda el comando `du --block-size=4k / --max-depth=1 | grep /etc`.

###### Actividad 3.10

Primero empezamos creando los archivos: `touch archivo.txt target_hardLink2.txt`.

Vamos a crear ahora los enlaces duros a ambos archivos. Para ello basta con usar la orden `ln` sin argumentos dos veces:

```bash
ln archivo.txt hardLink
ln target_hardLink2.txt hardLink2
```

Ahora vamos a crear el enlace simbólico sobre archivo.txt. Para ello añadimos la opción -s:

```bash
ln -s archivo.txt softLink
```

Para comprobar que lo hemos hecho bien ahora usamos `ls -lai` y veremos algo así:

```bash
14251 -rw-r--r--  2 root root    0 Oct 17 17:22 archivo.txt
14251 -rw-r--r--  2 root root    0 Oct 17 17:22 hardLink
14253 -rw-r--r--  2 root root    0 Oct 17 17:22 hardLink2
14263 lrwxrwxrwx  1 root root   11 Oct 17 17:40 softLink -> archivo.txt
14253 -rw-r--r--  2 root root    0 Oct 17 17:22 target_hardLink2.txt
```

El por qué archivo.txt tiene el contador es una respuesta obvia según la definición de contador de enlaces. El contador de enlaces indica cuántos archivos acceden al mismo inodo. Entonces como al inodo de archivo.txt (14251 en mi caso) lo apuntan tanto hardLink como el propio archivo.txt, pues su contador es 2.

###### Actividad 3.11

1. En este caso tan solo utilizamos la orden -L:

   ```bash
   ls -Lla
   ```

2. Ahora basta con usar la orden -d:

   ```bash
   ls -Lda
   ```

###### Actividad 3.12

Para crear un archivo de bloques haremos:

```bash
mknod archivoBloques b 0 1
```

Para crear el archivo de caracteres:

```bash
mknod archivoCaracteres c 0 1
```

Al usar `ls -li` podemos ver que nos queda:

```bash
14251 -rw-r--r-- 2 root root    0 Oct 17 17:22 archivo.txt
14265 brw-r--r-- 1 root root 0, 1 Oct 17 18:25 archivoBloques
14266 crw-r--r-- 1 root root 0, 1 Oct 17 18:25 archivoCaracteres
14251 -rw-r--r-- 2 root root    0 Oct 17 17:22 hardLink
14253 -rw-r--r-- 2 root root    0 Oct 17 17:22 hardLink2
14263 lrwxrwxrwx 1 root root   11 Oct 17 17:40 softLink -> archivo.txt
14253 -rw-r--r-- 2 root root    0 Oct 17 17:22 target_hardLink2.txt
```



## Módulo II

### Sesión 1

###### Actividad 1.2

```c
/*
Implementa un programa que realice la siguiente funcionalidad:
El programa acepta como argumento el nombre de un archivo 
(pathname), lo abre y lo lee en bloques de tamaño 80 Bytes, 
y crea un nuevo archivo de salida, salida.txt, en el que 
debe aparecer la siguiente información:
Bloque 1
	Aquí van los primeros 80 Bytes del archivo pasado como argumento.
Bloque 2
	Aquí van los siguientes 80 Bytes del archivo pasado como argumento.
...
Bloque n
	Aquí van los siguientes 80 Bytes del archivo pasado como argumento.
*/

#include<unistd.h>  /* POSIX Standard: 2.10 Symbolic Constants <unistd.h> */
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  /* Primitive system data types for abstraction	\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
		       */
#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>

int MAX_LECT = 80;
int MAX_BLOQUE = 15;

int main(int argc, char *argv[]){
	int fich_lec, fich_esc;
	char buff[MAX_LECT];
	int leidos;
	int cont=1;
	char bloque[MAX_BLOQUE];

	if (argc==2){
		if( (fich_lec=open(argv[1],O_RDONLY))<0 ){
			printf("\nError %d en open",errno);
			perror("\nError en open del argumento argv[1]");
			exit(EXIT_FAILURE);
		} else{
			printf("Utilizando el fichero %s como archivo de entrada\n", argv[1]);
		}	
	}
	else{
		printf( "Utilizando la entrada estándar como entrada:\n");
		fflush(stdout);
		fich_lec=STDIN_FILENO;
	}

	if( (fich_esc=open("salida.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0 ){
		printf("\nError %d en open",errno);
		perror("\nError en open de salida.txt");
		exit(EXIT_FAILURE);
	}

	while( (leidos=read(fich_lec, buff, MAX_LECT))>0 ){
		sprintf(bloque, "\nBloque %d\n",cont);

		if( write(fich_esc, bloque, strlen(bloque))<0 ){
			printf("\nError %d en primer write: bloque %d",errno,cont);
			perror("\nError en el primer write (línea de bloque n)");
			exit(EXIT_FAILURE);
		}

		if( write(fich_esc, buff, leidos)<0 ){
			printf("\nError %d en segundo write: bloque %d",errno,cont);
			perror("\nError en el segundo write (línea de escritura de bytes)");
			exit(EXIT_FAILURE);
		}

		cont++;
	}

	close( fich_lec );
	close( fich_esc );

	return EXIT_SUCCESS;
}
```

