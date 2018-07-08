#include <algorithm>
#include <iostream>//���������ͷ�ļ�
#include <string>//�ַ�����ͷ�ļ�
#include <iomanip>//��ʹ�ø�ʽ��I/O��ʱ��Ӧ�ð������ͷ�ļ�
#include <cstring>
#include <fstream>
//����/����ļ������ͷ�ļ�
 
using namespace std;

const int Max_Teacher=30;//��ʦ��������30����
const int Max_Student=10;//ѧ����������10����

//��ʦ�� 
class Teacher
{
//�������˽�г�Ա
private:
    int flag;  //ɾ����� 1:��ɾ 0:δɾ
    int id;   //��ʦ���� 
    char name[10];  //��ʦ����
    int borrowbook[Max_Teacher];//����ͼ��
//������Ĺ��г�Ա
public:
    Teacher() {}//���캯���������ǳ�ʼ���Ĳ���
    char *GetName()
    {
        return name;   //��ȡ����
    }
    int GetTag()
    {
        return flag;   //��ȡɾ�����
    }
    int GetID()
    {
        return id;   //��ȡ��ʦ�˺� 
    }
    void SetName(char n[])            //��������
    {
        strcpy(name,n);
    }
    void DelBook()
    {
        flag=1;     //����ɾ����� 1:��ɾ 0:δɾ
    }
    void AddTeacher(int i,char *n)//������ʦ 
    {
        flag=0;
        id=i;
        strcpy(name,n);
        for(int j=0; j<Max_Teacher; j++)
            borrowbook[j]=0;
    }
    void BorrowBook(int book_id)//�������
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
    int ReturnBook(int book_id)//�������
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
    void Disp()//������ʦ��Ϣ
    {
        cout << setw(5) << id <<setw(10) << name<<"�����ţ�[";
        for(int i=0; i<Max_Teacher; i++)
            if(borrowbook[i]!=0)
                cout << borrowbook[i] << "|";
        cout << "]"<<endl;
    }
};
//��ʦ��⣬ʵ�ֽ�����ʦ�ĸ�������
class TeacherData
{
//�������˽�г�Ա
private:
    int top;       //��ʦ��¼ָ��
    Teacher teacher[1000];//��ʦ��¼������1000����ʦ 
//�������˽�г�Ա
public:
    TeacherData()   //���캯������teacher.txt����teacher[]��
    {
        Teacher t;
        top=-1;
        fstream file("teacher.txt",ios::in);//��һ�������ļ�
        while (1)//������ѭ����
        {
            file.read((char *)&t,sizeof(t));
            if (!file)break;
            top++;
            teacher[top]=t;
        }
        file.close();     //�ر� teacher.txt
    }
    void Clear()//ɾ��������ʦ��Ϣ
    {
        top=-1;
    }
    int AddTeacher(int id,char *n)//�����ʦʱ�Ȳ����Ƿ����
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
    Teacher *query(int teacher_id)//���˺Ų���
    {
        for (int i=0; i<=top; i++)
            if (teacher[i].GetID()==teacher_id &&
                    teacher[i].GetTag()==0)
            {
                return &teacher[i];
            }
        return NULL;
    }
    void Disp()  //���������ʦ��Ϣ
    {
        for (int i=0; i<=top; i++)
            teacher[i].Disp();
    }
    void TeacherDataMaintain();//��ʦ���� 
    ~TeacherData()  //������������teacher[]д��teacher.txt�ļ���
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
        cout <<"\n\n\t\t\t      ��   ʦ   ��   ��\n\n\n\t\t\t      1     ��      ��\n\n\t\t\t      2     ��      ��";
		cout <<"\n\n\t\t\t      3     ɾ      ��\n\n\t\t\t      4     ��      ��\n\n\t\t\t      5     ��      ʾ";
		cout <<"\n\n\t\t\t      6     ȫ      ɾ\n\n\t\t\t      0     ��      ��"<<endl;
        cin >> choice;
        switch (choice)
        {
        case '1':
            cout << "������ʦ�˺�:";
            cin >> teacher_id;
            cout << "������ʦ����:";
            cin >> teacher_name;
            AddTeacher (teacher_id,teacher_name);
            break;
        case '2':
            cout << "������ʦ�˺�:";
            cin >> teacher_id;
            t=query(teacher_id);
            if (t==NULL)
            {
                cout << " ����ʦ������  "<<endl;
                break;
            }
            cout << "�����µ�����:";
            cin >> teacher_name;
            t->SetName(teacher_name);
            break;
        case '3':
            cout << " ������ʦ�˺�:";
            cin >> teacher_id;
            t=query(teacher_id);
            if (t==NULL)
            {
                cout <<" ����ʦ������" << endl;
                break;
            }
            t->DelBook();
            break;
        case '4':
            cout << "������ʦ�˺�:";
            cin >> teacher_id;
            t=query(teacher_id);
            if (t==NULL)
            {
                cout <<"����ʦ������"<< endl;
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
            cout<<"���������������룺";
            break;
        }
    }
}
//ѧ���� 
class Student
{
//�������˽�г�Ա
private:
    int flag;  //ɾ����� 1:��ɾ 0:δɾ
    int id;   //ѧ��ѧ�� 
    char name[10];  //ѧ������
    int borrowbook[Max_Student];//����ͼ��
//������Ĺ��г�Ա
public:
    Student() {}//���캯���������ǳ�ʼ���Ĳ���
    char *GetName()
    {
        return name;   //��ȡ����
    }
    int GetTag()
    {
        return flag;   //��ȡɾ�����
    }
    int GetID()
    {
        return id;   //��ȡѧ���˺� 
    }
    void SetName(char n[])            //��������
    {
        strcpy(name,n);
    }
    void DelBook()
    {
        flag=1;     //����ɾ����� 1:��ɾ 0:δɾ
    }
    void AddStudent(int i,char *n)//����ѧ�� 
    {
        flag=0;
        id=i;
        strcpy(name,n);
        for(int j=0; j<Max_Student; j++)
            borrowbook[j]=0;
    }
    void BorrowBook(int book_id)//�������
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
    int ReturnBook(int book_id)//�������
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
    void Disp()//����ѧ����Ϣ
    {
        cout << setw(5) << id <<setw(10) << name<<"�����ţ�[";
        for(int i=0; i<Max_Student; i++)
            if(borrowbook[i]!=0)
                cout << borrowbook[i] << "|";
        cout << "]"<<endl;
    }
};
//ѧ����⣬ʵ�ֽ���ѧ���ĸ�������
class StudentData
{
//�������˽�г�Ա
private:
    int top;       //ѧ����¼ָ��
    Student student[10000];//ѧ����¼������10000��ѧ�� 
//�������˽�г�Ա
public:
    StudentData()   //���캯������teacher.txt����teacher[]��
    {
        Student t;
        top=-1;
        fstream file("student.txt",ios::in);//��һ�������ļ�
        while (1)//������ѭ����
        {
            file.read((char *)&t,sizeof(t));
            if (!file)break;
            top++;
            student[top]=t;
        }
        file.close();     //�ر� teacher.txt
    }
    void Clear()//ɾ������ѧ����Ϣ
    {
        top=-1;
    }
    int AddStudent(int id,char *n)//���ѧ��ʱ�Ȳ����Ƿ����
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
    Student *query(int student_id)//���˺Ų���
    {
        for (int i=0; i<=top; i++)
            if (student[i].GetID()==student_id &&
                    student[i].GetTag()==0)
            {
                return &student[i];
            }
        return NULL;
    }
    void Disp()  //���������ʦ��Ϣ
    {
        for (int i=0; i<=top; i++)
            student[i].Disp();
    }
    void StudentDataMaintain();//ѧ������ 
    ~StudentData()  //������������student[]д��student.txt�ļ���
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
        cout <<"\n\n\t\t\t      ѧ   ��   ��   ��\n\n\n\t\t\t      1     ��      ��\n\n\t\t\t      2     ��      ��";
		cout <<"\n\n\t\t\t      3     ɾ      ��\n\n\t\t\t      4     ��      ��\n\n\t\t\t      5     ��      ʾ";
		cout <<"\n\n\t\t\t      6     ȫ      ɾ\n\n\t\t\t      0     ��      ��"<<endl;
        cin >> choice;
        switch (choice)
        {
        case '1':
            cout << "����ѧ���˺�:";
            cin >> student_id;
            cout << "����ѧ������:";
            cin >> student_name;
            AddStudent (student_id,student_name);
            break;
        case '2':
            cout << "����ѧ���˺�:";
            cin >> student_id;
            t=query(student_id);
            if (t==NULL)
            {
                cout << " ��ѧ��������  "<<endl;
                break;
            }
            cout << "�����µ�����:";
            cin >> student_name;
            t->SetName(student_name);
            break;
        case '3':
            cout << " ����ѧ���˺�:";
            cin >> student_id;
            t=query(student_id);
            if (t==NULL)
            {
                cout <<" ��ѧ��������" << endl;
                break;
            }
            t->DelBook();
            break;
        case '4':
            cout << "����ѧ���˺�:";
            cin >> student_id;
            t=query(student_id);
            if (t==NULL)
            {
                cout <<"��ѧ��������"<< endl;
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
            cout<<"���������������룺";
            break;
        }
    }
}
//ͼ���࣬ʵ�ֶ�ͼ���������ͼ��ı�ţ��������۸����ߣ�����������
class Book
{
//�������˽�г�Ա
private:
    int tag;//ɾ����� 1:��ɾ 0:δɾ
    char name[20];//����
    char writer[20];//ͼ������ 
    int id;//ͼ����
    float fprice;//ͼ��۸�
    int onshelf;//�Ƿ��ټ� 1:�ټ� 2:�ѽ�
//�������˽�г�Ա
public:
    Book() {}
    char *GetName()
    {
        return name;    //��ȡ���� 
    }
    char *GetWriter()
    {
        return writer;    //��ȡ���� 
    }
    int GetID()
    {
        return id;    //��ȡͼ����
    }
    float GetPrice()
    {
    	return fprice;//��ȡ�۸� 
    }
    int GetTag()
    {
        return tag;    //��ȡɾ�����
    }
    void SetName(char n[])//��������
    {
        strcpy(name,n);
    }
    void DeleteBook()
    {
        tag=1;   //ɾ��ͼ��
    }
    void AddBook(int i,char *n)//����ͼ��
    {
        tag=0;
        id=i;
        strcpy(name,n);
        onshelf=1;
    }
    int BorrowBook()//�������
    {
        if (onshelf==1)
        {
            onshelf=0;
            return 1;
        }
        return 0;
    }
    void ReturnBook()//�������
    {
        onshelf=1;
    }
    void Disp()//���ͼ��
    {
        cout << setw(6) << id << setw(18) << name << setw(10)
             <<(onshelf==1? "�ڼ�":"�ѽ�") <<endl;
    }
};
//ͼ����࣬ʵ�ֶ�ͼ���ά�������ң�ɾ����
class BookData
{
private:
    int top;         //ͼ���¼ָ��
    Book book[100]; //ͼ���¼
public:
    BookData()//���캯������book.txt����book[]��
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
    void Clear()//ȫɾ
    {
        top=-1;
    }
    int AddBook(int n,char *na)//����ͼ��
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
    Book *query(int bookid)//����ͼ��
    {
        for (int i=0; i<=top; i++)
            if (book[i].GetID()==bookid &&book[i].GetTag()==0)
            {
                return &book[i];
            }
        return NULL;
    }
    void BookDataMaintain();//ͼ���ά��
    void Disp()
    {
        for (int i=0; i<=top; i++)
            if (book[i].GetTag()==0)
                book[i].Disp();
    }
    ~BookData()//������������book[]д��book.txt�ļ���
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
        cout <<"\n\n\t\t\t      ͼ  ��  ��  �� "<<endl<<endl;
        cout<<"\t\t\t      1   ��     ��\n\n\t\t\t      2   ��     ��\n\n\t\t\t      3   ɾ     ��\n\n\t\t\t      4   ��     ��";
		cout<<"\n\n\t\t\t      5   ��     ʾ\n\n\t\t\t      6   ȫ     ɾ\n\n\t\t\t      0   ��     ��"<<endl;
        cin >> choice;
        switch (choice)
        {
        case '1':
            cout << "����ͼ����:"<<endl;
            cin >> book_id;
            cout << "����ͼ������:"<<endl;
            cin >> book_name;
            AddBook(book_id,book_name);
            break;
        case '2':
            cout << "����ͼ����:"<<endl;
            cin >> book_id;
            b=query(book_id);
            if (b==NULL)
            {
                cout << " ��ͼ�鲻����  "<<endl;
                break;
            }
            cout << "�����µ�����:"<<endl;
            cin >> book_name;
            b->SetName(book_name);
            break;
        case '3':
            cout <<" ����ͼ����:"<<endl;
            cin >> book_id;
            b=query(book_id);
            if (b==NULL)
            {
                cout <<" ��ͼ�鲻����" << endl;
                break;
            }
            b->DeleteBook();
            break;
        case '4':
            cout << "  ����ͼ����:"<<endl;
            cin >> book_id;
            b=query(book_id);
            if (b==NULL)
            {
                cout <<"  ��ͼ�鲻����"<< endl;
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
            cout<<"����������������:";
        }
    }
}
//�ж�����ʦ����ѧ��
void Judge()
{
	
} 
//main() ������ʵ�֣�����������������
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
		cout <<endl<<endl<<"\t\t\t     ͼ  ��  ��  ��  ϵ  ͳ\n\n\n";//���캯���������ǳ�ʼ���Ĳ���
        cout <<"\t\t\t      1    ��       ��\n\n\t\t\t      2    ��       �� \n\n\t\t\t      3    ͼ �� �� ��";
		cout <<"\n\n\t\t\t      4    �� �� �� ��\n\n\t\t\t      0    ��       ��"<<endl;
		cin >>choice1;
		switch(choice1)
		{
			case  '1':case '2':
				cout<<endl<<endl<<"\t\t\t      ��  ��\n\n\n";
				cout<<"\t\t\t      1     ��   ʦ\n\n\n";
				cout<<"\t\t\t      2     ѧ   ��\n\n\n";
				cin>> choice2;
				switch(choice2)
				{
					case '1':
						cout <<"  �˺�:";
			            cin >>teacher_id;
			            cout <<"  ����:";
			            cin >>*teacher_password;
						cout <<"\t\t\t      1    ��       ��\n\n\t\t\t      2    ��       �� \n\n\t\t\t";
						cin>>choice3;
						switch(choice3)
						{
							case '1':
					            cout <<"  ͼ���ţ� ";
					            cin >>book_id;
					            t=TD.query(teacher_id);//���˺Ų���
					            if (NULL==t)
					            {
					                cout <<"  �����ڸ��˺ţ����ܽ���"<< endl;
					                break;
					            }
					            b=BD.query(book_id);
					            if (b==NULL)
					            {
					                cout <<"  �����ڸ�ͼ�飬���ܽ���"<< endl;
					                break;
					            }
					            if (b->BorrowBook()==0)
					            {
					                cout << "  ��ͼ���ѽ�������ܽ���"<< endl;
					                break;
					            }
					            t->BorrowBook(b->GetID());
					            break;
					        case '2':
					            cout << "   ͼ����:";
					            cin >>book_id;
					            t=TD.query(teacher_id);
					            if (t==NULL)
					            {
					                cout <<" �����ڸ��˺ţ����ܻ���" << endl;
					                break;
					            }
					            b=BD.query(book_id);
					            if (b==NULL)
					            {
					                cout <<"  �����ڸ�ͼ�飬���ܻ���" <<endl;
					                break;
					            }
					            b->ReturnBook();
					            t->ReturnBook(b->GetID());
					            break;
					        default:
           						 cout<<"����������������:";
						}
						break;
					case '2':
						cout <<"  �˺�:";
			            cin >>student_id;
			            cout <<"  ����:";
			            cin >>*student_password;
						cout <<"\t\t\t      1    ��       ��\n\n\t\t\t      2    ��       �� \n\n\t\t\t";
						cin>>choice3;
						switch(choice3)
						{
							case '1':
					            cout <<"  ͼ���ţ� ";
					            cin >>book_id;
					            s=SD.query(student_id);//���˺Ų���
					            if (NULL==t)
					            {
					                cout <<"  �����ڸ��˺ţ����ܽ���"<< endl;
					                break;
					            }
					            b=BD.query(book_id);
					            if (b==NULL)
					            {
					                cout <<"  �����ڸ�ͼ�飬���ܽ���"<< endl;
					                break;
					            }
					            if (b->BorrowBook()==0)
					            {
					                cout << "  ��ͼ���ѽ�������ܽ���"<< endl;
					                break;
					            }
					            s->BorrowBook(b->GetID());
					            break;
					        case '2':
					            cout << "   ͼ����:";
					            cin >>book_id;
					            s=SD.query(student_id);
					            if (s==NULL)
					            {
					                cout <<" �����ڸ��˺ţ����ܻ���" << endl;
					                break;
					            }
					            b=BD.query(book_id);
					            if (b==NULL)
					            {
					                cout <<"  �����ڸ�ͼ�飬���ܻ���" <<endl;
					                break;
					            }
					            b->ReturnBook();
					            s->ReturnBook(b->GetID());
					            break;
					            default:
          							  cout<<"����������������:";
						}
						break;
						default:
           					 cout<<"����������������:";
				}
				break;
				case '3':
	            BD.BookDataMaintain();
	            break;
		        case '4':
		        	cout<<"\n\t\t\t     �������\n\n\n";
		        	cout<<"\t\t\t      1    �� ʦ �� ��\n\n\n";
				    cout<<"\t\t\t      2    ѧ �� �� ��\n\n\n";
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
            		cout<<"����������������:";
	    }
	}
	return 0;
}

