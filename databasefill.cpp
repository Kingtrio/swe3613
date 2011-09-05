#include <iostream>
#include <string>
#include <fstream>
#include <sqlite3.h>

int main()
{
  string line;
  string icd10Code, icd9Code, desc;
  sqlite3 *db;

  ifstream icd9 ("icd9.txt");
  icd9.open();
  sqlite3_open(icd.db, &db);
  sqlite3_stmt *stmt; 
  char sql[256];
  sprintf(sql, "%s", "INSERT INTO icd9(Id,Desc) VALUES(?,?)");
  sqlite3_prepare(db, sql, -1, &stmt, 0);
  while(icd9.good())
  {
    getline(icd9,line);
    size_t space1=line.find_first_of(" ");
    icd9Code=line.substr(0,space1);
    desc=line.substr(space1);
    sqlite3_bind_text(stmt,1,icd9code,-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,2,desc,-1,SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_reset(stmt);
    //Insert icd9 and desc into db
  }
  icd9.close();

  sql[0]='\0';
  ifstream icd10 ("icd10.txt");
  icd10.open();
  sprintf(sql, "%s", "INSERT INTO icd10(Id,Desc) VALUES(?,?)");
  sqlite3_reset(stmt);
  while(icd10.good())
  {
    getline(icd10,line);
    size_t space1=line.find_first_of(" ");
    icd10Code=line.substr(0,space1);
    desc=line.substr(space1);
    sqlite3_bind_text(stmt,1,icd10code,-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,2,desc,-1,SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_reset(stmt);
    //Insert icd10 and desc into db
  }
  icd10.close();

  sql[0]='\0';
  ifstream icd10to9 ("icd10to9.txt");
  icd10to9.open();
  sprintf(sql, "%s", "INSERT INTO icd10to9 VALUES(?,?)");
  sqlite3_reset(stmt);
  while(icd10to9.good())
  {
    getline(icd10to9,line);
    size_t space1=line.find_first_of(" ");
    size_t space2=line.find_first_of(" ",space1+1);
    icd10Code=line.substr(0,space1);
    icd9Code=line.substr(space1,space2);
    sqlite3_bind_text(stmt,1,icd9code,-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,2,icd10code,-1,SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_reset(stmt);
    //Insert icd9 and icd10 here into db
  }
  icd10to9.close();

  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return 0;
}
