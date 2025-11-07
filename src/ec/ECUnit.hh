#ifndef _ECUNIT_HH_
#define _ECUNIT_HH_

#include "../inc/include.hh"

using namespace std;

//* 单元（一个线性组合）：一个单元包含一个父节点和多个子节点，以及一个系数表。表示如何通过子节点列表来生成对应的父节点
class ECUnit {
  private:
    int _unitId;
    vector<int> _childs;
    int _parent;
    vector<int> _coefs;

  public:
    ECUnit(int unitid, vector<int> childs, int parent, vector<int> coefs);
    int getUnitId();
    vector<int> getChilds();
    int getParent();
    vector<int> getCoefs();

    string dump();
    string getChildStr();
    
};

#endif
