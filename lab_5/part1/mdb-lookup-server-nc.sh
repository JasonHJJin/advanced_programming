#!/bin/sh
mkfifo mypipe-$$
cat mypipe-$$ | nc -l $1 | /home/jae/cs3157-pub/bin/mdb-lookup-cs3157 > mypipe-$$
rm -f mypipe-$$
on_ctrl_c() {
    echo "Ignoring Ctrl-C"
}
on_ctrl_c INT

