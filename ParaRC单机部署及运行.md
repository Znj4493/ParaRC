# ParaRC单机部署及运行

## 一、安装依赖库

* nasm
  ```bash
  $> sudo apt install autoconf automake libtool -y
  ```
* hiredis
  ```bash
  $> sudo apt install libhiredis-dev -y
  ```

* gf-complete
  ```bash
  $> sudo apt install libgf-complete-dev -y
  ```

* isa-l library

  ```bash
  $> git clone https://github.com/01org/isa-l.git
  $> cd isa-l/
  $> sudo apt install autoconf automake libtool -y
  $> ./autogen.sh
  $> ./configure
  $> make
  $> sudo make install
  ```

* cmake

  ```bash
  $> sudo apt-get install cmake
  ```

## 二、编译ParaRC

```bash
$> cd /home/pararc/ParaRC
$> ./compile.sh
```

## 三、准备配置文件

* ```/home/pararc/ParaRC/conf/sysSetting.xml```

  ```xml
  <setting>
    <attribute><name>prsgenerator.addr</name><value>127.0.0.1</value></attribute>  <!-- 本地IP -->
    <attribute><name>controller.addr</name><value>127.0.0.1</value></attribute>    <!-- 本地IP -->
    <attribute><name>agents.addr</name><value>127.0.0.1</value></attribute>        <!-- 本地IP -->
    <attribute><name>fullnode.addr</name><value>127.0.0.1</value></attribute>      <!-- 本地IP -->
    <attribute><name>local.addr</name><value>127.0.0.1</value></attribute>         <!-- 本地IP -->
    <attribute><name>block.directory</name><value>/home/book/ParaRC/blkDir</value></attribute>  <!-- 存数据块的文件夹 -->
    <attribute><name>stripestore.directory</name><value>/home/book/ParaRC/stripeStore</value></attribute>  <!-- 存元数据的文件夹 -->
    <attribute><name>tradeoffpoint.directory</name><value>/home/book/ParaRC/tradeoffPoint</value></attribute>  <!-- 存MLP的文件夹 -->
    <attribute><name>pararc.mode</name><value>standalone</value></attribute>  <!-- 单机模式 -->
    <attribute><name>controller.thread.num</name><value>10</value></attribute>  <!-- Coordinator 协调线程数 -->
    <attribute><name>agent.thread.num</name><value>16</value></attribute>      <!-- Agent 工作线程数（核心计算） -->
    <attribute><name>cmddist.thread.num</name><value>6</value></attribute>     <!-- 命令分发线程数 -->
  </setting>
  ```

* 手动创建```/home/pararc/ParaRC/blkDir```，用于存储条带
  ## 四、离线生成MLP

  1. 为每个块都生成一个MLP

     ```bash
     ./GenMLP Clay 6 4 8 0
     ./GenMLP Clay 6 4 8 1
     ./GenMLP Clay 6 4 8 2
     ./GenMLP Clay 6 4 8 3
     ./GenMLP Clay 6 4 8 4
     ./GenMLP Clay 6 4 8 5
     ```

  2. 收集每次输出的字符串，手动生成xml文件```/home/pararc/ParaRC/tradeoffPoint/Clay_6_4_8.xml```

     ```xml
     <tradeoff>
     <attribute><name>code</name><value>Clay</value></attribute>
     <attribute><name>ecn</name><value>6</value></attribute>
     <attribute><name>eck</name><value>4</value></attribute>
     <attribute><name>ecw</name><value>8</value></attribute>
     <attribute><name>digits</name><value>1</value></attribute>
     <attribute><name>point</name>
     <value>0:00201121252125212222222125415511</value>
     <value>1:52005124522452242220202344244244</value>
     <value>2:22332245030505413345334533413315</value>
     <value>3:22131230001010101410141014114410</value>
     <value>4:22451145050000112212232325152515</value>
     <value>5:00332245000303210322332303240324</value>
     </attribute>
     </tradeoff>
     ```

  ## 五、离线生成条带

  ```bash
  ./GenData Clay 6 4 8 0 1048576 1024
  ```

  ```bash
  $> ls blkDir
  
  stripe-0-0  stripe-0-1  stripe-0-2  stripe-0-3  stripe-0-4  stripe-0-5 
  ```

  ## 六、生成条带元数据文件

  ```/home/pararc/ParaRC/stripeStore/Clay-0.xml```

  ```xml
  <stripe>
    <attribute><name>code</name><value>Clay</value></attribute>
    <attribute><name>ecn</name><value>6</value></attribute>  <!-- 总块数n=6 -->
    <attribute><name>eck</name><value>4</value></attribute>  <!-- 数据块数k=4 -->
    <attribute><name>ecw</name><value>8</value></attribute>  <!-- 子分组级别w=8 -->
    <attribute><name>stripename</name><value>Clay-0</value></attribute>  <!-- 条带名称，对应索引0 -->
    <attribute><name>blocklist</name>
      <!-- 每个块对应agent的IP（单节点均为127.0.0.1） -->
      <value>stripe-0-0:127.0.0.1</value>
      <value>stripe-0-1:127.0.0.1</value>
      <value>stripe-0-2:127.0.0.1</value>
      <value>stripe-0-3:127.0.0.1</value>
      <value>stripe-0-4:127.0.0.1</value>
      <value>stripe-0-5:127.0.0.1</value>
    </attribute>
    <attribute><name>blockbytes</name><value>1048576</value></attribute>  <!-- 块大小1MB（1048576字节） -->
    <attribute><name>subpktbytes</name><value>1024</value></attribute>  <!-- 子包大小1KB（1024字节） -->
  </stripe>
  ```

  ## 七、启动ParaRC

  ```bash
  $> python script/start.py
  ```

  目前```DistCoordinator```进程需要独立启动

  ```bash
  ./DistCoordinator
  ```

  ## 八、并行修复测试

  ```bash
  $> ./DistClient degradeRead stripe-0-0 dist
  ```

  

  

  