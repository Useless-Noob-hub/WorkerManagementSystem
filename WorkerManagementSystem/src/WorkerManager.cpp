#include "WorkerManager.h"
WorkerManager::WorkerManager()
{
    //1、文件不存在
    ifstream ifs;
    ifs.open(FILENAME,ios::in);//读文件

    if(!ifs.is_open())
    {
        // cout<<"文件不存在"<<endl;
        // 初始化属性
        // 初始化记录人数
        this->m_EmpNum = 0;
        // 初始化数组
        this->m_EmpArray = NULL;
        //初始化文件是否为空
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    //2、文件存在 数据为空
    char ch;
    ifs>>ch;
    if(ifs.eof())
    {
        //文件为空
        // cout<<"文件为空"<<endl;
        // 初始化记录人数
        this->m_EmpNum = 0;
        // 初始化数组
        this->m_EmpArray = NULL;
        //初始化文件是否为空
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    // 3、文件存在 数据不为空
    int num = this->getEmpNum();
    // cout<<"当前职工人数为："<<num<<"人"<<endl;
    this->m_FileIsEmpty = false;
    this->m_EmpNum = num;

    //开辟空间
    this->m_EmpArray=new Worker*[num];
    // 将文件中的数据，存到数组中
    this->InitEmp();

    // // 测试代码
    // for(int i=0;i<this->m_EmpNum;i++)
    // {
    //     cout<<"职工编号："<<this->m_EmpArray[i]->m_Id
    //     <<"姓名："<<this->m_EmpArray[i]->m_Name
    //     <<"部门："<<this->m_EmpArray[i]->GetDeptName()<<endl;
    // }

}
void WorkerManager::ShowMenu()
{
    cout << "***************************************" << endl;
    cout << "********* 欢迎使用职工管理系统! *********" << endl;
    cout << "************ 0.退出管理程序 ************" << endl;
    cout << "************ 1.增加职工信息 ************" << endl;
    cout << "************ 2.显示职工信息 ************" << endl;
    cout << "************ 3.删除离职职工 ************" << endl;
    cout << "************ 4.修改职工信息 ************" << endl;
    cout << "************ 5.查找职工信息 ************" << endl;
    cout << "************ 6.按照编号排序 ************" << endl;
    cout << "************ 7.清空所有文档 ************" << endl;
    cout << "***************************************" << endl;
}
void WorkerManager::ExitSystem()
{
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);    //退出程序
}

// 添加职工
void WorkerManager::AddEmp()
{
    cout << "请输入添加职工数量：" << endl;
    int addNum = 0; //添加的职工数量
    cin >> addNum;
    if(addNum>0)
    {
        //添加
        // 计算添加新空间大小
        int newSize = this->m_EmpNum + addNum;  //新空间大小=原来的大小+添加的个数

        // 开辟新空间
        Worker **newSpace = new Worker*[newSize];

        // 将原来空间数据拷贝到新空间
        if(this->m_EmpNum>0)
        {

            for(int i=0;i<this->m_EmpNum;i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            } 
        }
        // 批量添加新数据 
        for(int i=0;i<addNum;i++)
        {
            int id; //职工编号
            string name;//职工姓名
            int dSelect;//部门选择
            cout << "请输入第" << i+1 << "个新职工编号：" << endl;
            cin >> id;
            while(this->IsExistEmp(id)>0)
            {
                cout << "编号已存在，请重新输入：" << endl;
                cin >> id;
            }
            cout << "请输入第" << i+1 << "个新职工姓名：" << endl;
            cin >> name;
            cout << "请输入第" << i+1 << "个新职工部门号：" << endl;
            cout << "1.普通职工" << endl;
            cout << "2.经理" << endl;
            cout << "3.老板" << endl;
            cin >> dSelect;
            Worker *worker = NULL;
            switch(dSelect)
            {
            case 1:
                worker = new Employee(id,name,1);
                break;
            case 2:
                worker = new Manager(id,name,2);
                break;
            case 3:
                worker = new Boss(id,name,3);
                break;
            }
            //将创建职工，保存到数组中
            newSpace[this->m_EmpNum+i] = worker;
        }
        
        //释放原有空间
        delete []this->m_EmpArray;
        
        //  更改新空间指向
        this->m_EmpArray = newSpace;

        // 更新人数
        this->m_EmpNum = newSize;

        //成功添加后 保存到文件中 
        this->Save();

        // 更新文件是否为空的标记
        this->m_FileIsEmpty = false;

        //提示添加成功
        cout << "添加成功" << addNum << "个职工" << endl;
    }
    else
    {
        cout << "输入有误，请重新输入" << endl;
    }

    //按任意键后 清屏回到上级目录
    system("pause");
    system("cls");
}

// 保存文件
void WorkerManager::Save()
{
    ofstream ofs;
    ofs.open(FILENAME,ios::out);//out模式，输出方式代开文件——写文件

    //将每个人数据写入到文件中
    for(int i = 0 ;i < this->m_EmpNum;i++)
    {
        ofs<< this->m_EmpArray[i]->m_Id<<"\t"
        << this->m_EmpArray[i]->m_Name<<"\t"
        <<this->m_EmpArray[i]->m_DeptId<<endl;
    }
        //关闭文件
        ofs.close();    //卸载循环体外部
}
int WorkerManager::getEmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME,ios::in); //打开文件 读
    int id ;
    string name;
    int dId;

    int num=0;

    while(ifs >>id && ifs >>name && ifs>>dId)
    {
         //统计人数变量
         num++;
    }
    return num;
}

void WorkerManager::InitEmp()
{
    ifstream ifs;
    ifs.open(FILENAME,ios::in);
    int id;
    string name;
    int dId;

    int index=0;
    while(ifs>>id && ifs>>name && ifs>>dId)
    {
        Worker *worker = NULL;
        switch(dId)
        {
        case 1:
            worker = new Employee(id,name,dId);
            break;
        case 2:
            worker = new Manager(id,name,dId);
            break;
        case 3:
            worker = new Boss(id,name,dId);
            break;
        }
        this->m_EmpArray[index++] = worker;
    }

    // 关闭文件
    ifs.close();

}

void WorkerManager::ShowEmp()
{
    //判断文件是否为空
    if(this->m_FileIsEmpty)
    {
        cout << "文件为空" << endl;
    }
    else
    {
        for(int i=0;i<this->m_EmpNum;i++)
        {
            //利用多态调用程序接口
            this->m_EmpArray[i]->ShowInfo();
        }
    }
    //按任意键后 清屏回到上级目录
    system("pause");
    system("cls");
}

void WorkerManager::DelEmp()
{
    //判断文件是否存在
    if(this->m_FileIsEmpty)
    {
        cout<<"文件为空"<<endl;
    }
    else
    {
        cout << "请输入要删除的职工编号：" << endl;
        int id = 0;
        cin >> id;
        //取得删除元素下标
        int index=this->IsExistEmp(id);
        if(index!=-1)//说明职工存在
        {
            for(int i = index;i<this->m_EmpNum-1;i++)//i指向删除位置，需要后面元素前移
            {
                this->m_EmpArray[i]=this->m_EmpArray[i+1];//前移复制
            }
            this->m_EmpNum--;//元素个数-1

            //更新文件
            this->Save();

            cout<<"删除成功"<<endl;
        }else{
            cout<<"删除失败，未找到该职位 "<<endl;
        }
    }

    //按任意键后 清屏回到上级目录
    system("pause");
    system("cls");

}

int WorkerManager::IsExistEmp(int id)
{   
    for(int i = 0;i<this->m_EmpNum;i++)
    {
        if(this->m_EmpArray[i]->m_Id == id)
        {
            //找到职工
            return i;
        }
    }
    return -1;
}

void WorkerManager::ModEmp()
{
    //判断文件是否存在
        if(this->m_FileIsEmpty)
    {
        cout<<"文件为空"<<endl;
    }else
    {
        cout << "请输入要修改的职工编号：" << endl;
        int id = 0;
        cin >> id;
        
        int ret = this->IsExistEmp(id);
        if(ret!=-1)//说明职工存在
        {
            Worker *temp = this->m_EmpArray[ret];
            //查找到新编号的职工
            cout << "查到"<<id<<"编号的职工，请输入新职工号：" << endl;
            int newId = 0;
            cin >> newId;
            while(this->IsExistEmp(newId)>0)
            {
                cout << "该职工号已存在，请重新输入新职工号：" << endl;
            }

            string newName;
            cout << "请输入新姓名：" << endl;
            cin >> newName;

            int newdId;
            cout << "请输入新部门号：" << endl;
            cout << "1.普通职工" << endl;
            cout << "2.经理" << endl;
            cout << "3.老板" << endl;
            cin >> newdId;
            switch(newdId)
            {
            case 1:
                this->m_EmpArray[ret]= new Employee(newId,newName,1);
                delete temp;//释放旧职员内存
                break;
            case 2:
                this->m_EmpArray[ret]= new Manager(newId,newName,2);
                delete temp;
                break;
            case 3:
                this->m_EmpArray[ret]= new Boss(newId,newName,3);
                delete temp;
               break;
            default:
                cout << "职位不变"<< endl;
                this->m_EmpArray[ret]->m_Id=newId;
                this->m_EmpArray[ret]->m_Name=newName;
                break;
            }
            cout<<"修改成功"<<endl;
            this->Save();
        }else{
            cout<<"修改失败，未找到该职位 "<<endl;
        }
        system("pause");
        system("cls");
    }
}


void WorkerManager::FindEmp()
{
    if(this->m_FileIsEmpty)
    {
        cout<<"文件为空"<<endl;
    }else
    {
        cout<<"请输入查找方式："<<endl;
        cout<<"1.按职工编号查找"<<endl;
        cout<<"2.按职工姓名查找"<<endl;
        int type = 0;
        cin>>type;
        switch(type)
        {
        case 1:
        {
            cout<<"请输入查找的职工编号："<<endl;
            int id = 0;
            cin>>id;
            int ret = this->IsExistEmp(id);
            if(ret!=-1)
            {
                cout<<"查找成功"<<endl;
                this->m_EmpArray[ret]->ShowInfo();
            }else{
               cout<<"查找失败，未找到该职位 "<<endl;
            }
            system("pause");
            system("cls");
            break;
        }
        case 2:
        {
            cout<<"请输入查找的职工姓名："<<endl;
            string name;
            cin>>name;
            //加入判断查找标准
            bool flag = false;

            for(int i = 0;i<this->m_EmpNum;i++)
            {
                if(this->m_EmpArray[i]->m_Name == name)
                {
                   cout<<"查找成功"<<endl;
                   this->m_EmpArray[i]->ShowInfo();
                   flag = true;
                }
            }
            //未找到该职员
            if(!flag)
            {
                cout<<"查找失败，未找到该职位 "<<endl;
            }
            system("pause");
            system("cls");
            break;
        }
        default:
            cout<<"输入错误"<<endl;
            break;
        }
    }

}

void WorkerManager::SortEmp()
{
    if(this->m_FileIsEmpty)
    {
        cout<<"文件为空"<<endl;
    }else
    {
        cout<<"请选择排序方式："<<endl;
        cout<<"1.按职工编号升序"<<endl;
        cout<<"2.按职工编号降序"<<endl;
        cout<<"3.返回主界面"<<endl;
        int type;
        cin>>type;
        if(type!=1 && type!=2)
        {
            return;
        }
        for(int i=0;i<this->m_EmpNum-1;i++)
        {
            if(type==1)
            {
                for(int j=0;j<this->m_EmpNum-1-i;j++){
                    if(this->m_EmpArray[j]->m_Id > this->m_EmpArray[j+1]->m_Id)
                    {
                        Swap(this->m_EmpArray[j],this->m_EmpArray[j+1]);
                        cout<<"第"<<j+1<<"和"<<j+2<<"交换"<<endl;
                        
                    }
                }
            }
            else if(type==2)
            {
                for(int j=0;j<this->m_EmpNum-1-i;j++){
                    if(this->m_EmpArray[j]->m_Id < this->m_EmpArray[j+1]->m_Id)
                    {
                        Swap(this->m_EmpArray[j],this->m_EmpArray[j+1]);
                    }

                }
            }
        }
        cout<<"排序成功"<<endl;
        this->Save();
        this->ShowEmp();
        system("pause");
        system("cls");
    }
}

void WorkerManager::Swap(Worker *&p1, Worker *&p2)
{      
        Worker *temp = p1;
        p1 = p2;
        p2 = temp;
    
}

void WorkerManager::CleanFile()
{
    cout <<"确认清空？"<<endl;
    cout <<"1.确认"<<endl;
    cout <<"2.取消"<<endl;
    int select = 0;
    cin>>select;
    if(select==1)
    {
        //清空文件
        ofstream ofs(FILENAME,ios::trunc);
        ofs.close();
        for(int i=0;i<this->m_EmpNum;i++)
        {//删除堆区的每个职工对象
        delete this->m_EmpArray[i];
        this->m_EmpArray[i]=NULL;
        }
        // 删除堆区数组指针
        delete []this->m_EmpArray;
        this->m_EmpArray = NULL;
        this->m_EmpNum = 0;
        this->m_FileIsEmpty = true;
        cout<<"清空成功"<<endl;
    }

    system("pause");
    system("cls");
}

WorkerManager::~WorkerManager()
{
 if(this->m_EmpArray!=NULL)   
 {
    for(int i=0;i<this->m_EmpNum;i++)
    {
        if(this->m_EmpArray[i]!=NULL)
        {
        delete this->m_EmpArray[i];
        this->m_EmpArray[i]=NULL;
        }
    }
    delete []this->m_EmpArray;
    this->m_EmpArray = NULL;
 }
}