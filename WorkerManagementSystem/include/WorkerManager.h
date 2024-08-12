#pragma once //防止头文件重复包含
#include "iostream"//包含输入输出流头文件
using namespace std;//使用标准命名空间
#include "Worker.h"
#include "Manager.h"
#include "Employee.h"
#include "Boss.h"
#include <fstream>
#define FILENAME "./bin/empFile.txt"



class WorkerManager
{
public:
    WorkerManager();        //构造函数，只做声明不做实现
    
    void ShowMenu();        //显示菜单

    void ExitSystem();

    // 记录职工人数
    int m_EmpNum;

    //职工数组指针
    Worker **m_EmpArray;

    //添加职工
    void AddEmp();

    //保存文件
    void Save();

    // 判断文件是否为空
    bool m_FileIsEmpty;

    //统计文件中人数
    int getEmpNum();

    //初始化员工
    void InitEmp();

    //显示职工
    void ShowEmp();

    //删除职工
    void DelEmp();

    // 查找职工
    int IsExistEmp(int id);

    //修改职工
    void ModEmp();

    //查找职工
    void FindEmp();

    //按照编号排序
    void SortEmp();

    //交换Worker顺序
    void Swap(Worker *&p1, Worker *&p2);

    //清空文件
    void CleanFile();

    ~WorkerManager();       //析构函数
};