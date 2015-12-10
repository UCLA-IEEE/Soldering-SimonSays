#!/bin/bash

program()
{
    echo -e "n\nn\nn\n" | (sudo avrdude -p t84 -c jtag2isp -F -e)
    sleep 2
    sudo avrdude -p t84 -c jtag2isp -F -D -U main.hex
}

debug()
{
    echo "NODEBUG"
}

P_FLAG=0
D_FLAG=0

for i in $@
do
    if [[ $i == -p ]]
    then
        P_FLAG=1
    fi

    if [[ $i == -d ]]
    then
        D_FLAG=1
    fi
done

if [[ $P_FLAG == 1 ]]
then
    program
fi

if [[ $D_FLAG == 1 ]]
then
    debug
fi
