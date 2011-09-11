#include <iostream>
#include <string>
#include <fstream>
#include <sqlite3.h>

using namespace std;

void printmenu ()
{
  cout<<"1: Convert an ICD-9 code to an ICD-10 code"<<endl;
  cout<<"9: Quit"<<endl;
}

int main ()
{
  string icd9;
  sqlite3 *db;
  char sql[256];
  int menuctrl=0;
  string icd10;
  char sql2[256];
  int counter;


  sqlite3_open("icd.db", &db);
  sqlite3_stmt *getIcd, *count;
  sprintf(sql, "%s","SELECT Icd10 FROM Convert WHERE Icd9=?");
  sprintf(sql2, "%s","SELECT COUNT(Icd10) FROM Convert WHERE Icd9=?");  // Make this a second column of the above?
  cout<<"Welcome to icd9 to icd10 conversion!"<<endl;
  sqlite3_prepare(db,sql,-1,&getIcd,0);
  sqlite3_prepare(db,sql2,-1,&count,0);
  while(menuctrl!=9)
  {
    cout<<"What would you like to do?"<<endl;
    printmenu();
    cin>>menuctrl;
    if(menuctrl==1)
    {                          // separate out to a function
      cout<<"Please enter the ICD-9 code to convert:";
      cin>>icd9;
      sqlite3_bind_text(count,1,icd9.c_str(),-1,SQLITE_STATIC);
      sqlite3_step(count);
      counter= sqlite3_column_int(count,0);
      sqlite3_bind_text(getIcd,1,icd9.c_str(),-1,SQLITE_STATIC);
      for(int i=0; i<counter; i++)
      {
      sqlite3_step(getIcd);             
      icd10= (const char*) sqlite3_column_text(getIcd,0);
      cout<<icd10<<endl;
      }
    }  
      
  }

  return 0;
}
