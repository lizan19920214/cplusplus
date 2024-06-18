/**
 * 成员函数做友元
*/
#include <iostream>
#include <string>
using namespace std;

class Building;

class RoomMate
{
public:
    RoomMate();
    ~RoomMate();

    void visit1();
    void visit2();
private:
    Building* m_building;
};

class Building
{
public:
    string m_sittingRoom;
    //声明成员函数1为友元
    friend void RoomMate::visit1();
public:
    Building()
    {
        m_sittingRoom = "客厅";
        m_bedRoom = "卧室";
    }

private:
    string m_bedRoom;
};

RoomMate::RoomMate()
{
    m_building = new Building();
}

RoomMate::~RoomMate()
{
    delete m_building;
    m_building = nullptr;
}


void RoomMate::visit1()
{
    cout << "visit1" << endl;
    cout << "室友方法1访问" << m_building->m_sittingRoom << endl;
    //因为室友的方法1为建筑类的友元，所有可以访问私有变量
    cout << "室友方法1访问" << m_building->m_bedRoom << endl;
}

void RoomMate::visit2()
{
    cout << "visit2" << endl;
    cout << "室友方法2访问" << m_building->m_sittingRoom << endl;
    // cout << "室友方法2访问" << m_building->m_bedRoom << endl;
}

int main()
{
    RoomMate r;
    r.visit1();
    r.visit2();
    return 0;
}