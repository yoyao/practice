#########################################################################
# File Name: exec.sh
# Author: yoyao
# mail: yoyao@126.com
# Created Time: 2018年03月24日 星期六 22时47分08秒
#########################################################################
#!/bin/bash

make -f server_make clean
make -f server_make
./rbmq_server.out







