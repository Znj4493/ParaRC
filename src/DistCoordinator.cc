#include "common/CmdDistributor.hh"
#include "common/Config.hh"
#include "common/Coordinator.hh"
#include "common/StripeStore.hh"

#include "inc/include.hh"

using namespace std;

int main(int argc, char** argv) {
  
  string configpath = "conf/sysSetting.xml";
  Config* conf = new Config(configpath);
  // create stripestore
  // TODO: need to add recover from backup
  StripeStore* ss = new StripeStore(conf); 

  // command distributor
  CmdDistributor* cmdDistributor = new CmdDistributor(conf);

  // coordinator
  // 在内存中分配一个指针数组，用于存储多个Coordinator对象的指针
  // conf->_coorThreadNum：数组元素个数（Coordinator线程数）；sizeof(Coordinator*)：每个元素的大小（指针的大小）
  Coordinator** coors = (Coordinator**)calloc(conf->_coorThreadNum, sizeof(Coordinator*));
  // 创建线程池，每个线程运行一个Coordinator对象的doProcess方法
  thread thrds[conf->_coorThreadNum];
  for (int i=0; i<conf->_coorThreadNum; i++) {
    coors[i] = new Coordinator(conf, ss);
    thrds[i] = thread([=]{coors[i]->doProcess();});
  }
  cout << "OECCoordinator started ......" << endl;
  
  for (int i=0; i<conf->_coorThreadNum; i++) {
    thrds[i].join();
  }
  /**
   * Shoule never reach here
   */
  for (int i=0; i<conf->_coorThreadNum; i++) {
    delete coors[i];
  }
  free(coors);
  delete conf;
  delete cmdDistributor;

  return 0;
}
