#include <algorithm>
#include <iostream>//输入输出的头文件
#include <string>//字符串的头文件
#include <iomanip>//在使用格式化I/O的时候应该包含这个头文件
#include <cstring>
#include <fstream>
//输入/输出文件流类的头文件
 
using namespace std;

const int Max_Teacher=30;//老师允许最多借30本书
const int Max_Student=10;//学生允许最多借10本书

//老师类 
class Teacher
{
//定义类的私有成员
private:
    int flag;  //删除标记 1:已删 0:未删
    int id;   //老师工号 
    char name[10];  //老师姓名
    int borrowbook[Max_Teacher];//所借图书
//定义类的公有成员
public:
    Teacher() {}//构造函数：作用是初始化的操作
    char *GetName()
    {
        return name;   //获取姓名
    }
    int GetTag()
    {
        return flag;   //获取删除标记
    }
    int GetID()
    {
        return id;   //获取老师账号 
    }
    void SetName(char n[])            //设置姓名
    {
        strcpy(name,n);
    }
    void DelBook()
    {
        flag=1;     //设置删除标记 1:已删 0:未删
    }
    void AddTeacher(int i,char *n)//增加老师 
    {
        flag=0;
        id=i;
        strcpy(name,n);
        for(int j=0; j<Max_Teacher; j++)
            borrowbook[j]=0;
    }
    void BorrowBook(int book_id)//借书操作
    {
        for(int i=0; i<Max_Teacher; i++)
        {
            if (borrowbook[i]==0)
            {
                borrowbook[i]=book_id;
                return;
            }
        }
    }
    int ReturnBook(int book_id)//还书操作
    {
        for(int i=0; i<Max_Teacher; i++)
        {
            if(borrowbook[i]==book_id)
            {
                borrowbook[i]=0;
                return 1;
            }
        }
        return 0;
    }
    void Disp()//读出老师信息
    {
        cout << setw(5) << id <<setw(10) << name<<"借书编号：[";
        for(int i=0; i<Max_Teacher; i++)
            if(borrowbook[i]!=0)
                cout << borrowbook[i] << "|";
        cout << "]"<<endl;
    }
};
//老师类库，实现建立老师的个人资料
class TeacherData
{
//定义类的私有成员
private:
    int top;       //老师记录指针
    Teacher teacher[1000];//老师记录，容量1000个老师 
//定义类的私有成员
public:
    TeacherData()   //构造函数，将teacher.txt读到teacher[]中
    {
        Teacher t;
        top=-1;
        fstream file("teacher.txt",ios::in);//打开一个输入文件
        while (1)//加入死循环中
        {
            file.read((char *)&t,sizeof(t));
            if (!file)break;
            top++;
            teacher[top]=t;
        }
        file.close();     //关闭 teacher.txt
    }
    void Clear()//删除所有老师信息
    {
        top=-1;
    }
    int AddTeacher(int id,char *n)//添加老师时先查找是否存在
    {
        Teacher *p=query(id);
        if (p==NULL)
        {
            top++;
            teacher[top].AddTeacher(id,n);
            return 1;
        }
        return 0;
    }
    Teacher *query(int teacher_id)//按账号查找
    {
        for (int i=0; i<=top; i++)
            if (teacher[i].GetID()==teacher_id &&
                    teacher[i].GetTag()==0)
            {
                return &teacher[i];
            }
        return NULL;
    }
    void Disp()  //输出所有老师信息
    {
        for (int i=0; i<=top; i++)
            teacher[i].Disp();
    }
    void TeacherDataMaintain();//老师管理 
    ~TeacherData()  //析构函数，将teacher[]写到teacher.txt文件中
    {
        fstream file("teacher.txt",ios::out);
        for (int i=0; i<=top; i++)
            if (teacher[i].GetTag()==0)
                file.write((char *)&teacher[i],sizeof(teacher[i]));
        file.close();
    }
};
void TeacherData::TeacherDataMaintain()
{
    char choice;
    char teacher_name[20];
    int teacher_id;
    Teacher *t;
    while (choice!='0')
    {
        cout <<"\n\n\t\t\t      老   师   管   理\n\n\n\t\t\t      1     新      增\n\n\t\t\t      2     更      改";
		cout <<"\n\n\t\t\t      3     删      除\n\n\t\t\t      4     查      找\n\n\t\t\t      5     显      示";
		cout <<"\n\n\t\t\t      6     全      删\n\n\t\t\t      0     退      出"<<endl;
        cin >> choice;
        switch (choice)
        {
        case '1':
            cout << "输入老师账号:";
            cin >> teacher_id;
            cout << "输入老师姓名:";
            cin >> teacher_name;
            AddTeacher (teacher_id,teacher_name);
            break;
        case '2':
            cout << "输入老师账号:";
            cin >> teacher_id;
            t=query(teacher_id);
            if (t==NULL)
            {
                cout << " 该老师不存在  "<<endl;
                break;
            }
            cout << "输入新的姓名:";
            cin >> teacher_name;
            t->SetName(teacher_name);
            break;
        case '3':
            cout << " 输入老师账号:";
            cin >> teacher_id;
            t=query(teacher_id);
            if (t==NULL)
            {
                cout <<" 该老师不存在" << endl;
                break;
            }
            t->DelBook();
            break;
        case '4':
            cout << "读入老师账号:";
            cin >> teacher_id;
            t=query(teacher_id);
            if (t==NULL)
            {
                cout <<"该老师不存在"<< endl;
                break;
            }
            t->Disp();
            break;
        case '5':
            Disp();
            break;
        case '6':
            Clear();
            break;
        default:
            cout<<"输入错误，请从新输入：";
            break;
        }
    }
}
//学生类 
class Student
{
//定义类的私有成员
private:
    int flag;  //删除标记 1:已删 0:未删
    int id;   //学生学号 
    char name[10];  //学生姓名
    int borrowbook[Max_Student];//所借图书
//定义类的公有成员
public:
    Student() {}//构造函数：作用是初始化的操作
    char *GetName()
    {
        return name;   //获取姓名
    }
    int GetTag()
    {
        return flag;   //获取删除标记
    }
    int GetID()
    {
        return id;   //获取学生账号 
    }
    void SetName(char n[])            //设置姓名
    {
        strcpy(name,n);
    }
    void DelBook()
    {
        flag=1;     //设置删除标记 1:已删 0:未删
    }
    void AddStudent(int i,char *n)//增加学生 
    {
        flag=0;
        id=i;
        strcpy(name,n);
        for(int j=0; j<Max_Student; j++)
            borrowbook[j]=0;
    }
    void BorrowBook(int book_id)//借书操作
    {
        for(int i=0; i<Max_Student; i++)
        {
            if (borrowbook[i]==0)
            {
                borrowbook[i]=book_id;
                return;
            }
        }
    }
    int ReturnBook(int book_id)//还书操作
    {
        for(int i=0; i<Max_Student; i++)
        {
            if(borrowbook[i]==book_id)
            {
                borrowbook[i]=0;
                return 1;
            }
        }
        return 0;
    }
    void Disp()//读出学生信息
    {
        cout << setw(5) << id <<setw(10) << name<<"借书编号：[";
        for(int i=0; i<Max_Student; i++)
            if(borrowbook[i]!=0)
                cout << borrowbook[i] << "|";
        cout << "]"<<endl;
    }
};
//学生类库，实现建立学生的个人资料
class StudentData
{
//定义类的私有成员
private:
    int top;       //学生记录指针
    Student student[10000];//学生记录，容量10000个学生 
//定义类的私有成员
public:
    StudentData()   //构造函数，将teacher.txt读到teacher[]中
    {
        Student t;
        top=-1;
        fstream file("student.txt",ios::in);//打开一个输入文件
        while (1)//加入死循环中
        {
            file.read((char *)&t,sizeof(t));
            if (!file)break;
            top++;
            student[top]=t;
        }
        file.close();     //关闭 teacher.txt
    }
    void Clear()//删除所有学生信息
    {
        top=-1;
    }
    int AddStudent(int id,char *n)//添加学生时先查找是否存在
    {
        Student *p=query(id);
        if (p==NULL)
        {
            top++;
            student[top].AddStudent(id,n);
            return 1;
        }
        return 0;
    }
    Student *query(int student_id)//按账号查找
    {
        for (int i=0; i<=top; i++)
            if (student[i].GetID()==student_id &&
                    student[i].GetTag()==0)
            {
                return &student[i];
            }
        return NULL;
    }
    void Disp()  //输出所有老师信息
    {
        for (int i=0; i<=top; i++)
            student[i].Disp();
    }
    void StudentDataMaintain();//学生管理 
    ~StudentData()  //析构函数，将student[]写到student.txt文件中
    {
        fstream file("student.txt",ios::out);
        for (int i=0; i<=top; i++)
            if (student[i].GetTag()==0)
                file.write((char *)&student[i],sizeof(student[i]));
        file.close();
    }
};
void StudentData::StudentDataMaintain()
{
    char choice;
    char student_name[20];
    int student_id;
    Student *t;
    while (choice!='0')
    {
        cout <<"\n\n\t\t\t      学   生   管   理\n\n\n\t\t\t      1     新      增\n\n\t\t\t      2     更      改";
		cout <<"\n\n\t\t\t      3     删      除\n\n\t\t\t      4     查      找\n\n\t\t\t      5     显      示";
		cout <<"\n\n\t\t\t      6     全      删\n\n\t\t\t      0     退      出"<<endl;
        cin >> choice;
        switch (choice)
        {
        case '1':
            cout << "输入学生账号:";
            cin >> student_id;
            cout << "输入学生姓名:";
            cin >> student_name;
            AddStudent (student_id,student_name);
            break;
        case '2':
            cout << "输入学生账号:";
            cin >> student_id;
            t=query(student_id);
            if (t==NULL)
            {
                cout << " 该学生不存在  "<<endl;
                break;
            }
            cout << "输入新的姓名:";
            cin >> student_name;
            t->SetName(student_name);
            break;
        case '3':
            cout << " 输入学生账号:";
            cin >> student_id;
            t=query(student_id);
            if (t==NULL)
            {
                cout <<" 该学生不存在" << endl;
                break;
            }
            t->DelBook();
            break;
        case '4':
            cout << "读入学生账号:";
            cin >> student_id;
            t=query(student_id);
            if (t==NULL)
            {
                cout <<"该学生不存在"<< endl;
                break;
            }
            t->Disp();
            break;
        case '5':
            Disp();
            break;
        case '6':
            Clear();
            break;
        default:
            cout<<"输入错误，请从新输入：";
            break;
        }
    }
}
//图书类，实现对图书的描述，图书的编号，书名，价格，作者，借出，还入等
class Book
{
//定义类的私有成员
private:
    int tag;//删除标记 1:已删 0:未删
    char name[20];//书名
    char writer[20];//图书作者 
    int id;//图书编号
    float fprice;//图书价格
    int onshelf;//是否再架 1:再架 2:已借
//定义类的私有成员
public:
    Book() {}
    char *GetName()
    {
        return name;    //获取书名 
    }
    char *GetWriter()
    {
        return writer;    //获取作者 
    }
    int GetID()
    {
        return id;    //获取图书编号
    }
    float GetPrice()
    {
    	return fprice;//获取价格 
    }
    int GetTag()
    {
        return tag;    //获取删除标记
    }
    void SetName(char n[])//设置书名
    {
        strcpy(name,n);
    }
    void DeleteBook()
    {
        tag=1;   //删除图书
    }
    void AddBook(int i,char *n)//增加图书
    {
        tag=0;
        id=i;
        strcpy(name,n);
        onshelf=1;
    }
    int BorrowBook()//借书操作
    {
        if (onshelf==1)
        {
            onshelf=0;
            return 1;
        }
        return 0;
    }
    void ReturnBook()//还书操作
    {
        onshelf=1;
    }
    void Disp()//输出图书
    {
        cout << setw(6) << id << setw(18) << name << setw(10)
             <<(onshelf==1? "在架":"已借") <<endl;
    }
};
//图书库类，实现对图书的维护，查找，删除等
class BookData
{
private:
    int top;         //图书记录指针
    Book book[100]; //图书记录
public:
    BookData()//构造函数，将book.txt读到book[]中
    {
        Book b;
        top=-1;
        fstream file("book.txt",ios::in);
        while (1)
        {
            file.read((char *)&b,sizeof(b));
            if (!file) break;
            top++;
            book[top]=b;
        }
        file.close();
    }
    void Clear()//全删
    {
        top=-1;
    }
    int AddBook(int n,char *na)//增加图书
    {
        Book *p=query(n);
        if (NULL==p)
        {
            top++;
            book[top].AddBook(n,na);
            return 1;
        }
        return 0;
    }
    Book *query(int bookid)//查找图书
    {
        for (int i=0; i<=top; i++)
            if (book[i].GetID()==bookid &&book[i].GetTag()==0)
            {
                return &book[i];
            }
        return NULL;
    }
    void BookDataMaintain();//图书库维护
    void Disp()
    {
        for (int i=0; i<=top; i++)
            if (book[i].GetTag()==0)
                book[i].Disp();
    }
    ~BookData()//析构函数，将book[]写到book.txt文件中
    {
        fstream file("book.txt",ios::out);
        for (int i=0; i<=top; i++)
            if (book[i].GetTag()==0)
                file.write((char *)&book[i],sizeof(book[i]));
        file.close();
    }
};
void BookData::BookDataMaintain()
{
    char choice;
    char book_name[40];
    int book_id;
    Book *b;
    while (choice!='0')
    {
        cout <<"\n\n\t\t\t      图  书  管  理 "<<endl<<endl;
        cout<<"\t\t\t      1   新     增\n\n\t\t\t      2   更     改\n\n\t\t\t      3   删     除\n\n\t\t\t      4   查     找";
		cout<<"\n\n\t\t\t      5   显     示\n\n\t\t\t      6   全     删\n\n\t\t\t      0   退     出"<<endl;
        cin >> choice;
        switch (choice)
        {
        case '1':
            cout << "输入图书编号:"<<endl;
            cin >> book_id;
            cout << "输入图书书名:"<<endl;
            cin >> book_name;
            AddBook(book_id,book_name);
            break;
        case '2':
            cout << "输入图书编号:"<<endl;
            cin >> book_id;
            b=query(book_id);
            if (b==NULL)
            {
                cout << " 该图书不存在  "<<endl;
                break;
            }
            cout << "输入新的书名:"<<endl;
            cin >> book_name;
            b->SetName(book_name);
            break;
        case '3':
            cout <<" 读入图书编号:"<<endl;
            cin >> book_id;
            b=query(book_id);
            if (b==NULL)
            {
                cout <<" 该图书不存在" << endl;
                break;
            }
            b->DeleteBook();
            break;
        case '4':
            cout << "  读入图书编号:"<<endl;
            cin >> book_id;
            b=query(book_id);
            if (b==NULL)
            {
                cout <<"  该图书不存在"<< endl;
                break;
            }
            b->Disp();
            break;
        case '5':
            Disp();
            break;
        case '6':
            Clear();
            break;
        default:
            cout<<"输入错误，请从新输入:";
        }
    }
}
//判断是老师还是学生
void Judge()
{
	
} 
//main() 函数的实现，程序的主界面的引导
int main(void)
{
    char choice1,choice2,choice3,choice4;
    int book_id,teacher_id,student_id;
    char *teacher_password,*student_password;
    TeacherData TD;
    StudentData SD;
    Teacher *t;
    Student *s;
    BookData BD;
    Book *b;
    while(choice1!='0')
	{
		cout <<endl<<endl<<"\t\t\t     图  书  管  理  系  统\n\n\n";//构造函数：作用是初始化的操作
        cout <<"\t\t\t      1    借       书\n\n\t\t\t      2    还       书 \n\n\t\t\t      3    图 书 管 理";
		cout <<"\n\n\t\t\t      4    读 者 管 理\n\n\t\t\t      0    退       出"<<endl;
		cin >>choice1;
		switch(choice1)
		{
			case  '1':case '2':
				cout<<endl<<endl<<"\t\t\t      身  份\n\n\n";
				cout<<"\t\t\t      1     老   师\n\n\n";
				cout<<"\t\t\t      2     学   生\n\n\n";
				cin>> choice2;
				switch(choice2)
				{
					case '1':
						cout <<"  账号:";
			            cin >>teacher_id;
			            cout <<"  密码:";
			            cin >>*teacher_password;
						cout <<"\t\t\t      1    借       书\n\n\t\t\t      2    还       书 \n\n\t\t\t";
						cin>>choice3;
						switch(choice3)
						{
							case '1':
					            cout <<"  图书编号： ";
					            cin >>book_id;
					            t=TD.query(teacher_id);//按账号查找
					            if (NULL==t)
					            {
					                cout <<"  不存在该账号，不能借书"<< endl;
					                break;
					            }
					            b=BD.query(book_id);
					            if (b==NULL)
					            {
					                cout <<"  不存在该图书，不能借书"<< endl;
					                break;
					            }
					            if (b->BorrowBook()==0)
					            {
					                cout << "  该图书已借出，不能借书"<< endl;
					                break;
					            }
					            t->BorrowBook(b->GetID());
					            break;
					        case '2':
					            cout << "   图书编号:";
					            cin >>book_id;
					            t=TD.query(teacher_id);
					            if (t==NULL)
					            {
					                cout <<" 不存在该账号，不能还书" << endl;
					                break;
					            }
					            b=BD.query(book_id);
					            if (b==NULL)
					            {
					                cout <<"  不存在该图书，不能还书" <<endl;
					                break;
					            }
					            b->ReturnBook();
					            t->ReturnBook(b->GetID());
					            break;
					        default:
           						 cout<<"输入错误，请从新输入:";
						}
						break;
					case '2':
						cout <<"  账号:";
			            cin >>student_id;
			            cout <<"  密码:";
			            cin >>*student_password;
						cout <<"\t\t\t      1    借       书\n\n\t\t\t      2    还       书 \n\n\t\t\t";
						cin>>choice3;
						switch(choice3)
						{
							case '1':
					            cout <<"  图书编号： ";
					            cin >>book_id;
					            s=SD.query(student_id);//按账号查找
					            if (NULL==t)
					            {
					                cout <<"  不存在该账号，不能借书"<< endl;
					                break;
					            }
					            b=BD.query(book_id);
					            if (b==NULL)
					            {
					                cout <<"  不存在该图书，不能借书"<< endl;
					                break;
					            }
					            if (b->BorrowBook()==0)
					            {
					                cout << "  该图书已借出，不能借书"<< endl;
					                break;
					            }
					            s->BorrowBook(b->GetID());
					            break;
					        case '2':
					            cout << "   图书编号:";
					            cin >>book_id;
					            s=SD.query(student_id);
					            if (s==NULL)
					            {
					                cout <<" 不存在该账号，不能还书" << endl;
					                break;
					            }
					            b=BD.query(book_id);
					            if (b==NULL)
					            {
					                cout <<"  不存在该图书，不能还书" <<endl;
					                break;
					            }
					            b->ReturnBook();
					            s->ReturnBook(b->GetID());
					            break;
					            default:
          							  cout<<"输入错误，请从新输入:";
						}
						break;
						default:
           					 cout<<"输入错误，请从新输入:";
				}
				break;
				case '3':
	            BD.BookDataMaintain();
	            break;
		        case '4':
		        	cout<<"\n\t\t\t     管理对象\n\n\n";
		        	cout<<"\t\t\t      1    老 师 管 理\n\n\n";
				    cout<<"\t\t\t      2    学 生 管 理\n\n\n";
				    cin>>choice4;
					switch(choice4)
					{
						case '1':
							TD.TeacherDataMaintain();
							break;
						case '2':
							SD.StudentDataMaintain();
							break;
						
					 } 
		            break;
		        case '0':
		            break;
		        default:
            		cout<<"输入错误，请从新输入:";
	    }
	}
	return 0;
}

