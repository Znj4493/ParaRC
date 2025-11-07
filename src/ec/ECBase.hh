#ifndef _ECBASE_HH_
#define _ECBASE_HH_

#include "../inc/include.hh"

#include "ECDAG.hh"

using namespace std;

class ECBase {
  public:
    int _n, _k, _w;
    //bool _locality;
    int _opt;

    //* 构造函数无需虚化，因为构造对象时已经知道对象类型，无需运行时后决定
    //* 但析构函数需要虚化！因为子类可能有自己的析构函数，需要调用子类的析构函数
    ECBase();
    ECBase(int n, int k, int w, vector<string> param);
    
    //* 虚函数：允许子类重新定义父类中的该函数
    //* 纯虚函数：该函数没有实现，必须在子类中实现；包含纯虚函数的类不能直接创建对象
    virtual ECDAG* Encode() = 0;
    virtual ECDAG* Decode(vector<int> from, vector<int> to) = 0;
 //   virtual void Place(vector<vector<int>>& group) = 0;
};

#endif
