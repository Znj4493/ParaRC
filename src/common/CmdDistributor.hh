#ifndef _CMDDISTRIBUTOR_HH_
#define _CMDDISTRIBUTOR_HH_

#include "Config.hh"

#include "../inc/include.hh"
#include "../util/RedisUtil.hh"


using namespace std;

// 负责将Coordinator的命令分发到各个Agent上
class CmdDistributor {
  private:
    Config* _conf;
    int _dNum; // 用多少个线程来分发命令
    vector<thread> _dThreads; // 实际要运行的线程
    unordered_map<unsigned int, redisContext*> _agentCtx; // Agent的ip -> redisContext
                                                          // 实际并没有使用该变量

  public:
    CmdDistributor(Config* conf); 
    ~CmdDistributor();
    void distribute(); // 每个线程都独立执行distribute()方法
};

#endif

