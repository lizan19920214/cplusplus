/**
 * dynamic_cast < type-id > ( expression)
 *      该运算符把expression转换成type-id类型的对象。Type-id必须是类的指针、类的引用或者void*；
 *      如果type-id是类指针类型，那么expression也必须是一个指针，如果type-id是一个引用，那么expression也必须是一个引用。
 * 
 * 使用场景：
 *      用于将一个父类的指针/引用转为子类的指针/应用(下行转换)
 * 
 * 特点：
 *  1、基类必须要有虚函数，因为dynamic_cast是运行时类型检查，需要运行时类型信息，
 *      而虚函数表就是存储运行时类型信息的地方
 *  2、对于下行转换，dynamic_cast是安全的（当类型不一致时，转换过来的是空指针），而static_cast是不安全的
 *  3、对指针进行 dynamic_cast，失败返回 NULL，成功返回正常 cast 后的对象指针；
 *  4、对引用进行 dynamic_cast，失败抛出一个异常，成功返回正常 cast 后的对象引用。
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
 
//美术家
class Artist 
{
    public:
        virtual void draw() {printf("Artist draw\n");}
};
 
//音乐家
class Musician 
{
	public:
};
 
//教师
class Teacher 
{
    public:
        virtual void teachStu() {printf("Teacher teachStu\n");}
};
 
//即是美术，又是音乐家，又是教师的人
class People: public virtual Artist,public virtual Musician,public Teacher 
{
	public:
 
};
 
void test1() 
{
	People *p1 = new People();
	p1->draw();
	p1->teachStu();
 
	Artist *a1 =  dynamic_cast<Artist*>(p1);
 
	a1->draw();     //success: 打印Artist draw

	Artist *a2 =  p1; //向上转换，C++总是能够正确识别。即将派生类的指针直接赋值给基类指针。
    a2->draw();     //success: 打印Artist draw

	//a1->teachStu(); //error: no member named 'teachStu' in 'Artist'
}

void test2()
{
    People *p1 = new People();

    Artist *a1 = p1; //success
    // 明确说明，无法直接用（T*）b的形式去进行由父类指针到派生类指针的转换；
    //People *p2 = (People*)a1; //error: cannot cast 'Artist *' to 'People *' via virtual base 'Artist'
    People *p3 = dynamic_cast<People*>(a1);//success：加了dynamic_cast，进行强转
    p3->draw();
}

void test3() 
{
 
	People *p1 = new People();
	
	printf("\ndynamic_cast test:\n");
 
	Musician *m1 = p1; //success
    //无法直接用（T*）b的形式去进行由父类指针到派生类指针的转换；
	// People *p2 = (People*)m1; //cannot cast 'Musician *' to 'People *' via virtual base 'Musician'
    //Musician是非虚基类，所以，无法进行强制dynamic_cast转换
	// People *p3 = dynamic_cast<People*>(m1);//error: 'Musician' is not polymorphic
}

void test4() 
{
 
	People *p1 = new People();
	
	printf("\ndynamic_cast test:\n");
 
	Teacher *t1 = p1; //success
	People *p2 = (People*)t1;                //success,继承自Teacher，采用非虚继承的方式（不使用virtual），所以ok。
	People *p3 = dynamic_cast<People*>(t1);  //success：加了dynamic_cast，进行强转
 
}

int main() 
{
    std::cout << "test1=============" << std::endl;
	test1();
    std::cout << "test2=============" << std::endl;
	test2();
    std::cout << "test3=============" << std::endl;
	test3();
    std::cout << "test4=============" << std::endl;
	test4();

	return 0;
 
}