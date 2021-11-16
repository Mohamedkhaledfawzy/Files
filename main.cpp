#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

fstream outfile;
fstream IDfile;
fstream instructorFile;
struct Course
{
    int id;
    string coursename , instructorname;
    short weeks;

};
struct FirstIndex
{
    string id;
    int RRN;
};
struct Secondindex
{
    string instructorname;
    int ID;
};
void WritePrimIndex(FirstIndex PrmIndxArray[],int numRec,fstream&IDfile) {
    for(int i =0;i<numRec;i++)
    {
        IDfile.write((char*)&PrmIndxArray[i].RRN,sizeof(int));
        IDfile.write(PrmIndxArray[i].id.c_str(),10);
    }
}
void writeSeconIndex(Secondindex SeconIndxArray[],int numRec,fstream&instructorFile)
{
    for(int i =0;i<numRec;i++)
    {
        instructorFile.write((char*)&SeconIndxArray[i].ID,sizeof(int));
        instructorFile.write(SeconIndxArray[i].instructorname.c_str(),10);
    }

}
void sorti(FirstIndex f[],int left , int right)
{
   int i = left, j = right;
   FirstIndex tmp;
   string pivot = f[(left + right) / 2].id;
   while (i <= j) {
        while (f[i].id < pivot)
            i++;
        while (f[j].id > pivot)
            j--;
        if (i <= j) {
            tmp = f[i];
            f[i] = f[j];
            f[j] = tmp;
            i++;
            j--;
        }
    }
    if (left < j)
        sorti(f, left, j);
    if (i < right)
        sorti(f, i, right);


}
void AddCourse(int num)
{
    Course s[num];
    FirstIndex f[num];
    Secondindex g[num];

    outfile.open("outfile.txt",ios::out);
    IDfile.open("ID.txt",ios::out);
    instructorFile.open("Instructor.txt",ios::out);

    for(int i=0;i<num;i++)
    {
        cout<<"Enter Course ID: "<<endl;
        cin>>s[i].id;
        cout<<"Enter Course Name: "<<endl;
        cin>>s[i].coursename;
        cout<<"Enter Course Instructor Name: "<<endl;
        cin>>s[i].instructorname;
        cout<<"Enter Course Weeks: "<<endl;
        cin>>s[i].weeks;
        f[i].id=s[i].id;
        f[i].RRN=i;
        g[i].instructorname=s[i].instructorname;
        g[i].ID=s[i].id;
    }

    outfile.write((char *)&s,num);
    sorti(f,0,num);
    WritePrimIndex(f,num,IDfile);
    writeSeconIndex(g,num,instructorFile);
    outfile.close();
    IDfile.close();
    instructorFile.close();
}
int GetRecordRRN(FirstIndex PrmIndxArray[], int numRec, string ID) {
	int RRN = -1;
	int low = 0, mid, high = numRec - 1;

	while (low <= high) {
		mid = (low + high) / 2;
		if (ID < PrmIndxArray[mid].id)
			high = mid - 1;
		else if (ID > PrmIndxArray[mid].id)
			low = mid + 1;
		else {
			RRN = PrmIndxArray[mid].RRN;
			break;
		}
	}
	return RRN;
}
string GetStudentID(Secondindex ScndIndxArray[], int numRec, string Name) {
	string ID = "";
	int low = 0, mid, high = numRec - 1;

	while (low <= high) {
		mid = (low + high) / 2;
		if (Name < ScndIndxArray[mid].instructorname)
			high = mid - 1;
		else if (Name > ScndIndxArray[mid].instructorname)
			low = mid + 1;
		else {
			ID = ScndIndxArray[mid].ID;
			break;
		}
	}
	return ID;
}
void DeleteCourse(string ID)
{
    IDfile.open("ID.txt",ios::in);
    outfile.open("outfile.txt",ios::in);
    int sizee=sizeof(IDfile);
    int RRN;
    FirstIndex *f=new FirstIndex[sizee];
    for(int i=01;i<sizeof(IDfile);i++)
    {
       IDfile.read((char *)&f[i],sizeof(f[i]));
    }
   RRN=GetRecordRRN(f,sizee,ID);
   outfile.seekp(RRN,ios::beg);
   outfile.write((char *)'*',sizeof('*'));
   IDfile.close();
   outfile.close();
}
void Deleteinstructor(string name)
{
    IDfile.open("ID.txt",ios::in);
    instructorFile.open("Instructor.txt",ios::in);
    outfile.open("outfile.txt",ios::in);
    int sizee=sizeof(instructorFile);
    int RRN;
    Secondindex *s=new Secondindex[sizee];
    FirstIndex *f=new FirstIndex[sizee];

    for(int i=01;i<sizeof(IDfile);i++)
    {
       IDfile.read((char *)&f[i],sizeof(f[i]));
    }
    for(int i=01;i<sizeof(instructorFile);i++)
    {
       instructorFile.read((char *)&s[i],sizeof(s[i]));
    }
   string ID=GetStudentID(s,sizee,name);
   RRN=GetRecordRRN(f,sizee,ID);
   outfile.seekp(RRN,ios::beg);
   outfile.write((char *)'*',sizeof('*'));

   IDfile.close();
   instructorFile.close();
   outfile.close();
}
void PrintCourse(string id)
{
    IDfile.open("ID.txt",ios::in);
    outfile.open("outfile.txt",ios::in);
    int sizee=sizeof(IDfile);
    int RRN;
    FirstIndex *f=new FirstIndex[sizee];
    for(int i=01;i<sizeof(IDfile);i++)
    {
       IDfile.read((char *)&f[i],sizeof(f[i]));
    }
   RRN=GetRecordRRN(f,sizee,id);
   outfile.seekg(RRN,ios::beg);

   Course temp;
   outfile.read((char *)&temp,sizeof(temp));
   cout<<"ID: "<<temp.id<<endl;
   cout<<"instructor name: "<<temp.instructorname<<endl;
   cout<<"Course name: "<<temp.coursename<<endl;
   cout<<"weeks: "<<temp.weeks<<endl;
   IDfile.close();
   outfile.close();
}
void PrintInstructor(string name)
{
    IDfile.open("ID.txt",ios::in);
    instructorFile.open("Instructor.txt",ios::in);
    outfile.open("outfile.txt",ios::in);
    int sizee=sizeof(instructorFile);
    int RRN;
    Secondindex *s=new Secondindex[sizee];
    FirstIndex *f=new FirstIndex[sizee];

    for(int i=01;i<sizeof(IDfile);i++)
    {
       IDfile.read((char *)&f[i],sizeof(f[i]));
    }
    for(int i=01;i<sizeof(instructorFile);i++)
    {
       instructorFile.read((char *)&s[i],sizeof(s[i]));
    }
   string ID=GetStudentID(s,sizee,name);
   RRN=GetRecordRRN(f,sizee,ID);
   outfile.seekg(RRN,ios::beg);
   Course temp;
   outfile.read((char *)&temp,sizeof(temp));
   cout<<"ID: "<<temp.id<<endl;
   cout<<"instructor name: "<<temp.instructorname<<endl;
   cout<<"Course name: "<<temp.coursename<<endl;
   cout<<"weeks: "<<temp.weeks<<endl;
   IDfile.close();
   instructorFile.close();
   outfile.close();
}
void UpdateCourse(string id)
{
    IDfile.open("ID.txt",ios::in);
    outfile.open("outfile.txt",ios::in);
    int sizee=sizeof(IDfile);
    int RRN;
    FirstIndex *f=new FirstIndex[sizee];
    for(int i=01;i<sizeof(IDfile);i++)
    {
       IDfile.read((char *)&f[i],sizeof(f[i]));
    }
   RRN=GetRecordRRN(f,sizee,id);
   outfile.seekp(RRN,ios::beg);


   IDfile.close();
   outfile.close();
}
void Updateinstructor(string name)
{
    IDfile.open("ID.txt",ios::in);
    instructorFile.open("Instructor.txt",ios::in);
    outfile.open("outfile.txt",ios::in);
    int sizee=sizeof(instructorFile);
    int RRN;
    Secondindex *s=new Secondindex[sizee];
    FirstIndex *f=new FirstIndex[sizee];

    for(int i=01;i<sizeof(IDfile);i++)
    {
       IDfile.read((char *)&f[i],sizeof(f[i]));
    }
    for(int i=01;i<sizeof(instructorFile);i++)
    {
       instructorFile.read((char *)&s[i],sizeof(s[i]));
    }
   string ID=GetStudentID(s,sizee,name);
   RRN=GetRecordRRN(f,sizee,ID);
   outfile.seekp(RRN,ios::beg);


   IDfile.close();
   instructorFile.close();
   outfile.close();
}
int main()
{
    int choice,numberofcources;
    cout<<"1) Add new course"<<endl;
    cout<<"2) Delete course (ID)"<<endl;
    cout<<"3) Delete course(instructor name)"<<endl;
    cout<<"4) Print course (ID)"<<endl;
    cout<<"5) Print course (instructor name)"<<endl;
    cout<<"6) Update course (ID)"<<endl;
    cout<<"7) Update course (instructor name)"<<endl;
    cout<<"8) Exit"<<endl;
    cout<<"Please Enter Your Choice: "<<endl;
    cin>>choice;
    while(choice<8)
    {
        if(choice==1)
        {
            cout<<" Enter Number of Cources: "<<endl;
            cin>>numberofcources;
            AddCourse(numberofcources);
        }
        if(choice==2)
        {
            string ID;
            cout<<"Enter ID u want to delete:"<<endl;
            cin>>ID;
            DeleteCourse(ID);
        }
        if(choice==3)
        {
            string name;
            cout<<"Enter Instructor name u want to delete:"<<endl;
            cin>>name;
            Deleteinstructor(name);
        }
        if(choice==4)
        {
            string ID;
            cout<<"Enter the Course ID u want to print: "<<endl;
            cin>>ID;
            PrintCourse(ID);

        }
        if(choice==5)
        {
            string name;
            cout<<"Enter instructor name u want to print :"<< endl;
            cin>>name;
            PrintInstructor(name);
        }
        if(choice==6)
        {


        }
        if(choice==8)
        {break;}

        cout<<"1) Add new course"<<endl;
        cout<<"2) Delete course (ID)"<<endl;
        cout<<"3) Delete course(instructor name)"<<endl;
        cout<<"4) Print course (ID)"<<endl;
        cout<<"5) Print course (instructor name)"<<endl;
        cout<<"6) Update course (ID)"<<endl;
        cout<<"7) Update course (instructor name)"<<endl;
        cout<<"8) Exit"<<endl;
        cout<<"Please Enter Your Choice: "<<endl;
        cin>>choice;
    }

    return 0;
}
