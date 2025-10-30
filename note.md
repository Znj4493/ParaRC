* 10.30
    1. Coordinator其实就是Controller，它运行在某个节点上，共有_coorThreadNum个线程，即Controller节点上有_coorThreadNum个Coordinator来执行Controller的功能（比如agent1完成第一个任务，agent2完成第二个任务）
    2. CmdDistributor需要与Controller节点连接，被动监听Controller给的任务，并告诉对应的agent需要完成什么任务（比如告诉agent1你需要完成第一个任务）
    3. DistCoordinator，它主要就是用来初始化刚刚说的那些组件的，比如初始化一个cmdDistributor、初始化coorThreadNum个coordinator并让他们开始干活（每个coor线程都要执行doProcess函数）