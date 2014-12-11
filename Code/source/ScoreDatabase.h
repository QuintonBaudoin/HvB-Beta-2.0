#pragma once

#include "Decl.h"
#include "sqlite3.h"




class ScoreDatabase
{
	static sqlite3 *s_db;
	static const char *s_dbname;
	ScoreDatabase() {}
public:
	static void open();
	static void addScore(const char *a_name, int a_score);
	static void draw();
	static void close();


};