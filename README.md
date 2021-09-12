Per chi avesse avuto problemi durante la compilazione della toolchain di OS161 per svolgere i laboratori nativamente sulla propria distribuzione, questi sono i problemi che ho riscontrato e come ho risolto. Ho effettuato l'installazione su pop-os 20.10 (distro Ubuntu based), seguendo questa guida http://os161.eecs.harvard.edu/resources/setup.html.

## *SEGUIRE LA GUIDA LINKATA QUI SOPRA E SEGUIRE I CONSIGLI SOTTOSTANTI QUANDO SI GENERANO DEGLI ERRORI (TALE PARTE POTREBBE ESSERE OPZIONALE IN BASE ALLA VERSIONE DELLA VOSTRA DISTRIBUZIONE), TERMINATA LA GUIDA ANDARE AL PROSSIMO PARAGRAFO (NON OPZIONALE)*

**Librerie da installare**
Se non sbaglio ho dovuto installare **libncurses5-dev** e **libmpc-dev**

```bash
sudo apt install libncurses5-dev
sudo apt install libmpc-dev
```

**Compilazione di GDB** 
Per compilare GDB ho dovuto modificare **gdb-7.8+os161-2.1/sim/common/sim-arange.h** commentando l' **#include** a linea 76 (#include "sim-arange.c")
Inoltre ho dovuto settare come versione default di python python 2.7 sostituento python 3.8 .
Per farlo ho utilizzato il comando :

```bash
sudo update-alternatives --config python
```

Se il comando precedente non trova l'opzione python2.7 o da errore significa che sulla vostra distro non è stata impostata alcuna alternativa per python2.7.
Per prima cosa assicuratevi di avere python2.7 installato.

```bash
sudo apt install python2.7
```

Poi eseguite i seguenti comandi:

```bash
update-alternatives --install /usr/bin/python python /usr/bin/python2.7 1
update-alternatives --install /usr/bin/python python /usr/bin/python3.8 2
```

Se python3.8 non viene trovato sostituire python3.8 con la vostra versione più recente installata nel comando precedente

Ora potete settare la vostra versione python di default con

```bash
sudo update-alternatives --config python
```

Per verificare che tutto sia andato a buon fine verificate la versione python attuale con 

```bash
python --version
```

**Compilazione di sys/161 **
Per risolvere i problemi di compilazione ho dovuto dichiarare come **extern** la variabile **extra_selecttime** in **sys161-2.0.8/include/onsel.h**.

## *LA PARTE SEGUENTE VA ESEGUITA SOLO DOPO AVER COMPLETATO CON SUCCESSO LA GUIDA LINKATA ALL'INIZIO DI QUESTO FILE*

**Scaricare OS161**
Scaricare l'archivio **os161-base-2.0.3.tar.gz** da http://os161.eecs.harvard.edu/download/ e decomprimerlo in **$HOME/os161/** 

**Aggiungere tools al PATH** 
per poter usare comandi come **sys161** serve aggiungere la cartella **tools/bin** al **PATH** 

```bash
echo -e "PATH=\"$HOME/os161/tools/bin:"'$PATH'"\"" >>$HOME/.profile
```

**IMPORTANTE: EFFETTUARE IL LOGOUT E FARE DI NUOVO LOGIN PER AGGIORNARE IL PATH**

**Cartella root e build del kernel** 
Eseguire il seguente script per effettuare il primo build del kernel e configurare la cartella **/root** (consiglio di eseguirlo riga per riga in modo da notare eventuali errori).
**Attenzione la cartella root si troverà nella cartella $HOME/os161/**

```bash
#!/bin/bash
cd $HOME/os161/os161-base-2.0.3/
./configure --ostree=$HOME/os161/root
bmake
bmake install
cd kern
cd conf
./config DUMBVM
cd ../compile/DUMBVM/
bmake depend
bmake
bmake install
cd $HOME/os161/root
if [ -f "LHD0.img" ]; then
  rm LHD0.img
fi
if [ -f "LHD1.img" ]; then
  rm LHD1.img
fi
disk161 create LHD0.img 5M
disk161 create LHD1.img 5M
cp $HOME/os161/tools/share/examples/sys161/sys161.conf.sample $HOME/os161/root/sys161.conf
```

**.gdbinit**
Creare un file **.gdbinit** in **$HOME** e scrivere al suo interno :

```bash
set auto-load safe-path /
```

Creare un file **.gdbinit** in **$HOME/os161/root** e scrivere al suo interno :

```
def dbos161
	dir ../../os161/os161-base-2.0.3/kern/compile/DUMBVM
	target remote unix:.sockets/gdb
end
dbos161
```

**EXTRA-VSCODE setup**
Per settare vscode seguite questa guida https://github.com/cheina97/os161vscode/tree/generic-(not-only-for-VM) e ricordatevi di lasciare una stella \**wink wink*\* 
