#########################################################################
# File Name: cgi-bind.sh
# Author: yoyao
# mail: yoyao@126.com
# Created Time: Thu 05 Apr 2018 09:08:53 PM CST
#########################################################################
#!/bin/bash


function isIncluded()
{
	src=$1;
	subs=$2;
	if [[ $src == *$subs* ]]
	then
		return 0;
	fi
	return 1;
}


function isPass()
{
	string=$1;
	arr=("grep" "/bin/bash");
	for str in ${arr[@]}
	do
		echo "equal $string and $str";
	    isIncluded "$string" "$str";
		res=$?;
		if [[ $res -eq 0 ]]
		then
			return 1;
		fi
	done
	return 0;
}

search=$1
#地址
addr="127.0.0.1";
#端口
port=$2;
#执行程序
exe=$3;

pid=0;


count=0;

pids=$(ps aux | grep $search | grep -v "grep" | awk '{print $2;}');

for id in ${pids[@]}
do
echo "pid is "${id};
pid=$id;
count=$(expr $count+1);
done

if [ $count -ne 1 ]
then
echo "error;found more than one";
exit 0;
fi

echo "founded pid "$pid;

echo "execute kill -9 $pid";









