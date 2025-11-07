#ifndef _ECDAG_HH_
#define _ECDAG_HH_

#include "../inc/include.hh"
#include "../protocol/AGCommand.hh"
//
//#include "Cluster.hh"
#include "ECNode.hh"
#include "ECUnit.hh"
#include "ECCluster.hh"
#include "ECTask.hh"
#include "../util/BlockingQueue.hh"
#include "../util/LoadVector.hh"

using namespace std;

#define ECDAG_DEBUG_ENABLE true
//#define BINDSTART 200
//#define OPTSTART 300

#define REQUESTOR 32767
#define SGSTART 0
#define USTART 0
#define CSTART 0

class ECDAG {
  private:
    unordered_map<int, ECNode*> _ecNodeMap; //* 节点映射：节点索引 -> 节点
    vector<int> _ecHeaders; //* 头节点：修复好的块
    vector<int> _ecLeaves; //* 叶子节点：原始块

    // // for SimpleGraph
    // int _sgId = SGSTART;
    // unordered_map<int, SimpleGraph*> _sgMap;
    // vector<int> _sgList;
    // unordered_map<int, vector<int>> _child2sgs;

    // for coloring
    unordered_map<int, unsigned int> _idx2ip; //* 节点索引 -> 节点IP

    // for ECUnits
    int _unitId = USTART;
    unordered_map<int, ECUnit*> _ecUnitMap; //* 单元映射：单元索引 -> 单元
    vector<int> _ecUnitList;

    // for ECClusters
    int _clusterId = CSTART;
    unordered_map<int, ECCluster*> _ecClusterMap;
    vector<int> _ecClusterList;
    
  public:
    ECDAG(); 
    ~ECDAG();

    //* 将cidx中的块通过系数表coefs进行编码，得到pidx块
    void Join(int pidx, vector<int> cidx, vector<int> coefs);
    //* 标记输出节点，调用Join添加一个REQUESTOR节点
    void Concact(vector<int> cidx);

    //void genSimpleGraph();
    //void initializeLeaveIp(unordered_map<int, unsigned int> availIps);
    //void initializeRequestorIp(unsigned int ip);
    //void initializeIntermediateIp(unsigned int ip); 
    //void fillLoadVector(LoadVector* loadvector);
    //void coloring(LoadVector* loadvector);
    //void genECTasks(vector<ECTask*>& tasklist,
    //                int ecn, int eck, int ecw,
    //                string stripename, vector<string> blocklist); 
    //void simulateLoc();

    void genECUnits();
    void clearECCluster();
    void genECCluster(unordered_map<int, int> coloring, int clustersize);
    void genStat(unordered_map<int, int> coloring, unordered_map<int, int>& inmap, unordered_map<int, int>& outmap);
    void genECTasksByECClusters(vector<ECTask*>& tasklist,
            int ecn, int eck, int ecw, int blkbytes, int pktbytes,
            string stripename, vector<string> blocklist,
            unordered_map<int, unsigned int> coloring_res);
    void genECTasksTopo(vector<ECTask*>& tasklist,
            int ecn, int eck, int ecw, int blkbytes, int pktbytes,
            string stripename, vector<string> blocklist, vector<unsigned int> loclist,
            unordered_map<int, unsigned int> coloring_res);
    void genComputeTaskByECUnits(vector<ComputeTask*>& tasklist);
    void genConvECTasks(vector<ECTask*>& tasklist,
            int ecn, int eck, int ecw, int blkbytes, int pktbytes,
            string stripename, vector<string> blocklist, 
            vector<unsigned int> loclist, int repairIdx);
    void genConvECTasks2(vector<ECTask*>& tasklist,
            int ecn, int eck, int ecw, int blkbytes, int pktbytes,
            string stripename, vector<string> blocklist, 
            vector<unsigned int> loclist, int repairIdx);
    void genConvECTasksWithOffset(vector<ECTask*>& tasklist,
            int ecn, int eck, int ecw, int blkbytes, int pktbytes,
            string stripename, vector<string> blocklist, 
            vector<unsigned int> loclist, int repairIdx, int offset);
    void genDistECTasks(vector<ECTask*>& tasklist,
            int ecn, int eck, int ecw, int blkbytes, int pktbytes,
            string stripename, vector<string> blocklist,
            unordered_map<int, unsigned int> coloring_res);

    unordered_map<int, ECNode*> getECNodeMap();
    vector<int> getECHeaders();
    vector<int> getECLeaves();
    unordered_map<int, ECUnit*> getUnitMap();
    vector<int> getUnitList();

    // for debug
    void dump();
};
#endif
