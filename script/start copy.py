import os
import subprocess
import time

filepath=os.path.realpath(__file__)
script_dir = os.path.dirname(os.path.normpath(filepath))
home_dir = os.path.dirname(os.path.normpath(script_dir))
conf_dir = home_dir+"/conf"
CONF = conf_dir+"/sysSetting.xml"

f = open(CONF)
start = False
concactstr = ""
for line in f:
    if line.find("setting") == -1:
        line = line[:-1]
    concactstr += line
res=concactstr.split("<attribute>")

slavelist=[]
fstype=""
for attr in res:
    if attr.find("agents.addr") != -1:
        valuestart=attr.find("<value>")
        valueend=attr.find("</attribute>")
        attrtmp=attr[valuestart:valueend]
        slavestmp=attrtmp.split("<value>")
        for slaveentry in slavestmp:
            if slaveentry.find("</value>") != -1:
                entrysplit=slaveentry.split("<")
                slave=entrysplit[0]
                slavelist.append(slave)
    if attr.find("fullnode.addr") != -1:
        valuestart=attr.find("<value>")
        valueend=attr.find("</attribute>")
        attrtmp=attr[valuestart:valueend]
        slavestmp=attrtmp.split("<value>")
        for slaveentry in slavestmp:
            if slaveentry.find("</value>") != -1:
                entrysplit=slaveentry.split("<")
                slave=entrysplit[0]
                slavelist.append(slave)

# start
print("start coordinator")
os.system("redis-cli flushall")
os.system("killall DistCoordinator")
os.system("sudo service redis_6379 restart")
# command="cd "+{home_dir}+"; ./DistCoordinator &> "+{home_dir}+"/coor_output &"
command = f"cd {home_dir}; ./DistCoordinator &> {home_dir}/coor_output &"

subprocess.Popen(['/bin/bash', '-c', command])

for slave in slavelist:
    # 本地杀死进程（单节点无需远程）
    os.system("killall DistAgent")
    os.system("killall DistClient")
    # 本地重启Redis（单节点共享Redis）
    os.system("sudo service redis_6379 restart")
    os.system("redis-cli flushall")
    # 本地启动Agent（无需复制文件，直接运行）
    command = f"cd {home_dir}; ./DistAgent &> {home_dir}/agent_output &"
    os.system(command)
