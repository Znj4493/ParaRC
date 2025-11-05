* 10.30
    1. Coordinator其实就是Controller，它运行在某个节点上，共有_coorThreadNum个线程，即Controller节点上有_coorThreadNum个Coordinator来执行Controller的功能（比如agent1完成第一个任务，agent2完成第二个任务）
    2. CmdDistributor需要与Controller节点连接，被动监听Controller给的任务，并告诉对应的agent需要完成什么任务（比如告诉agent1你需要完成第一个任务）
    3. DistCoordinator，它主要就是用来初始化刚刚说的那些组件的，比如初始化一个cmdDistributor、初始化coorThreadNum个coordinator并让他们开始干活（每个coor线程都要执行doProcess函数）
    
* 11.4
    1. CmdDistributor和Coordinator初始化方式的对比
        * CmdDistributor有一个对象，包含多个线程；Coordinator有N个对象
        * CmdDistributor各线程共享成员变量；Coordinator每个对象有自己的成员变量（保证了各个修复任务之间不会相互干扰）
        
    2. “悬空指针”与“野指针”
        * 悬空指针：指针曾经有效，但只向的内存后来被释放了
        
          ```c++
          int* p = new int(10);
          delete p;        // 内存释放了
          *p = 20;         // p 现在是悬空指针，访问会出错
          ```
        
        * 野指针：指针从未初始化，指向随机的内存
        
          ```c++
          int* p;          // 没有初始化，p 是野指针
          *p = 20;    
          ```
        
        * 两者都是指向不该访问的内存，可能导致**段错误**