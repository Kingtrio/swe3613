#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sqlite3.h>


using namespace std;

int main()
{
  string line;
  string icd10Code, icd9Code, desc;
  sqlite3 *db;
  
  ifstream icd9;
  icd9.open("icd9.txt");
  sqlite3_open("icd.db", &db);
  sqlite3_stmt *stmt; 
 /* char sql[256];
  sprintf(sql, "%s", "INSERT INTO icd9(Id,Desc) VALUES(?,?)");
  sqlite3_prepare(db, sql, -1, &stmt, 0);
  while(icd9.good())
  {
    getline(icd9,line);
    if(line.size()>0)
    {
      size_t space1=line.find_first_of(" ");
      icd9Code=line.substr(0,space1);
      desc=line.substr(space1);
      sqlite3_bind_text(stmt,1,icd9Code.c_str(),-1,SQLITE_STATIC);
      sqlite3_bind_text(stmt,2,desc.c_str(),-1,SQLITE_STATIC);
      sqlite3_step(stmt);
      sqlite3_reset(stmt);
      //Insert icd9 and desc into db
    }
  }
  icd9.close();

  char sql2[256];
  ifstream icd10;
  icd10.open("icd10.txt");
  sprintf(sql2, "%s", "INSERT INTO icd10(Id,Desc) VALUES(?,?)");
  sqlite3_prepare(db, sql2, -1, &stmt, 0);
  while(icd10.good())
  {
    getline(icd10,line);
    if(line.size()>0)
    { 
      size_t space1=line.find_first_of(" ");
      icd10Code=line.substr(0,space1);
      desc=line.substr(space1);
      sqlite3_bind_text(stmt,1,icd10Code.c_str(),-1,SQLITE_STATIC);
      sqlite3_bind_text(stmt,2,desc.c_str(),-1,SQLITE_STATIC);
      sqlite3_step(stmt);
      sqlite3_reset(stmt);
      //Insert icd10 and desc into db
    }
  }
  icd10.close();                         
  */
  char sql3[256];
  ifstream icd10to9;
  icd10to9.open("icd10to9.txt");
  sprintf(sql3, "%s", "INSERT INTO Convert VALUES(?,?)");
  sqlite3_prepare(db, sql3, -1, &stmt, 0);
  while(icd10to9.good())
  {
    getline(icd10to9,line);
    if(line.size()>0)
    {      
      icd10Code=line.substr(0,7);
      icd9Code=line.substr(6,7);
      icd10Code.erase(remove_if(icd10Code.begin(),icd10Code.end(),::isspace), icd10Code.end());
      icd9Code.erase(remove_if(icd9Code.begin(),icd9Code.end(),::isspace), icd9Code.end());
      sqlite3_bind_text(stmt,1,icd9Code.c_str(),-1,SQLITE_STATIC);
      sqlite3_bind_text(stmt,2,icd10Code.c_str(),-1,SQLITE_STATIC);
      sqlite3_step(stmt);
      sqlite3_reset(stmt);
    //Insert icd9 and icd10 here into db
    }
  }
  icd10to9.close();

  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return 0;
}
