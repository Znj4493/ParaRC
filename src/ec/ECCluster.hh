#ifndef _ECCLUSTER_HH_
#define _ECCLUSTER_HH_

#include "../inc/include.hh"
#include "ECUnit.hh"

using namespace std;

//* 描述了一个节点上需要执行的所有计算单元
class ECCluster {
  private: 
    int _clusterId;
    vector<int> _unitList;
    int _color; //* 颜色（所属节点）

    vector<int> _childList; //* 依赖于哪些集群（输入）
    vector<int> _parentList; //* 哪些集群依赖于该集群（输入）
    unordered_map<int, vector<int>> _coefMap;

  public:
    ECCluster(int clusterid, vector<int> unitlist);
    ~ECCluster();

    int getClusterId();
    vector<int> getUnitList();
    void setChildList(vector<int> childlist);
    void setParentList(vector<int> parentlist);
    void setCoefMap(unordered_map<int, vector<int>> coefmap);
    bool isConcact(int requestor);
    vector<int> getChildList();
    vector<int> getParentList();
    unordered_map<int, vector<int>> getCoefMap();

    string dump();
};

#endif
