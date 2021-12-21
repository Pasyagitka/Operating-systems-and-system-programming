if [ -z "$1" ];then 
 echo parametrs not found
 exit 1
fi

ps -q $1 >/dev/null 2>&1

if [ $? -ne 0 ];then
 echo pid=$1 process not found
 exit 1
fi

echo "Name: `ps -q $1 -o comm | tail -n 1 | xargs`"
echo "PID:  `ps -q $1 -o pid  | tail -n 1 | xargs`"
echo "PPID: `ps -q $1 -o ppid | tail -n 1 | xargs`"

if [[ "$2" == "fd" ]];then
 for i in `ls /proc/$1/fd`; do
  echo fd = $i
 done
fi

