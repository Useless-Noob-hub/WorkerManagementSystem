#include <iostream>
using namespace std;
#include "WorkerManager.h"
#include "Worker.h"
#include "Employee.h"
#include "Manager.h"
#include "Boss.h"


void test01()
{
    WorkerManager wm;

    int choice =0;  //用来存储用户的选项


    bool isExit = false;
    while(!isExit)
    {
        wm.ShowMenu();
        cout << "请输入您的选择：" << endl;
        cin >> choice;//获取用户的选项


        switch (choice)
        {
        case 0:
            wm.ExitSystem();
            break;
        case 1:
            wm.AddEmp();
            break;
        case 2:
            wm.ShowEmp();
            break;
        case 3:
           { 
            wm.DelEmp();
            break;
            }
        case 4:
            wm.ModEmp();
            break;
        case 5:
            wm.FindEmp();
            break;
        case 6:
            wm.SortEmp();
            break;
        case 7:
            wm.CleanFile();
            break;
        default:
            system("cls");  //清屏
            break;
        }
    }
}



int main(){
    test01();
    system("pause");
    return 0;
}